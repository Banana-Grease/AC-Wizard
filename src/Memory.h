#pragma once
#include "Includes.h"

struct Memory {

    // offsets from the player base in the entity list
    enum MemOffsets {
        EntityHealthOffset = 0xEC,
        EntityNameOffset = 0x205, // each player name is 16 characters long. that offset is the beggining character
        EntityXPosOffset = 0x28,
        EntityYPosOffset = 0x2C,
        EntityZPosOffset = 0x30
    };

    HWND hwnd;
    DWORD ProcID;
    HANDLE HProc;

    inline uintptr_t GetModuleAddr(const char* ModuleName = "ac_client.exe") {
        HANDLE ModuleHandle = GetModuleHandleA(ModuleName);
        uintptr_t ModuleAddr = (uintptr_t)ModuleHandle;
        return ModuleAddr;
    }

    inline uintptr_t GetMemAddr(const char* ModuleName, uintptr_t ModuleBaseOffset, vector<int> Offsets) {
        uintptr_t Addr = GetModuleAddr();
        Addr += ModuleBaseOffset;
        for (int i = 0; i < Offsets.size(); i++)
        {
            Addr = *(uintptr_t*)Addr;
            Addr += Offsets[i];
        }
        return Addr;
    }

    inline bool Hook(HWND* hwnd, DWORD* ProcID, HANDLE* HProc, LPCSTR WindowName, int Flags) {
        *hwnd = FindWindowA(NULL, WindowName);
        GetWindowThreadProcessId(*hwnd, ProcID);
        *HProc = OpenProcess(Flags, FALSE, *ProcID);
        return true;
    }
};