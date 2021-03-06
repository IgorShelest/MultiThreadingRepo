// 06_PassingArguments_by_reference_into_Thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <thread>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <sstream>

//-----------------------------------------------------------------------------

void thread_function(int counter, std::string& data)
{
    std::ostringstream sstream;
    sstream << std::this_thread::get_id();
    const std::string thread_id = sstream.str();

    for (unsigned iter = 0; iter < counter; ++iter)
    {
        std::cout << "\nThread: " << thread_id << " is working on data: " << data;
    }

    data.append("+" + thread_id);
}

//-----------------------------------------------------------------------------

int main()
{
    std::cout << "\nMain thread START";

    const unsigned counter = 10;
    std::string data = "Some Data";

    std::thread thread_1(thread_function, counter, std::ref(data));
    std::thread thread_2(thread_function, counter, std::ref(data));

    // Let the thread do some work
    Sleep(1);

    // Detaching first thread
    if (thread_1.joinable())
        // Can be detached since std::ref(data)
        thread_1.detach();      

    // Detaching second thread
    if (thread_2.joinable())
        // Can be detached since std::ref(data)
        thread_2.detach();      

    std::cout << "\nAfter threads execution"
        << "\ndata: " << data;

    std::cout << "\nMain thread END\n";

    std::system("pause");
    return 0;
}
