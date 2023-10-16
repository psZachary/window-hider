#include <Windows.h>
#include <iostream>
#include <vector>

std::vector<HWND> windows = std::vector<HWND>();

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
    if (pid == GetCurrentProcessId()) {
        windows.push_back(hwnd);
	}
	return TRUE;
}

BOOL GetAllWindowsOfCurrentApplication() {
    return EnumWindows(EnumWindowsProc, NULL);
}

void MainThread(LPVOID lpThreadParameter) {
    HMODULE hModule = (HMODULE)lpThreadParameter;
    GetAllWindowsOfCurrentApplication();
    for (HWND hwnd : windows) {
        SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);
    }
    Sleep(100);
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, (LPVOID)hModule, NULL, NULL);
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

