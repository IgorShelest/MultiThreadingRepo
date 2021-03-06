// 17_Processes_Data_Copy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <sstream>

//-----------------------------------------------------------------------------

static const std::string g_event_name = "StopEvent";
static const std::string g_mutex_name = "SharedMutex";

//-----------------------------------------------------------------------------

int main()
{
    // Convert Event name
    TCHAR* named_event_name = new TCHAR[g_event_name.size() + 1];
    copy(g_event_name.begin(), g_event_name.end(), named_event_name);   // -D_SCL_SECURE_NO_WARNINGS
    named_event_name[g_event_name.size()] = 0;

    // Create named Event
    HANDLE event_handle = CreateEvent(
        NULL,             // default security attributes
        TRUE,             // manual-reset event
        FALSE,            // initial state is non-signaled
        named_event_name  // object name
    );

    // Convert Mutex name
    LPCSTR named_mutex_name = g_mutex_name.c_str();

    // Create named Mutex
    HANDLE mutex_handle = CreateMutexA(0, 0, named_mutex_name);

    // Launch Receiving Process
    STARTUPINFO receive_startupInfo;
    PROCESS_INFORMATION receive_processInfo;
    memset(&receive_startupInfo, 0, sizeof(receive_startupInfo));
    memset(&receive_processInfo, 0, sizeof(receive_processInfo));

    receive_startupInfo.cb = sizeof(receive_startupInfo);

    //TCHAR szPath[] = TEXT("C:\\Users\\igor.shelest\\source\\repos\\ConsoleApplication6\\Debug\\ReceivingProcessEXE.exe \"Bla Bla Bla\"");
    TCHAR receive_szPath[] = TEXT("ReceivingProcessEXE \"Bla Bla Bla\"");

    if (CreateProcess(TEXT("D:\\Git\\PersonalRepo\\MultiThreading\\WinAPI\\MultiThreading\\Debug\\ReceivingProcessEXE.exe"),
        receive_szPath,
        0, 0, 0, 0, 0, 0,
        &receive_startupInfo,
        &receive_processInfo) == 0)
    {
        std::cout << "\nERROR: " << GetLastError();
    }
    
    // Launch Sending Process
    STARTUPINFO send_startupInfo;
    PROCESS_INFORMATION send_processInfo;
    memset(&send_startupInfo, 0, sizeof(send_startupInfo));
    memset(&send_processInfo, 0, sizeof(send_processInfo));

    send_startupInfo.cb = sizeof(send_startupInfo);

    //TCHAR szPath[] = TEXT("C:\\Users\\igor.shelest\\source\\repos\\ConsoleApplication6\\Debug\\SendingProcessEXE.exe \"Bla Bla Bla\"");
    TCHAR send_szPath[] = TEXT("SendingProcessEXE \"Bla Bla Bla\"");

    if (CreateProcess(TEXT("D:\\Git\\PersonalRepo\\MultiThreading\\WinAPI\\MultiThreading\\Debug\\SendingProcessEXE.exe"),
        send_szPath,
        0, 0, 0, 0, 0, 0,
        &send_startupInfo,
        &send_processInfo) == 0)
    {
        std::cout << "\nERROR: " << GetLastError();
    }
        
    // Daughter processes will wait for the Event to be set
    Sleep(6000);

    // Set Event
    SetEvent(event_handle);

    // Wait/Close Waiting Process
    WaitForSingleObject(receive_processInfo.hProcess, INFINITE);
    CloseHandle(receive_processInfo.hProcess);
    CloseHandle(receive_processInfo.hThread);

    // Wait/Close Sending Process
    WaitForSingleObject(send_processInfo.hProcess, INFINITE);
    CloseHandle(send_processInfo.hProcess);
    CloseHandle(send_processInfo.hThread);

    CloseHandle(event_handle);
    CloseHandle(mutex_handle);

    std::system("pause");
    return 0;
}

//-------------------------- ReceivingProcessEXE --------------------------------

//int main(int argc, char* argv[])
//{
//    if (argc >= 1)
//    {
//        std::cout << "\nStarting Receiving Process with [" << argv[1] << "] parameter";
//
//        // Convert event name
//        LPCSTR named_event_name = g_event_name.c_str();
//        HANDLE named_event_handle = OpenEventA(
//                                        EVENT_ALL_ACCESS,    // Desired Access
//                                        TRUE,                // Inherit Handle 
//                                        named_event_name);   // Event Name
//        
//        // Convert mutex name
//        LPCSTR named_mutex_name = g_mutex_name.c_str();
//
//        // Open named Mutex
//        HANDLE named_mutex_handle = OpenMutexA(
//            MUTEX_ALL_ACCESS,    // Desired Access
//            TRUE,                // Inherit Handle 
//            named_mutex_name);   // Event Name
//
//        while (WaitForSingleObject(named_event_handle, 1000) == WAIT_TIMEOUT)
//        {
//            // Waiting infinitely for the mutex to unlock
//            WaitForSingleObject(named_mutex_handle, INFINITE);
//
//            std::cout << "\nWaitng for the message...";
//
//            ReleaseMutex(named_mutex_handle);
//            Sleep(2000);
//        }
//
//        CloseHandle(named_event_handle);
//        CloseHandle(named_mutex_handle);
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

//-------------------------- SendingProcessEXE --------------------------------

//int main(int argc, char* argv[])
//{
//    if (argc >= 1)
//    {
//        std::cout << "\nStarting Sending Process with [" << argv[1] << "] parameter";
//        
//        // Convert event name
//        LPCSTR named_event_name = g_event_name.c_str();
//        HANDLE named_event_handle = OpenEventA(
//                                        EVENT_ALL_ACCESS,    // Desired Access
//                                        TRUE,                // Inherit Handle 
//                                        named_event_name);   // Event Name
//
//        // Convert mutex name
//        LPCSTR named_mutex_name = g_mutex_name.c_str();
//
//        // Open named Mutex
//        HANDLE named_mutex_handle = OpenMutexA(
//            MUTEX_ALL_ACCESS,    // Desired Access
//            TRUE,                // Inherit Handle 
//            named_mutex_name);   // Event Name
//
//        while (WaitForSingleObject(named_event_handle, 1000) == WAIT_TIMEOUT)
//        {
//            // Waiting infinitely for the mutex to unlock
//            WaitForSingleObject(named_mutex_handle, INFINITE);
//
//            std::cout << "\nSending message...";
//
//            ReleaseMutex(named_mutex_handle);
//            Sleep(2000);
//        }
//
//        CloseHandle(named_event_handle);
//        CloseHandle(named_mutex_handle);
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