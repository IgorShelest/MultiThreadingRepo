// 03_CreateThread_JoineMultiple.cpp : Defines the entry point for the console application.
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
    HANDLE thread_array[2];

    thread_array[0] = CreateThread(0, 0, thread_function, 0, 0, 0);
    thread_array[1] = CreateThread(0, 0, thread_function, 0, 0, 0);

    // Joining threads (waiting for the threads to finish)
    WaitForMultipleObjects(2, thread_array, true, INFINITE);

    // Closing Handles
    CloseHandle(thread_array[0]);
    CloseHandle(thread_array[1]);

    system("pause");
    return 0;
}