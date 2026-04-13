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

#include <string>
#include <vector>

#include "GameWindow.h"

namespace
{
    std::string narrowWideArg(const std::wstring& wideArg)
    {
        if (wideArg.empty())
        {
            return "";
        }

        const int requiredSize = WideCharToMultiByte(CP_UTF8, 0, wideArg.c_str(), -1, nullptr, 0, nullptr, nullptr);

        if (requiredSize <= 0)
        {
            return "";
        }

        std::string result(size_t(requiredSize - 1), '\0');
        WideCharToMultiByte(CP_UTF8, 0, wideArg.c_str(), -1, result.data(), requiredSize, nullptr, nullptr);

        return result;
    }
}

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nCmdShow);

    std::vector<std::string> args;
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if (argv != nullptr)
    {
        for (int index = 1; index < argc; index++)
        {
            const std::wstring wideArg(argv[index]);
            args.push_back(narrowWideArg(wideArg));
        }

        LocalFree(argv);
    }

    GameWindow::configureOffsetLabAutomationOptionsFromArgs(args);

    // run game
    GameWindow app;
    return cocos2d::Application::getInstance()->run();
}
