


#include "header.h"

__declspec(naked) void ShellcodeStart() {
	__asm {
		jmp ShellcodeEntry
	}
}

__declspec(naked) DWORD getKernel32() {
	__asm {
		mov eax, fs: [30h]
		mov eax, [eax + 0ch]
		mov eax, [eax + 14h]
		mov eax, [eax]
		mov eax, [eax]
		mov eax, [eax + 10h]
		ret
	}
}

FARPROC _GetProcAddress(HMODULE hModuleBase) {
	PIMAGE_DOS_HEADER lpDosHeader = (PIMAGE_DOS_HEADER)hModuleBase;
	PIMAGE_NT_HEADERS32 lpNtHeader = (PIMAGE_NT_HEADERS)((DWORD)hModuleBase + lpDosHeader->e_lfanew);
	if (!lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size) {
		return NULL;
	}
	if (!lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress) {
		return NULL;
	}
	PIMAGE_EXPORT_DIRECTORY lpExports = (PIMAGE_EXPORT_DIRECTORY)((DWORD)hModuleBase + (DWORD)lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	PDWORD lpdwFunName = (PDWORD)((DWORD)hModuleBase + (DWORD)lpExports->AddressOfNames);
	PWORD lpwOrd = (PWORD)((DWORD)hModuleBase + (DWORD)lpExports->AddressOfNameOrdinals);
	PDWORD lpdwFunAddr = (PDWORD)((DWORD)hModuleBase + (DWORD)lpExports->AddressOfFunctions);

	DWORD dwLoop = 0;
	FARPROC pRet = NULL;
	for (; dwLoop <= lpExports->NumberOfNames - 1; dwLoop++) {
		char* pFunName = (char*)(lpdwFunName[dwLoop] + (DWORD)hModuleBase);
		if (
			pFunName[0] == 'G' &&
			pFunName[1] == 'e' &&
			pFunName[2] == 't' &&
			pFunName[3] == 'P' &&
			pFunName[4] == 'r' &&
			pFunName[5] == 'o' &&
			pFunName[6] == 'c' &&
			pFunName[7] == 'A' &&
			pFunName[8] == 'd' &&
			pFunName[9] == 'd' &&
			pFunName[10] == 'r' &&
			pFunName[11] == 'e' &&
			pFunName[12] == 's' &&
			pFunName[13] == 's'
			) {
			pRet = (FARPROC)(lpdwFunAddr[lpwOrd[dwLoop]] + (DWORD)hModuleBase);
			break;
		}
	}
	return pRet;
}


void ShellcodeEntry() {

	//动态调用GetProcAddress
	typedef FARPROC(WINAPI* x_GetProcAddress)(_In_ HMODULE hModule,_In_ LPCSTR lpProcName);
	x_GetProcAddress f_GetProcAddress = (x_GetProcAddress)_GetProcAddress((HMODULE)getKernel32());

	//动态调用LoadLibraryA
	char strLoadLibraryA[] = { 'L','o','a','d','L','i','b','r','a','r','y','A',0};
	typedef HMODULE(WINAPI* x_LoadLibraryA)(_In_ LPCSTR lpLibFileName);
	x_LoadLibraryA f_LoadLibraryA = (x_LoadLibraryA)f_GetProcAddress((HMODULE)getKernel32(), strLoadLibraryA);


	typedef int (WINAPI* dd_MessageBoxA)(
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType);
	char strUser32[] = { 'u','s','e','r','3','2','.','d','l','l',0};
	char strMessageBoxA[] = { 'M','e','s','s','a','g','e','B','o','x','A',0};
	char strfuck_c[] = { 'f','u','c','k','_','c',0};
	char strvs_idio[] = { 'v','s','_','i','d','i','o',0};
	dd_MessageBoxA box523;
	box523 = (dd_MessageBoxA)f_GetProcAddress(f_LoadLibraryA(strUser32), strMessageBoxA);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);
	box523(NULL, strfuck_c, strvs_idio, MB_OK);


	////动态调用GetProcAddress
	//typedef FARPROC(WINAPI* x_GetProcAddress)(_In_ HMODULE hModule,_In_ LPCSTR lpProcName);
	//x_GetProcAddress f_GetProcAddress = (x_GetProcAddress)_GetProcAddress((HMODULE)getKernel32());

	////动态调用LoadLibraryA
	//char strLoadLibraryA[] = { 'L','o','a','d','L','i','b','r','a','r','y','A',0};
	//typedef HMODULE(WINAPI* x_LoadLibraryA)(_In_ LPCSTR lpLibFileName);
	//x_LoadLibraryA f_LoadLibraryA = (x_LoadLibraryA)f_GetProcAddress((HMODULE)getKernel32(), strLoadLibraryA);

	//typedef int(WINAPI* FN_MessageBoxA)(
	//	__in_opt HWND hWnd,
	//	__in_opt LPCSTR lpText,
	//	__in_opt LPCSTR lpCaption,
	//	__in UINT uType);


	//char szUser32[] = { 'U','s','e','r','3','2','.','d','l','l',0 };
	//char szMessageBoxA[] = { 'M','e','s','s','a','g','e','B','o','x','A',0 };
	//FN_MessageBoxA fn_MessageBoxA = (FN_MessageBoxA)f_GetProcAddress(f_LoadLibraryA(szUser32), szMessageBoxA);
	//char szHello[] = { 'H','e','l','l','o','!',0 };
	//char szTip[] = { 'T','i','p',0 };
	//fn_MessageBoxA(NULL, szHello, szTip, MB_OK);

}








