/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "Engine/UI/Controls/UIHelper.h"

#include "cocos/base/CCConsole.h"
#include "cocos/base/ccUTF8.h"

std::string UIHelper::getSubStringOfUTF8String(const std::string& str, std::string::size_type start, std::string::size_type length)
{
    std::u32string utf32;

    if (!StringUtils::UTF8ToUTF32(str, utf32))
    {
        CCLOGERROR("Can't convert string to UTF-32: %s", str.c_str());
        return "";
    }

    if (utf32.size() < start)
    {
        CCLOGERROR("'start' is out of range: %ld, %s", static_cast<long>(start), str.c_str());
        return "";
    }
    std::string result;
    if (!StringUtils::UTF32ToUTF8(utf32.substr(start, length), result))
    {
        CCLOGERROR("Can't convert internal UTF-32 string to UTF-8: %s", str.c_str());
        return "";
    }
    return result;
}
