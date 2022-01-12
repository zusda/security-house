

#include"header.h"

int entry_main() {
	ShellcodeStart();
	CreateShellcode();
	return 0;
}

void CreateShellcode() {
	typedef int (__CRTDECL* xx_printf)(
		_In_z_ _Printf_format_string_ char const* const _Format,
		...);
	xx_printf f_printf;
	f_printf = (xx_printf)GetProcAddress(LoadLibraryA("msvcrt.dll"), "printf");
	f_printf("À¬»øvscode\n");
	f_printf("À¬»øvscode\n");
	f_printf("À¬»øvscode\n");

	HANDLE hbin = CreateFileA("sh.bin", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hbin == INVALID_HANDLE_VALUE) {
		f_printf("create file error:%d\n", GetLastError());
		return;
	}
	DWORD dwSize = (DWORD)ShellcodeEnd - (DWORD)ShellcodeStart;
	DWORD dwWriten;
	WriteFile(hbin, ShellcodeStart, dwSize, &dwWriten, NULL);
	CloseHandle(hbin);

}








