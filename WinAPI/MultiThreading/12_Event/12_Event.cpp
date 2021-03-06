// 12_Event.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>

//-----------------------------------------------------------------------------

const unsigned int g_thread_amount = 2;

//-----------------------------------------------------------------------------

HANDLE g_event_handle;
HANDLE g_thread_array[g_thread_amount];
HANDLE g_io_mutex_handle;

//-----------------------------------------------------------------------------

DWORD WINAPI wait_thread_function(LPVOID)
{
    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " starting INFINITE WAIT";
    ReleaseMutex(g_io_mutex_handle);

    WaitForSingleObject(g_event_handle, INFINITE);
    
    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " signaled";
    ReleaseMutex(g_io_mutex_handle);

    return 0;
};

//-----------------------------------------------------------------------------

DWORD WINAPI do_thread_function(LPVOID)
{
    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " starting 1sec WAIT";
    ReleaseMutex(g_io_mutex_handle);

    while (WaitForSingleObject(g_event_handle, 1000) == WAIT_TIMEOUT)
    {
        WaitForSingleObject(g_io_mutex_handle, INFINITE);
        std::cout << "\nThread ID: " << GetCurrentThreadId() << " doing some work while not signaled";
        ReleaseMutex(g_io_mutex_handle);
    }

    WaitForSingleObject(g_io_mutex_handle, INFINITE);
    std::cout << "\nThread ID: " << GetCurrentThreadId() << " signaled";
    ReleaseMutex(g_io_mutex_handle);

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
                            FALSE,              // initial state is nonsignaled
                            TEXT("WriteEvent")  // object name
                        );

    // Start daughter threads
    g_thread_array[0] = CreateThread(0, 0, wait_thread_function, 0, 0, 0);
    g_thread_array[1] = CreateThread(0, 0, do_thread_function, 0, 0, 0);

    // Daughter threads will wait for the Event to be set
    Sleep(3000);

    // Set Event
    SetEvent(g_event_handle);

    WaitForMultipleObjects(2, g_thread_array, true, INFINITE);
    CloseHandle(g_thread_array[0]);
    CloseHandle(g_thread_array[1]);
    
    CloseHandle(g_event_handle);

    std::cout << "\n";
    system("pause");
    return 0;
}

