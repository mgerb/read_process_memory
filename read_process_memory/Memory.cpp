#include <iostream>
#include "Memory.h"


Memory::Memory(LPCWSTR windowName, const wchar_t* modName) {
	this->window = FindWindow(0, windowName);
	GetWindowThreadProcessId(this->window, &this->procId);
	this->moduleBase = getModuleBaseAddress(this->procId, modName);
	this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
}


uintptr_t getModuleBaseAddress(uintptr_t procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

