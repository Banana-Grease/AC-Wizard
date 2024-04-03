#include "Includes.h"
#include "PlayerStruct.h"
#include "VectorClass.h"
#pragma once

class BunnyHop {
public:
	enum DetectionFlags {
		Modulus = 1
	};
	
private:
	float GetClientHeight() {
		Player Client(true, NULL);
		return Client.GetVec3().z; // return height calculated by Player Class
	}


public:

	void Execute(int Flag) {
		switch (Flag) {
		case Modulus:
			if (!fmodf(GetClientHeight(), 0.25f)) { // if the client height is divisible by .25 evenly, then send jump either through memory or keyboard
				INPUT Input{};
				Input.type = INPUT_KEYBOARD; // set the input type
				Input.ki.wVk = ' '; // set the input to space
				if (!SendInput(1, &Input, sizeof(INPUT)))// send that hoe & error check
					cout << "SendInput Function Failed!\n";
			} return;
		}
	}

};