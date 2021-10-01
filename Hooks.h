#include "pch.h"
#include "Minhook/MinHook.h"
#include "Memory.h"
#include "Define.h"
#include <iostream>
#include "Util.h"
#pragma comment (lib, "Minhook/libMinHook.x64.lib")

#pragma once



namespace Hooks {

    PBYTE ExitAddress;

    typedef void* (__fastcall* fExitBypass)(__int64 arg1);
    typedef void* (__fastcall* fCrashBypass)(__int64 arg1, __int64 arg2);
    typedef void* (__fastcall* fRequestExit)(unsigned __int8 arg1, unsigned __int8 arg2);
    typedef void* (__fastcall* fNotiBypass)(wchar_t** arg1, unsigned __int8 arg2, __int64 arg3, char arg4);
    fExitBypass ExitBypass;
    fCrashBypass CrashBypass;
    fRequestExit RequestExitBypass;
    fNotiBypass NotiBypass;


    // Hooks Terminate Process
    void* __fastcall ExitBypassHook(__int64 a1)
    {
        return NULL;
    }

    // Hooks UnrealCrash
    void* __fastcall CrashHook(__int64 a1, __int64 a2)
    {
        return NULL;
    }

    // Hooks RequestExit
    void* __fastcall RequestExitBypassHook(unsigned __int8 a1, unsigned __int8 a2)
    {
        return NULL;
    }

    // Hooks Unreal Notification
    void* __fastcall NotificationHook(wchar_t** a1, unsigned __int8 a2, __int64 a3, char a4)
    {
        return NULL;
    }


    static void InitHook()
    {
        Utils::Log("Initializing Hooks...");
        auto ExitAddress = Memory::FindPattern(ExitSig);
        auto NotificationHookAddress = Memory::FindPattern(Notification);
        auto FNCrashHookAddress = Memory::FindPattern(FNCrashHook);
        auto RequestExitAddress = Memory::FindPattern(RequestExit);

        Utils::Verify(ExitAddress, "ExitAddress");
        Utils::Verify(NotificationHookAddress, "NotificationHookAddress");
        Utils::Verify(FNCrashHookAddress, "FNCrashHookAddress");
        Utils::Verify(RequestExitAddress, "RequestExitAddress");


        MH_Initialize();
        MH_CreateHook(((LPVOID)RequestExitAddress), RequestExitBypassHook, reinterpret_cast<LPVOID*>(&RequestExitBypass));
        MH_EnableHook(((LPVOID)RequestExitAddress));
        MH_CreateHook(((LPVOID)FNCrashHookAddress), CrashHook, reinterpret_cast<LPVOID*>(&CrashBypass));
        MH_CreateHook(((LPVOID)NotificationHookAddress), ExitBypassHook, reinterpret_cast<LPVOID*>(&NotiBypass));
        MH_EnableHook(((LPVOID)NotificationHookAddress));
        MH_CreateHook(((LPVOID)ExitAddress), ExitBypassHook, reinterpret_cast<LPVOID*>(&ExitBypass));
        MH_EnableHook(((LPVOID)ExitAddress));
    }

}

