// 10_LockGuard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <iostream>
#include <windows.h>
#include <iomanip>

//-----------------------------------------------------------------------------

#include <thread>
#include <mutex>

//-----------------------------------------------------------------------------

std::mutex io_mutex;

//-----------------------------------------------------------------------------

void thread_function()
{
    for (unsigned iter = 0; iter < 50; ++iter)
    {
        std::lock_guard<std::mutex> lock(io_mutex);
        std::cout << "\nThread: " << std::this_thread::get_id() << " is doing some work";
    }
}

//-----------------------------------------------------------------------------

int main()
{
    std::cout << "\nMain thread START";

    std::thread thread_1(thread_function);
    std::thread thread_2(thread_function);

    // Let the thread do some work
    Sleep(1);

    // Detaching first thread
    if (thread_1.joinable())
        thread_1.detach();

    // Waiting for the first thread to finish
    if (thread_2.joinable())
        thread_2.join();

    {
        std::lock_guard<std::mutex> lock(io_mutex);
        std::cout << "\nMain thread END\n";
    }

    std::system("pause");
    return 0;
}
