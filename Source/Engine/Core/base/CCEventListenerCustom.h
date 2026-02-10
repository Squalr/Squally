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

#ifndef __cocos2d_libs__CCCustomEventListener__
#define __cocos2d_libs__CCCustomEventListener__

#include "base/CCEventListener.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class EventCustom;

/** @class EventListenerCustom
 * @brief Custom event listener.
 * @code Usage:
 *        auto dispatcher = Director::getInstance()->getEventDispatcher();
 *     Adds a listener:
 *
 *        auto callback = [](EventCustom* event){ do_some_thing(); };
 *        auto listener = EventListenerCustom::create(callback);
 *        dispatcher->addEventListener(listener, one_node);
 *
 *     Dispatches a custom event:
 *
 *        EventCustom event("your_event_type");
 *        dispatcher->dispatchEvent(&event);
 *
 *     Removes a listener
 *
 *        dispatcher->removeEventListener(listener);
 * \endcode
 * @js cc._EventListenerCustom
 */
class CC_DLL EventListenerCustom : public EventListener
{
public:
    /** Creates an event listener with type and callback.
     * @param eventName The type of the event.
     * @param callback The callback function when the specified event was emitted.
     * @return An autoreleased EventListenerCustom object.
     */
    static EventListenerCustom* create(const std::string& eventName, const std::function<void(EventCustom*)>& callback);
    
    /** Constructor */
    EventListenerCustom();
    
    /** Initializes event with type and callback function */
    bool init(const std::string& listenerId, const std::function<void(EventCustom*)>& callback);

    std::string getListenerId();

    void invoke(EventCustom* eventCustom);

    void setCallback(const std::function<void(EventCustom*)>& callback);

    /** Sets paused state for the listener
     */
    void setPaused(bool paused) { this->paused = paused; }

    /** Checks whether the listener is paused */
    bool isPaused() const { return this->paused; }

    /** Gets the listener ID of this listener
     *  When event is being dispatched, listener ID is used as key for searching listeners according to event type.
     */
    const std::string& getListenerID() const { return listenerId; }
    
protected:
    std::function<void(EventCustom*)> callback;

    std::string listenerId;
    bool paused;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCCustomEventListener__) */
