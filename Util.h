#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <algorithm>


namespace Utils {

	static HANDLE pConsole;

	static __forceinline void FreeConsole() 
	{
		AllocConsole();
		FILE* pFile;
		freopen_s(&pFile, "CONIN$", "r", stdout);
		freopen_s(&pFile, "CONOUT$", "w", stderr);
		freopen_s(&pFile, "CONOUT$", "w", stdout);
		pConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	static void Log(std::string message)
	{
		HANDLE pConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(pConsole, 4);
		std::cout << ("[X] ");
		SetConsoleTextAttribute(pConsole, 15);
		std::cout << message << std::endl;
	}

	static void Verify(PBYTE address, std::string Type){if (!address){Log("Failed to find " + Type);}}
}
