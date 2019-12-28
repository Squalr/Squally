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

#include "main.h"
#include "GameWindow.h"

#include "client/windows/handler/exception_handler.h"

namespace
{
    class CrashHandler
    {
        google_breakpad::ExceptionHandler handler;

        static bool onException(const wchar_t* dump_path, const wchar_t* minidump_id, void* context,
                EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool succeeded)
        {
            CrashHandler* handler = reinterpret_cast<CrashHandler*>(context);
            OutputDebugStringW(dump_path);
            return succeeded;
        }

    public:
        CrashHandler(const std::wstring& pipeName)
            : handler(L"", nullptr, &CrashHandler::onException, this,
                google_breakpad::ExceptionHandler::HANDLER_ALL, MiniDumpNormal, pipeName.c_str(), nullptr)
        {
        }
    };
}

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    // enable crash handling if we were provided a server descriptor
    int wargc = 0;
    LPWSTR* wargv = nullptr;
    std::unique_ptr<CrashHandler> handler;
    if ((wargv = CommandLineToArgvW(lpCmdLine, &wargc)))
    {
        for (int i = 0; i < wargc; i++)
        {
            std::wstring arg(wargv[i]);
            if (!arg.compare(0, 3, L"/p:") && arg.size() > 3)
            {
                handler.reset(new CrashHandler(arg.substr(3)));
                break;
            }
        }
    }

    // run game
    GameWindow app;
    return cocos2d::Application::getInstance()->run();
}
