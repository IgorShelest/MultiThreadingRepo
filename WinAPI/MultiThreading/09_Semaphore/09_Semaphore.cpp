// 09_Semaphore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------------------

HANDLE g_semaphore_handle;

//-----------------------------------------------------------------------------

DWORD WINAPI thread_function(LPVOID lpParameter)
{
    WaitForSingleObject(g_semaphore_handle, INFINITE);

    for (unsigned int iter = 0; iter < 20; ++iter)
    {
        std::cout << "\nThread ID: " << GetCurrentThreadId()
            << " thread_function executing smth.";
    }

    ReleaseSemaphore(g_semaphore_handle, 1, 0);

    return 0;
}

//-----------------------------------------------------------------------------

int main()
{
    // Create Semaphore for 2 active threads
    const unsigned int initial_count = 2;
    const unsigned int max_count = 2;

    // 2 threads will be allowed to be executed at once
    g_semaphore_handle = CreateSemaphore(0, initial_count, max_count, 0);

    HANDLE thread_array[2];
    thread_array[0] = CreateThread(0, 0, thread_function, 0, 0, 0);
    thread_array[1] = CreateThread(0, 0, thread_function, 0, 0, 0);

    WaitForMultipleObjects(2, thread_array, true, INFINITE);

    CloseHandle(thread_array[0]);
    CloseHandle(thread_array[1]);

    CloseHandle(g_semaphore_handle);

    system("pause");
    return 0;
}