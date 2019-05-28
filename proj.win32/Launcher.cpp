/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <combaseapi.h>

#include <atomic>
#include <map>
#include <string>
#include <thread>

#include "client/windows/crash_generation/crash_generation_server.h"
#include "common/windows/guid_string.h"
#include "common/windows/http_upload.h"

#include "Config.h"

namespace
{
    std::atomic_bool gameCrashed = false;

    void onClientConnectedCallback(void* context, const google_breakpad::ClientInfo* client_info)
    {
        UNREFERENCED_PARAMETER(context);
        UNREFERENCED_PARAMETER(client_info);
    }

    void onClientDumpRequestCallback(void* context, const google_breakpad::ClientInfo* client_info,
            const std::wstring* file_path)
    {
        UNREFERENCED_PARAMETER(client_info);

        gameCrashed = true;

        // game has crashed.
        DWORD mainThreadId = *reinterpret_cast<DWORD*>(context);
        std::wstring crashDumpPath = *file_path;
        std::thread([mainThreadId, crashDumpPath] ()
        {
            const std::wstring& text = L"Squally has destroyed the simulation, oh dear.\n\n"
                L"If this was caused by editing assembly, ignore this. Otherwise, will you submit a bug"
                " report to keep this from happening again?";

            // If user denies crash report, exit launcher now
            if (MessageBox(nullptr, text.c_str(), L"Squally Launcher", MB_YESNO | MB_ICONERROR) != IDYES)
            {
                PostThreadMessage(mainThreadId, WM_QUIT, 0, 0);
                return;
            }

            // get os version
            OSVERSIONINFO info{};
            info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
            GetVersionEx(&info);

            // construct crash dump parameters
            std::map<std::wstring, std::wstring> parameters = {
                { L"app-version", std::to_wstring(VERSION_MAJOR) + L"." + std::to_wstring(VERSION_MINOR) + L"."
                    + std::to_wstring(VERSION_PATCH) },
                { L"platform-version", std::to_wstring(info.dwMajorVersion) + L"."
                    + std::to_wstring(info.dwMinorVersion) + L"." + std::to_wstring(info.dwBuildNumber) },
                { L"platform", L"windows" },
                { L"report", L"implement me (without mfc)" }
            };

            std::map<std::wstring, std::wstring> files = {
                { L"minidump", crashDumpPath }
            };

            // send the crash dump
            std::wstring response;
            int responseCode;
            google_breakpad::HTTPUpload::SendRequest(L"https://squallygame.com/api/v1/crashreport", parameters, files,
                    nullptr, &response, &responseCode);
            PostThreadMessage(mainThreadId, WM_QUIT, 0, 0);
        }).detach();
    }

    void onClientExitedCallback(void* context, const google_breakpad::ClientInfo* client_info)
    {
        UNREFERENCED_PARAMETER(client_info);

        // if the game has not crashed, exit the launcher now
        DWORD mainThreadId = *reinterpret_cast<DWORD*>(context);
        if (!gameCrashed)
        {
            PostThreadMessage(mainThreadId, WM_QUIT, 0, 0);
        }
    }
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // get a temporary path for dumps
    TCHAR tempPath[MAX_PATH];
    if (!GetTempPath(MAX_PATH, tempPath))
    {
        OutputDebugString(L"error: failed to get temporary path");
        return 1;
    }

    // create a guid for use as a pipe name
    GUID guid_;
    if (CoCreateGuid(&guid_) != RPC_S_OK)
    {
        OutputDebugString(L"error: failed to get guid");
        return 1;
    }

    // start crash dump server
    DWORD mainThreadId = GetCurrentThreadId();
    std::wstring pipeName = L"\\\\.\\pipe\\" + google_breakpad::GUIDString::GUIDToWString(&guid_);
    google_breakpad::CrashGenerationServer server(pipeName, nullptr, onClientConnectedCallback, &mainThreadId,
            onClientDumpRequestCallback, &mainThreadId, onClientExitedCallback, &mainThreadId, nullptr,
            nullptr, true, &std::wstring(tempPath));
    if (!server.Start())
    {
        OutputDebugString(L"error: failed to start debug server");
        return 1;
    }

    // compute path of squally executable
    TCHAR moduleName[MAX_PATH];
    if (!GetModuleFileName(nullptr, moduleName, MAX_PATH))
    {
        OutputDebugString(L"error: could not get module file name.");
        return 1;
    }

    std::wstring modulePath = moduleName;
    std::size_t pos = modulePath.find_last_of(L'\\');
    if (pos == std::wstring::npos)
    {
        OutputDebugString(L"error: malformed module path?");
        return 1;
    }

    // construct command line arguments
    std::wstring gamePath = modulePath.substr(0, pos + 1) + L"Squally.exe";
    std::wstring commandLine = L"\"" + gamePath + L"\" /p:" + pipeName;

    // spawn squally executable
    STARTUPINFO startupInfo{};
    PROCESS_INFORMATION processInfo{};
    if (!CreateProcess(gamePath.c_str(), &commandLine[0], nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo,
            &processInfo))
    {
        OutputDebugString(L"error: failed to start game modules");
        return 1;
    }

    // clean up handles to child process
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    // Run windows event loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
