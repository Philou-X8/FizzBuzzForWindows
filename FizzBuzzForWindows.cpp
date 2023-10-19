
#include <Windows.h>

#define FILE_BUFFER_SIZE 1024
#define MAX_N 100

void main()
{
    CHAR szFizz[MAX_PATH] = { 0 };
    strcpy_s(szFizz, MAX_PATH, "Fizz");
    CHAR szBuzz[MAX_PATH] = { 0 };
    strcpy_s(szBuzz, MAX_PATH, "Buzz");

    CHAR szFileContent[FILE_BUFFER_SIZE] = { 0 };
    DWORD dwFileContentSize = FILE_BUFFER_SIZE;
    DWORD dwItter = 1;
    for (dwItter; dwItter <= MAX_N; ++dwItter)
    {
        CHAR szNumberBuffer[MAX_PATH] = { 0 };
        BOOL bIsMultiple = FALSE;
        if ((dwItter % 3) == 0)
        {
            bIsMultiple = TRUE;
            strcat_s(szNumberBuffer, MAX_PATH, szFizz);
        }
        if ((dwItter % 5) == 0)
        {
            bIsMultiple = TRUE;
            strcat_s(szNumberBuffer, MAX_PATH, szBuzz);
        }
        if (bIsMultiple == FALSE)
        {
            _itoa_s(dwItter, szNumberBuffer, 10);
        }
        strcat_s(szNumberBuffer, MAX_PATH, "\r\n");

        strcat_s(szFileContent, FILE_BUFFER_SIZE, szNumberBuffer);
    }
    dwFileContentSize = (DWORD)strlen(szFileContent);

    HANDLE hFile = GetStdHandle(STD_OUTPUT_HANDLE);
    BOOL ret = FALSE;
    ret = WriteConsoleA(hFile, szFileContent, dwFileContentSize, NULL, NULL);
    if (ret == FALSE) {
        for(DWORD dwWait = 0; (GetLastError() == ERROR_IO_PENDING) && (dwWait < 1000); ++dwWait) Sleep(10);
        
        CloseHandle(hFile);
        return;
    }

    CloseHandle(hFile);
    return;
}
