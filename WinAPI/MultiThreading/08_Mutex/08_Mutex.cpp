// 08_Mutex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------------------

HANDLE g_mutex_handle;

//-----------------------------------------------------------------------------

DWORD WINAPI thread_function(LPVOID lpParameter)
{
    for (unsigned int iter = 0; iter < 20; ++iter)
    {
        // Waiting infinitely for the mutex to unlock
        WaitForSingleObject(g_mutex_handle, INFINITE);

        std::cout << "\nThread ID: " << GetCurrentThreadId()
            << " thread_function executing smth.";

        ReleaseMutex(g_mutex_handle);
    }

    return 0;
}

//-----------------------------------------------------------------------------

int main()
{
    g_mutex_handle = CreateMutex(0, 0, 0);

    HANDLE thread_array[2];
    thread_array[0] = CreateThread(0, 0, thread_function, 0, 0, 0);
    thread_array[1] = CreateThread(0, 0, thread_function, 0, 0, 0);

    WaitForMultipleObjects(2, thread_array, true, INFINITE);

    CloseHandle(thread_array[0]);
    CloseHandle(thread_array[1]);

    CloseHandle(g_mutex_handle);

    system("pause");
    return 0;
}