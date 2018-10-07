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

#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "client/linux/handler/exception_handler.h"
#include "GameWindow.h"

namespace
{
    class CrashHandler
    {
        google_breakpad::ExceptionHandler exceptionHandler;

        static bool onException(const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded)
        {
            CrashHandler* handler = reinterpret_cast<CrashHandler*>(context);
            std::cerr << "[game] produced crash dump: " << succeeded << std::endl;
            return succeeded;
        }

    public:
        CrashHandler(int serverDescriptor)
            : exceptionHandler(google_breakpad::MinidumpDescriptor(), nullptr, &CrashHandler::onException, nullptr,
            true, serverDescriptor)
        {
        }
    };
}

int main(int argc, char **argv)
{
    // enable crash handling if we were provided a server descriptor
    std::unique_ptr<CrashHandler> handler;
    if (argc >= 3
        && std::string(argv[1]) == "-d"
        && std::string(argv[2]).size() > 0)
    {
        handler.reset(new CrashHandler(std::stoi(argv[2])));
    }

    // run game
    GameWindow app;
    return cocos2d::Application::getInstance()->run();
}