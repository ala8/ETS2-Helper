#include "Game.h"

uintptr_t Game::GetDynamicAddr(HANDLE hProc, uintptr_t pointer, std::vector<DWORD> offsets)
{
	uintptr_t address = pointer;
	for (int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(hProc, (BYTE*)address, &address, sizeof(address), 0);
		address += offsets[i];
	}
	return address;
}

Game::Game()
{
	// OFFSETS
	std::vector<DWORD> CashOffsets = { 0x10, 0x10 };
	std::vector<DWORD> XPOffsets = { 0x1914 };

	// Obtain process ID
	PROCESSENTRY32 procEntry32;
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnapProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(hSnapProc, &procEntry32))
	{
		do
		{
			if (!_wcsicmp(procEntry32.szExeFile, L"eurotrucks2.exe"))
			{
				this->processId = procEntry32.th32ProcessID;
				break;
			}

		} while (Process32Next(hSnapProc, &procEntry32));
	}

	CloseHandle(hSnapProc);


	// Obtain Module base address
	MODULEENTRY32 modEntry32;
	modEntry32.dwSize = sizeof(MODULEENTRY32);

	HANDLE hSnapMod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->processId);

	if (Module32First(hSnapMod, &modEntry32))
	{
		do
		{
			if (!_wcsicmp(modEntry32.szModule, L"eurotrucks2.exe"))
			{

				this->moduleBaseAddress = (uintptr_t)modEntry32.modBaseAddr;
				this->moduleBasePtr = (uintptr_t)modEntry32.modBaseAddr + 0x160ABA0;
				break;
			}

		} while (Module32Next(hSnapMod, &modEntry32));
	}

	CloseHandle(hSnapMod);


	// Get dynamic addresses

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processId);

	this->dynamicCash = this->GetDynamicAddr(hProc, this->moduleBasePtr, CashOffsets);
	this->dynamicXP = this->GetDynamicAddr(hProc, this->moduleBasePtr, XPOffsets);

	CloseHandle(hProc);
}