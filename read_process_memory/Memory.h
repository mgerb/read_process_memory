#pragma once

#include <Windows.h>
#include <TlHelp32.h>

class Memory {

public:
	HWND window;
	uintptr_t moduleBase;

	Memory(LPCWSTR windowName, const wchar_t* modName);

	template<typename T> T RPM(SIZE_T address) {
		T buffer;
		ReadProcessMemory(this->hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template<typename T> void WPM(SIZE_T address, T buffer) {
		WriteProcessMemory(this->hProcess, (LPCVOID)address, &buffer, sizeof(buffer), NULL);
	}

private:
	HANDLE hProcess;
	DWORD procId;
};


uintptr_t getModuleBaseAddress(uintptr_t procId, const wchar_t* modName);
