// 18_1_Transactions_on_Named_Pipes_Client_via_CallNamedPipe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------------------------

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <strsafe.h>
#include <conio.h>

//-----------------------------------------------------------------------------

#define BUFSIZE 512

//-----------------------------------------------------------------------------

int main(int argc, TCHAR *argv[])
{
    LPTSTR lpszWrite = TEXT("Default message from client");
    TCHAR chReadBuf[BUFSIZE];
    BOOL fSuccess;
    DWORD cbRead;
    LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

    if (argc > 1)
    {
        lpszWrite = argv[1];
    }

    fSuccess = CallNamedPipe(
        lpszPipename,        // pipe name 
        lpszWrite,           // message to server 
        (lstrlen(lpszWrite) + 1) * sizeof(TCHAR), // message length 
        chReadBuf,              // buffer to receive reply 
        BUFSIZE * sizeof(TCHAR),  // size of read buffer 
        &cbRead,                // number of bytes read 
        20000);                 // waits for 20 seconds 

    if (fSuccess || GetLastError() == ERROR_MORE_DATA)
    {
        _tprintf(TEXT("%s\n"), chReadBuf);

        // The pipe is closed; no more data can be read. 

        if (!fSuccess)
        {
            printf("\nExtra data in message was lost\n");
        }
    }

    _getch();

    return 0;
}

