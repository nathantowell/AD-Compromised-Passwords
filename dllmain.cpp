// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <SubAuth.h>
#include <string>

/* Custom */
#include "sha1.cpp"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Advapi32.lib")

/* Visual Studio Boilerplate */

BOOL APIENTRY DllMain(
        HMODULE hModule,
        DWORD  ul_reason_for_call,
        LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

/* Get API URI from Registry */
LONG GetAPILocation(std::wstring& strValue)
{
    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\AD-CompromisedPasswords", 0, KEY_READ, &hKey);

    if (ERROR_SUCCESS != lRes)
    {
        return lRes;
    }

    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;

    nError = RegQueryValueExW(hKey, L"URI", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);

    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }

    return nError;
}

/* Generate SHA1 Hash from Input String */
CHAR GenerateSHA1()
{
    // TODO
}

extern "C" __declspec(dllexport) BOOLEAN __stdcall PasswordFilter(PUNICODE_STRING AccountName, PUNICODE_STRING FullName, PUNICODE_STRING Password, BOOLEAN SetOperation)
{
    /* Declare Result as TRUE by Default */
    BOOLEAN Result = TRUE;

    /* Get API URI */
    std::wstring APILocation;
    GetAPILocation(APILocation);

    /* Generate Hash and K Anonymity */
    SHA1 Checksum;
    Checksum.update(Password);

    std::wstring Hash = Checksum.final();
    std::wstring Range = Hash.substr(0, 5);

    /* Lookup Range in API */
    //TODO


    /* Clear Password from Memory */
    SecureZeroMemory(Password, sizeof(Password));

    /* Return Result */
    return Result;
}
