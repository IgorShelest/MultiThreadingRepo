// 16_Thread_monitoring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>

//-----------------------------------------------------------------------------

HANDLE g_event_handle;
HANDLE g_io_mutex_handle;


//-----------------------------------------------------------------------------

DWORD WINAPI thread_1_function(LPVOID)
{
    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " START";
    ReleaseMutex(g_io_mutex_handle);

    while (WaitForSingleObject(g_event_handle, 1000) == WAIT_TIMEOUT)
    {
        WaitForSingleObject(g_io_mutex_handle, INFINITE);
        std::cout << "\nThread ID: " << GetCurrentThreadId() << " working...";
        ReleaseMutex(g_io_mutex_handle);
    }

    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " END";
    ReleaseMutex(g_io_mutex_handle);

    return 0;
};

//-----------------------------------------------------------------------------

DWORD WINAPI thread_2_function(LPVOID)
{
    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " START";
    ReleaseMutex(g_io_mutex_handle);

    while (WaitForSingleObject(g_event_handle, 1000) == WAIT_TIMEOUT)
    {
        WaitForSingleObject(g_io_mutex_handle, INFINITE);
        std::cout << "\nThread ID: " << GetCurrentThreadId() << " working...";
        ReleaseMutex(g_io_mutex_handle);
    }

    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " END";
    ReleaseMutex(g_io_mutex_handle);

    return 0;
};

//-----------------------------------------------------------------------------

DWORD WINAPI main_thread_function(LPVOID)
{
    const unsigned int thread_amount = 2;
    HANDLE thread_array[thread_amount];

    // Start daughter threads
    thread_array[0] = CreateThread(0, 0, thread_1_function, 0, 0, 0);
    thread_array[1] = CreateThread(0, 0, thread_2_function, 0, 0, 0);

    DWORD thread_1_ExitCode = 0, thread_2_ExitCode = 0;
    const int terminate_timer = 500;

    // Daughter thread are being monitored to be restarted
    while (WaitForSingleObject(g_event_handle, 1000) == WAIT_TIMEOUT)
    {
        if (GetExitCodeThread(thread_array[0], &thread_1_ExitCode) && thread_1_ExitCode != STILL_ACTIVE)
        {
            std::cout << "Thread: " << GetThreadId(thread_array[0]) << " out with code: " << thread_1_ExitCode << ". Restarting it!";
            CloseHandle(thread_array[0]);
            thread_array[0] = CreateThread(NULL, 0, thread_1_function, NULL, 0, NULL);
        }

        if (GetExitCodeThread(thread_array[1], &thread_2_ExitCode) && thread_2_ExitCode != STILL_ACTIVE)
        {
            std::cout << "Thread: " << GetThreadId(thread_array[1]) << " out with code: " << thread_2_ExitCode << ". Restarting it!";
            CloseHandle(thread_array[1]);
            thread_array[1] = CreateThread(NULL, 0, thread_2_function, NULL, 0, NULL);
        }
    }    

    // Terminate thread in case it hanged 
    if (WaitForSingleObject(thread_array[0], terminate_timer) == WAIT_TIMEOUT)
    {
        TerminateThread(thread_array[0], -1);
    }

    // Terminate thread in case it hanged 
    if (WaitForSingleObject(thread_array[1], terminate_timer) == WAIT_TIMEOUT)
    {
        TerminateThread(thread_array[1], -1);
    }

    GetExitCodeThread(thread_array[0], &thread_1_ExitCode);
    GetExitCodeThread(thread_array[1], &thread_2_ExitCode);

    if (thread_array[0]) CloseHandle(thread_array[0]);
    if (thread_array[1]) CloseHandle(thread_array[1]);

    return 0;
};


//-----------------------------------------------------------------------------

int main()
{
    // Create mutex for io
    g_io_mutex_handle = CreateMutex(0, 0, 0);

    // Create Event
    g_event_handle = CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is non-signaled
        TEXT("WriteEvent")  // object name
    );
    
    HANDLE main_thread = CreateThread(0, 0, main_thread_function, 0, 0, 0);

    // Let threads do some work
    Sleep(3000);

    // Set Event
    SetEvent(g_event_handle);
    
    CloseHandle(main_thread);
    CloseHandle(g_event_handle);
    CloseHandle(g_io_mutex_handle);

    std::cout << "\n";
    system("pause");
    return 0;
}
