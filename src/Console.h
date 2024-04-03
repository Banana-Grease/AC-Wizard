#include "Includes.h"
#pragma once

using std::cout, std::cin, std::string, std::vector;

const LPCSTR WindowTitle = "AC_Wizard";

inline bool ConsOpen{};

inline void StartConsole(FILE* Fptr) {
    AllocConsole();
    SetConsoleTitleA(WindowTitle);
    freopen_s(&Fptr, "CONOUT$", "w", stdout);
    ConsOpen = true;
}
inline void CloseConsole() {
    ConsOpen = false;

    cout << "Console Detached";

    FreeConsole();
    DestroyWindow(FindWindowA(NULL, WindowTitle)); // attempt to destroy the window. idk why it dont work so i wont use it lol. INSTEAD USE OBFUSCATEWINDOW
}
inline void ObfuscateWindow(bool DoHide) {
    switch (DoHide) {
    case true:
        ShowWindow(FindWindowA(NULL, WindowTitle), SW_HIDE); // hide console
        break;
    case false:
        ShowWindow(FindWindowA(NULL, WindowTitle), SW_SHOW); // show console
        break;
    }
}