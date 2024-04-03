#include "Includes.h"

#include "Memory.h"
#include "Console.h"
#include "PlayerStruct.h"

#include "Aimbot.h"
#include "BunnyHop.h"

static DWORD WINAPI HackThread(HMODULE hModule) {
	// --- start
	
	SetWindowTextA(FindWindowA(NULL, "AssaultCube"), "AssaultCube - Wizard Injected");
	
	//fptr to open window
	FILE* Fptr = nullptr;

	//memory

	Memory MemClass{}; // no need to use MemClass.Hook(...) as the cheat is internal so why would you risk hooking for no gain? if needed hook with a read-only flag

	//finding addresses

	Player ClientPlayer(true, NULL); // the client we are inject into
	Player TargetPlayer(false, 1); // the target player. init at player 1 in entity list
	
	// initialise cheat classes

	Aimbot AimCheat{};
	BunnyHop BHOP{};

	// --- Main Loop

	StartConsole(Fptr);

	for (;; Sleep(5)) {
		if (GetKeyState(VK_END) & 0x8000) {
			break;
		}

		// console
		if (GetKeyState(VK_INSERT) & 0x8000) {
			ObfuscateWindow(false);
		}
		else if (GetKeyState(VK_DELETE) & 0x8000) { // doesnt work but does dissattach the console from the game PID so can be safley closed xd
			ObfuscateWindow(true);
		}

		// demo controll aim smooth and fov
		if (GetKeyState(VK_UP) & 0x8000) { // up arrow = more smooth
			AimCheat.Smoothness -= .01;
			if (ConsOpen)
				system("cls");
				cout << "Smoothness Factor: " << AimCheat.Smoothness << "\n";
				cout << "FOV Degrees: " << AimCheat.FOV << "\n";
		}
		if (GetKeyState(VK_DOWN) & 0x8000) { // down arrow = less smooth
			AimCheat.Smoothness += .01;
			if (ConsOpen)
				system("cls");
				cout << "Smoothness Factor: " << AimCheat.Smoothness << "\n";
				cout << "FOV Degrees: " << AimCheat.FOV << "\n";
		}
		if (GetKeyState(VK_LEFT) & 0x8000) { // left arrow = less fov
			AimCheat.FOV -= 1;
			if (ConsOpen)
				system("cls");
				cout << "Smoothness Factor: " << AimCheat.Smoothness << "\n";
				cout << "FOV Degrees: " << AimCheat.FOV << "\n";
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) { // right arrow = more fov
			AimCheat.FOV += 1;
			if (ConsOpen)
				system("cls");
				cout << "Smoothness Factor: " << AimCheat.Smoothness << "\n";
				cout << "FOV Degrees: " << AimCheat.FOV << "\n";
		}

		// aimbot
		if (GetKeyState(VK_F) & 0x8000) {
			AimCheat.Execute(AimCheat.Smooth);
		} else if(GetKeyState(VK_G) & 0x8000) {
			AimCheat.Execute(AimCheat.Snap);
		}

		// B-Hop
		if (GetKeyState(VK_SPACE) & 0x8000) {
			BHOP.Execute(BHOP.Modulus);
			cout << "Bhopped\n";
		}
	}


	// eject cheat and clean-up

	if (ConsOpen) // only close it if open
		system("cls");
		cout << "Console Has Exited -> Safe To Close\n\n";
		FreeConsole();

	SetWindowTextA(FindWindowA(NULL, "AssaultCube - Wizard Injected"), "AssaultCube"); // set the title back
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}