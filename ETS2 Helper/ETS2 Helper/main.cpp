// I learnt all this stuff from a course made by guidedhacking: https://guidedhacking.com/threads/start-here-beginners-guide-to-learning-game-hacking.5911/
// This was made for educational purposes only. This is not meant to be a "cheat" or a "hack".

#include "Game.h"

void WriteCash(HANDLE hProc, int newCash, uintptr_t address)
{
	int newValue = newCash;
	WriteProcessMemory(hProc, (LPVOID)address, &newValue, sizeof(newValue), 0);
}

void WriteXP(HANDLE hProc, int newXP, uintptr_t address)
{
	int newValue = newXP;
	WriteProcessMemory(hProc, (LPVOID)address, &newValue, sizeof(newValue), 0);
}

int main()
{
	Game game;
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, game.processId);
	int CashValue;
	int XPValue;
	ReadProcessMemory(hProc, (LPVOID)game.dynamicXP, &XPValue, sizeof(int), 0);
	ReadProcessMemory(hProc, (BYTE*)game.dynamicCash, &CashValue, sizeof(int), 0);

	// Print process information + addresses
	std::cout << "Process & Module Name: eurotrucks2.exe" << std::endl;
	std::cout << "Process ID: 0x" << std::hex << game.processId << std::endl;
	std::cout << "Module base address: 0x" << std::hex << game.moduleBaseAddress << std::endl;
	std::cout << "Module base pointer: 0x" << std::hex << game.moduleBasePtr << std::endl;
	std::cout << "Dynamic cash address: 0x" << std::hex << game.dynamicCash << " -> " << std::dec << CashValue << std::endl;
	std::cout << "Dynamic XP address: 0x" << std::hex << game.dynamicXP << " -> " << std::dec << XPValue << std::endl;
	std::cout << "Process handle: 0x" << std::hex << hProc << std::endl;
	std::cout << std::endl;

	// Use the functions I created above "WriteCash" and "WriteXP" to modify the cash/xp amount.
	// WriteCash example: WriteCash(hProc, *new cash amount*, game.dynamicCash);
	// WriteXP example: WriteXP(hProc, *new XP amount*, game.dynamicXP);

	// USE THE FUNCTIONS ABOVE THIS CLOSEHANDLE FUNCTION
	CloseHandle(hProc);
}