// 14_CreateNamedSharedMemory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

int main()
{
    // Start Write Process
    STARTUPINFO startupInfo_1;
    PROCESS_INFORMATION processInfo_1;
    memset(&startupInfo_1, 0, sizeof(startupInfo_1));
    memset(&processInfo_1, 0, sizeof(processInfo_1));
    startupInfo_1.cb = sizeof(startupInfo_1);
    TCHAR write_process_exe_name[] = TEXT("14_WriteProcess");

    if (CreateProcess(TEXT("D:\\Git\\PersonalRepo\\MultiThreading\\WinAPI\\MultiThreading\\Debug\\14_WriteProcess.exe"),
        write_process_exe_name,
        0, 0, 0, 0, 0, 0,
        &startupInfo_1,
        &processInfo_1) == 0)
    {
        std::cout << "\nERROR::Create 14_WriteProcess failed: " << GetLastError();
    }
    
    // Let the Write Process start
    Sleep(1000);

    // Start Read Process
    STARTUPINFO startupInfo_2;
    PROCESS_INFORMATION processInfo_2;
    memset(&startupInfo_2, 0, sizeof(startupInfo_2));
    memset(&processInfo_2, 0, sizeof(processInfo_2));
    startupInfo_2.cb = sizeof(startupInfo_2);
    TCHAR read_process_exe_name[] = TEXT("14_ReadProcess");

    if (CreateProcess(TEXT("D:\\Git\\PersonalRepo\\MultiThreading\\WinAPI\\MultiThreading\\Debug\\14_ReadProcess.exe"),
        read_process_exe_name,
        0, 0, 0, 0, 0, 0,
        &startupInfo_2,
        &processInfo_2) == 0)
    {
        std::cout << "\nERROR::Create 14_ReadProcess failed: " << GetLastError();
    }

    // Wait/Close Write Process 
    WaitForSingleObject(processInfo_1.hProcess, INFINITE);
    CloseHandle(processInfo_1.hProcess);
    CloseHandle(processInfo_1.hThread);

    // Wait/Close Read Process 
    WaitForSingleObject(processInfo_2.hProcess, INFINITE);
    CloseHandle(processInfo_2.hProcess);
    CloseHandle(processInfo_2.hThread);

    std::cout << "\n";
    system("pause");
    return 0;
}