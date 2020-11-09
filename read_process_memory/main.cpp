#include <iostream>
#include "Memory.h"

int main() {

	LPCWSTR windowName = L"AssaultCube";
	// wchar_t modName = L"ac_client.exe";

	Memory m = Memory(windowName, L"ac_client.exe");

	u_int object_ptr = m.RPM<u_int>(m.moduleBase + 0x10F4F4);
	u_int health = m.RPM<u_int>(object_ptr + 0xF8);

	return 0;
}