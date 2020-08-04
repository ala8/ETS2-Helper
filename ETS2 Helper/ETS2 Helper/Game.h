#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

class Game
{
private:
	uintptr_t GetDynamicAddr(HANDLE hProc, uintptr_t pointer, std::vector<DWORD> offsets);
public:
	// Variables
	DWORD processId;
	uintptr_t moduleBaseAddress;
	uintptr_t moduleBasePtr;
	
	// Dynamic addresses
	uintptr_t dynamicCash;
	uintptr_t dynamicXP;

	// Functions
	Game();
};

