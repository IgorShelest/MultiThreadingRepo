// 09_Mutex_lock_unlock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <thread>
#include <mutex>
#include <iostream>
#include <windows.h>
#include <iomanip>

//-----------------------------------------------------------------------------

std::mutex io_mutex;

//-----------------------------------------------------------------------------

void thread_function()
{
    for (unsigned iter = 0; iter < 50; ++iter)
    {
        io_mutex.lock();
        std::cout << "\nThread: " << std::this_thread::get_id() << " is doing some work";
        io_mutex.unlock();
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

    io_mutex.lock();
    std::cout << "\nMain thread END\n";
    io_mutex.unlock();

    std::system("pause");
    return 0;
}
