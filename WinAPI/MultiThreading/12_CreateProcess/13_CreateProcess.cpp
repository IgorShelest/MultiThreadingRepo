// 12_CreateProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <sstream>

//-----------------------------------------------------------------------------

int main()
{
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    memset(&startupInfo, 0, sizeof(startupInfo));
    memset(&processInfo, 0, sizeof(processInfo));

    startupInfo.cb = sizeof(startupInfo);

    //TCHAR szPath[] = TEXT("C:\\Users\\igor.shelest\\source\\repos\\ConsoleApplication6\\Debug\\PrintArgumentEXE.exe \"Bla Bla Bla\"");
    TCHAR szPath[] = TEXT("PrintArgumentEXE \"Bla Bla Bla\"");

    if (CreateProcess(TEXT("C:\\Users\\igor.shelest\\source\\repos\\ConsoleApplication6\\Debug\\PrintArgumentEXE.exe"),
        szPath,
        0, 0, 0, 0, 0, 0,
        &startupInfo,
        &processInfo) == 0)
    {
        std::cout << "\nERROR: " << GetLastError();
    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    
    std::cout << "\n";
    system("pause");
    return 0;
}

//--------------------------  PrintArgumentEXE --------------------------------

//int main(int argc, char* argv[])
//{
//    if (argc >= 1)
//    {
//        std::cout << "\nStarting Exe with " << argv[1] << " parameter";
//    }
//    else
//    {
//        std::cout << "\nNo arguments where passed";
//    }
//
//    std::cout << "\n";
//    system("pause");
//    return 0;
//}
