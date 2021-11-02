#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <cstring>

DWORD WINAPI showMsg(LPVOID targetModuleName) {
    if (!targetModuleName) {
        MessageBoxA(NULL, "Please set 'targetModuleName'!", "ERROR", MB_YESNO);
        return ~0;
    }

    char nameBuf[MAX_PATH];
    char msgBuf[MAX_PATH + 0x100];

    GetModuleFileNameA(GetModuleHandleA((LPCSTR)targetModuleName), nameBuf, MAX_PATH);
    FARPROC GetThreadIdStrAddr = GetProcAddress(GetModuleHandleA("kernel32"), "GetCurrentThreadId");
    DWORD threadId = GetThreadIdStrAddr();

    snprintf(msgBuf, MAX_PATH + 0xFF, "%s; id=%u", nameBuf, threadId);

    MessageBoxA(NULL, msgBuf, "Message", MB_YESNO);
    return 0;
}

char dllName[] = "kernel32.dll";

int main()
{
    HANDLE msgThreadHandle = CreateThread(NULL, 0, showMsg, dllName, 0, NULL);
    WaitForSingleObject(msgThreadHandle, INFINITE);
    return 0;
}
