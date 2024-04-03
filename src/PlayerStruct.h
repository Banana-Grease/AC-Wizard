#include "Includes.h"
#include "Memory.h"
#include "VectorClass.h"
#pragma once

struct Player {
	int* HPptr;
	float* LookXptr, * LookYptr, * SNCoordptr, * EWCoordptr, * HCoordptr;

	// --- funcs

	Vector3 GetVec3() {
		Vector3 ReturnVec3(*EWCoordptr, *SNCoordptr, *HCoordptr);
		return ReturnVec3;
	}

	void MemRefresh(bool ClientPlayer, int EntityIndex) {
		Memory MemClass{};

		if (ClientPlayer) {
			HPptr = (int*)MemClass.GetMemAddr("ac_client.exe", 0x17B0B8, { 0xEC });
			LookXptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x187C0C, { 0x34 });
			LookYptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x17B0B8, { 0x38 });
			SNCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x17B0B8, { 0x2C });
			EWCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x17B0B8, { 0x28 });
			HCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x17B0B8, { 0x30 });
		}
		else {
			HPptr = (int*)MemClass.GetMemAddr("ac_client.exe", 0x187C10, { (0x4 * EntityIndex), MemClass.EntityHealthOffset });
			LookXptr = nullptr; // dont need this
			LookYptr = nullptr; // dont need this
			SNCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x187C10, { (0x4 * EntityIndex), MemClass.EntityYPosOffset });
			EWCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x187C10, { (0x4 * EntityIndex), MemClass.EntityXPosOffset });
			HCoordptr = (float*)MemClass.GetMemAddr("ac_client.exe", 0x187C10, { (0x4 * EntityIndex), MemClass.EntityZPosOffset });
		}
	}

	// initialiser thing
	// NOTE in AssaultCube first entity is at index 1
	Player(bool ClientPlayer, int EntityIndex) {
		MemRefresh(ClientPlayer, EntityIndex);
	}
};