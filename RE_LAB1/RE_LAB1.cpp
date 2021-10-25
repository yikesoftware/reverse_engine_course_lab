// RE_LAB1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <cstring>
using namespace std;

char ollydbg_path[] = "D:\\ollydbg2.10_zh-ch\\Ollydbg.exe";

int EnableDebugPriv(const char* name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

    LookupPrivilegeValue(NULL, (LPCWSTR)name, &luid);
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;

    int ret = AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    return ret;
}

int main(int argc, char *argv[])
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!EnableDebugPriv((const char*)SE_DEBUG_NAME)) {
        cout << "* FAIL TO: Get SEDEBUG privilege" << endl;
        return 0;
    }
    else {
        cout << "* SUCCESS TO: Get SEDEBUG privilege" << endl;
    }

    char* startArg = argc > 1 ? argv[1]:NULL;
    if (!CreateProcessA(ollydbg_path, startArg, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi)) {
        std::cout << "Can not open: " << ollydbg_path << std::endl;
    }

}