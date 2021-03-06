// 12_Future_Promise.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>

//-----------------------------------------------------------------------------

#include <thread>
#include <mutex>
#include <future>

//-----------------------------------------------------------------------------

std::mutex g_io_mutex;

//-----------------------------------------------------------------------------

void thread_function(std::promise<std::string>* promise)
{
    Sleep(1000);

   std::cout << "\nThread " << std::this_thread::get_id() << " started setting data to promise";
   promise->set_value("Some data");
}

//-----------------------------------------------------------------------------

int main()
{
    std::cout << "\nMain thread START";

    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();
        
    std::thread thread(thread_function, &promise);

    // Wait until data is set in another thread
    std::cout << "\nMain thread waits for data to be set until it gets: " << future.get();

    // Detaching first thread
    if (thread.joinable())
        thread.join();

    std::cout << "\nMain thread END\n";

    std::system("pause");
    return 0;
}
