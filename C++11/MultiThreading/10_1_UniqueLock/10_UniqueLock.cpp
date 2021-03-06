// 10_1_UniqueLock.cpp : Defines the entry point for the console application.
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
        std::unique_lock<std::mutex> unique_lock(io_mutex);
        std::cout << "\nThread: " << std::this_thread::get_id() << " starts to do some work";

        if (iter % 2)
        {
            std::cout << "\nThread: " << std::this_thread::get_id() << "\n unlocks unique_lock";
            unique_lock.unlock();
            
            Sleep(10);

            unique_lock.lock();
            std::cout << "\nThread: " << std::this_thread::get_id() << "\n locks unique_lock again";
        }

        std::cout << "\nThread: " << std::this_thread::get_id() << " continues to do some work";
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
