#include "Includes.h"
#include "VectorClass.h"
#pragma once

class Aimbot {
public:
	float FOV = 20.f;
	float Smoothness = 0.25f;

	enum CorrectionFlags {
		Smooth = 1,
		Snap = 2
	};

private:

	// returns a 2D vector with Yaw and Pitch calculations respectivley
	Vector2 ComputeAngle(Vector3 LocalPlayerPos, Vector3 TargetPlayerPos) {
		Vector2 ReturnVector{};
		
		Vector3 DiffTri = LocalPlayerPos - TargetPlayerPos; // difference of the two points in 3d space

		// Yaw Calculation
		{
			Vector2 Local(LocalPlayerPos.x, LocalPlayerPos.y), Target(TargetPlayerPos.x, TargetPlayerPos.y); // 2 points in 2d space

			ReturnVector.x = atanf((abs(DiffTri.y) / abs(DiffTri.x))) * (180 / std::numbers::pi);

			// calculating final yaw angle by determining and adding offsets
			{
				float BaseAngle;
				if (Target.x > Local.x) {
					BaseAngle = 90.f;
				} else {
					BaseAngle = 270.f;
				}

				// if target is first or fourth quadrant around the client
				if (Target.x < Local.x && Target.y < Local.y || Target.x > Local.x && Target.y > Local.y) {
					ReturnVector.x = BaseAngle + ReturnVector.x;
				} else{
					ReturnVector.x = BaseAngle - ReturnVector.x;
				}
			}
		}

		// Pitch Calculation hypot(LocalPlayerPos.x, LocalPlayerPos.y)
		{
			Vector2 Local(sqrt((DiffTri.y*DiffTri.y) + (DiffTri.x*DiffTri.x)), 0.f), Target(0.f, DiffTri.z); // 2 points in 2d space

			if (DiffTri.z > 0)
				ReturnVector.y = -atanf((abs(Target.y) / abs(Local.x))) * (180 / std::numbers::pi);
			else
				ReturnVector.y = atanf((abs(Target.y) / abs(Local.x))) * (180 / std::numbers::pi);
		}

		return ReturnVector;
	}

public:

	void Execute(int Flag) {
		Player ClientPlayer(true, NULL), TargetPlayer(true, 1); // init players, no need to passthrough just find again

		short BestTargetIndex = 1; // the index in the entity list, which is the closest to the current aim-point
		float BestTargetDistance = HUGE_VALF; // the distance that is from the current aim-point. set to infinity so there is always better option
		Vector2 ComputedAngles; // where to put the angles once computed

		// this loop fids which player is closest to the clients current aim-point
		for (int i = 1; i < 8; i++) {
			TargetPlayer.MemRefresh(false, i);

			// if target player has un-realistic health, skip
			// this either means that they are dead or do not exist
			if (*TargetPlayer.HPptr < 1 || *TargetPlayer.HPptr > 100) {
				continue;
			}

			// if the target player has the same x and y to client, skip. could be us or right above, either way crashed game
			if (*TargetPlayer.EWCoordptr == *ClientPlayer.EWCoordptr && *TargetPlayer.SNCoordptr == *TargetPlayer.SNCoordptr) {
				continue;
			}


			ComputedAngles = ComputeAngle(ClientPlayer.GetVec3(), TargetPlayer.GetVec3()); // compute angles once each cycle

			// if this rounds distance is better than best, set this round to best
			if (sqrt((abs(ComputedAngles.y - *ClientPlayer.LookYptr) * abs(ComputedAngles.y - *ClientPlayer.LookYptr)) + (abs(ComputedAngles.x - *ClientPlayer.LookXptr) * abs(ComputedAngles.x - *ClientPlayer.LookXptr))) < BestTargetDistance) {
				BestTargetDistance = (abs(ComputedAngles.y - *ClientPlayer.LookYptr) * abs(ComputedAngles.y - *ClientPlayer.LookYptr)) + (abs(ComputedAngles.x - *ClientPlayer.LookXptr) * abs(ComputedAngles.x - *ClientPlayer.LookXptr));
				BestTargetIndex = i;
			}
		}

		// re-compute angles from best index
		TargetPlayer.MemRefresh(false, BestTargetIndex);
		ComputedAngles = ComputeAngle(ClientPlayer.GetVec3(), TargetPlayer.GetVec3());

		// if its outside FOV range, then go to next loop straight away
		if (abs(ComputedAngles.x - *ClientPlayer.LookXptr) > FOV || abs(ComputedAngles.y - *ClientPlayer.LookYptr) > FOV)
			return;

		// if its off by more than .05 degrees, re-compute and act
		if (abs(ComputedAngles.x - *ClientPlayer.LookXptr) > .05 || abs(ComputedAngles.y - *ClientPlayer.LookYptr) > .05) {

			// if the difference is less than 1, just snap the aimbot. it prevents it getting 'unlocked'.
			if ((abs(ComputedAngles.x - *ClientPlayer.LookXptr) < 1 && abs(ComputedAngles.y - *ClientPlayer.LookYptr) < 1)) {
				*ClientPlayer.LookXptr = ComputedAngles.x;
				*ClientPlayer.LookYptr = ComputedAngles.y;
				return;
			}

			// instead of setting the aim pos, add a factor of the difference to create a smoothing effect :)
			{
				// if Snap Flag is enabled, set the final smoothness factor to 1 to snap
				float F_SmoothFactor = Smoothness;
				if (Flag == Snap)
					F_SmoothFactor = 1;

				*ClientPlayer.LookXptr += (ComputedAngles.x - *ClientPlayer.LookXptr) * F_SmoothFactor;
				*ClientPlayer.LookYptr += (ComputedAngles.y - *ClientPlayer.LookYptr) * F_SmoothFactor;
			}
		}
	}
};