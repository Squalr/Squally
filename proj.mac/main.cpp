/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
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

#include "client/mac/handler/exception_handler.h"
#include "client/mac/crash_generation/crash_generation_client.h"

#include <memory>
#include <string>

#include "GameWindow.h"

namespace
{
    // wrapper for crash handling logic
    class CrashHandler
    {
        google_breakpad::ExceptionHandler exceptionHandler;
        google_breakpad::CrashGenerationClient client;

        // called when the game encounters an exception
        static bool onException(void *context, int exception_type, int exception_code,
                int exception_subcode, mach_port_t thread_name)
        {
            CrashHandler* handler = reinterpret_cast<CrashHandler*>(context);
            handler->client.RequestDumpForException(exception_type, exception_code,
                    exception_subcode, thread_name);
            return true;
        }

    public:
        CrashHandler(const std::string& portName)
            : exceptionHandler(&CrashHandler::onException, this, true),
            client(portName.c_str())
        {
        }
    };
}

int main(int argc, char *argv[])
{
    // enable crash handling if we were provided a port name
    std::unique_ptr<CrashHandler> handler;
    if (argc >= 3
        && std::string(argv[1]) == "-d"
        && std::string(argv[2]).size() > 0)
    {
        handler.reset(new CrashHandler(argv[2]));
    }

    // run game
    GameWindow app;
    return cocos2d::Application::getInstance()->run();
}