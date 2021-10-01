#include "pch.h" 
#include "Util.h"
#include "Hooks.h"

    BOOL APIENTRY DllMain(HMODULE hModule,
        DWORD  ul_reason_for_call,
        LPVOID lpReserved
    )
    {
        switch (ul_reason_for_call)
        {
        case DLL_PROCESS_ATTACH:
            Utils::FreeConsole();
            UnrealNotification::InitHook();
            break;
        }
        return TRUE;
    }

