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

#ifndef __cocos2d_libs__CCCustomEvent__
#define __cocos2d_libs__CCCustomEvent__

#include <string>
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/** @class EventCustom
 * @brief Custom event.
 */
class CC_DLL EventCustom : public Ref
{
public:
    /** Constructor.
     *
     * @param eventName A given name of the custom event.
     * @js ctor
     */
    EventCustom(const std::string& eventName, void* data = nullptr);
    
    /** Sets user data.
     *
     * @param data The user data pointer, it's a void*.
     */
    void setData(void* data) { this->data = data; }
    
    /** Gets user data.
     *
     * @return The user data pointer, it's a void*.
     */
    void* getData() const { return this->data; }
    
    /** Gets event name.
     *
     * @return The name of the event.
     */
    const std::string& getEventName() const { return this->eventName; }

    void stopPropagation() { this->propagationStopped = true; }

    bool isPropagationStopped() const { return this->propagationStopped; }
    
protected:
    void* data;
    std::string eventName;
    bool propagationStopped;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCCustomEvent__) */
