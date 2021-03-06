// 01_CreateThread_Detached.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------------------

DWORD WINAPI thread_function(LPVOID lpParameter)
{
    for (unsigned int iter = 0; iter < 20; ++iter)
        std::cout << "\nthread_function executing smth.";

    return 0;
}

//-----------------------------------------------------------------------------

int main()
{
    HANDLE thread_handle = CreateThread(0, 0, thread_function, 0, 0, 0);

    // Detaching thread (not waiting for the thread to finish)
    // WaitForSingleObject(thread_handle, INFINITE);

    // Close Handle
    CloseHandle(thread_handle);

    std::cout << "\n";
    system("pause");
    return 0;
}

