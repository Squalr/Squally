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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

#include "platform/CCPlatformMacros.h"
#include "base/CCEventListener.h"
#include "platform/CCStdC.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class Node;
class EventCustom;
class EventListenerCustom;

/** @class EventDispatcher
* @brief This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
@js NA
*/
class CC_DLL EventDispatcher : public Ref
{
public:
    /** Constructor of EventDispatcher.
     */
    EventDispatcher();
    /** Destructor of EventDispatcher.
     */
    ~EventDispatcher();
    
    /** Adds an event listener
     */
    void addEventListener(EventListenerCustom* listener);
    
    /** Dispatches a Custom Event with a event name an optional user data.
     *
     * @param eventName The name of the event which needs to be dispatched.
     * @param optionalUserData The optional user data, it's a void*, the default value is nullptr.
     */
    void dispatchEvent(const std::string &eventName, void *optionalUserData = nullptr);
    
    /** Dispatches a Custom Event.
     *
     */
    void dispatchEvent(EventCustom* event);
    
    /** Remove a listener.
     *
     *  @param listener The specified event listener which needs to be removed.
     */
    void removeEventListener(EventListenerCustom* listener);

    /** Removes all listeners.
     */
    void removeAllEventListeners();

private:
    void processAddForEvent(const std::string& eventName);
    void processRemoveForEvent(const std::string& eventName);
    void scheduleSlowClean();
    void slowCleanNext();

    std::unordered_map<std::string, std::set<EventListenerCustom*>> listenerMap;

    // Assisting data structures for adding/removing events without disrupting iterators
    std::unordered_map<std::string, std::set<EventListenerCustom*>> toRemove;
    std::unordered_map<std::string, std::vector<EventListenerCustom*>> toAdd;
};

NS_CC_END

// end of base group
/// @}

#endif // __CC_EVENT_DISPATCHER_H__
