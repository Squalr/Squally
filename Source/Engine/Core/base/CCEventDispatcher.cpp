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
#include "base/CCEventDispatcher.h"
#include <algorithm>

#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCScheduler.h"
#include "2d/CCScene.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

EventDispatcher::EventDispatcher()
{
    this->listenerMap = std::unordered_map<std::string, std::set<EventListenerCustom*>>();
    this->toRemove = std::unordered_map<std::string, std::set<EventListenerCustom*>>();
    this->toAdd = std::unordered_map<std::string, std::vector<EventListenerCustom*>>();
    
    this->scheduleSlowClean();
}

EventDispatcher::~EventDispatcher()
{
    removeAllEventListeners();
}

void EventDispatcher::addEventListener(EventListenerCustom* listener)
{
    const std::string& eventName = listener->getListenerID();

    listener->retain();

    this->toAdd[eventName].push_back(listener);
}

void EventDispatcher::dispatchEvent(const std::string &eventName, void* optionalUserData)
{
    EventCustom event = EventCustom(eventName, optionalUserData);

    dispatchEvent(&event);
}

void EventDispatcher::dispatchEvent(EventCustom* event)
{
    const std::string& eventName = event->getEventName();

    this->processAddForEvent(eventName);
    this->processRemoveForEvent(eventName);

    // Dispatch event
    if (this->listenerMap.find(eventName) != this->listenerMap.end())
    {
        for (const auto& listener : this->listenerMap[eventName])
        {
            if (this->toRemove.find(eventName) != this->toRemove.end() && this->toRemove[eventName].find(listener) != this->toRemove[eventName].end())
            {
                break;
            }

            if (event->isPropagationStopped())
            {
                break;
            }

            if (!listener->isPaused())
            {
                listener->invoke(event);
            }
        }
    }
}

void EventDispatcher::removeEventListener(EventListenerCustom* listener)
{
    if (listener == nullptr)
    {
        return;
    }
    
    const std::string& eventName = listener->getListenerID();

    this->toRemove[eventName].insert(listener);
}

void EventDispatcher::removeAllEventListeners()
{
    for (const auto& next : this->listenerMap)
    {
        for (const auto& listener : next.second)
        {
            listener->release();
        }
    }

    for (const auto& next : this->toAdd)
    {
        for (const auto& listener : next.second)
        {
            listener->release();
        }
    }

    for (const auto& next : this->toRemove)
    {
        for (const auto& listener : next.second)
        {
            listener->release();
        }
    }

    this->listenerMap.clear();
    this->toAdd.clear();
    this->toRemove.clear();
}

void EventDispatcher::processAddForEvent(const std::string& eventName)
{
    if (this->toAdd.find(eventName) != this->toAdd.end())
    {
        for (const auto& listener : this->toAdd[eventName])
        {
            this->listenerMap[eventName].insert(listener);
        }

        this->toAdd.erase(eventName);
    }
}

void EventDispatcher::processRemoveForEvent(const std::string& eventName)
{
    if (this->toRemove.find(eventName) != this->toRemove.end())
    {
        for (const auto& listener : this->toRemove[eventName])
        {
            listener->release();
            this->listenerMap[eventName].erase(listener);
        }

        this->toRemove.erase(eventName);
    }
}

void EventDispatcher::scheduleSlowClean()
{
	static const std::string eventKey = "EVENT_SLOW_CLEAN";
    static const int TasksPerSecond = 8;
    static const float TickSpeed = 1.0f / float(TasksPerSecond);

    // Schedules a job that fires every update cycle which only adds or removes one listener from the schedule queue.
    Director::getInstance()->getScheduler()->schedule([=](float dt)
    {
        this->slowCleanNext();
    }, this, eventKey, TickSpeed);

    // Long explanation:
    // processAddOrRemoveForEvent(eventName) is automatically called for a given eventName every time a corresponding event is dispatched.
    // However, that corresponding event may never fire, and these jobs could just get stuck in the toAdd and toRemove lists.
    // Over the course of a long gameplay session, this list could theoretically grow to be fairly large.
    // Probably not large enough to do any real damage, but nevertheless it'd be nice to address the issue.
    // To minimize load times, we do not want to process these immediately, so a slow task is good enough!
}

void EventDispatcher::slowCleanNext()
{
    // Always prioritize add first, as there may be an item in both queues.
    if (!this->toAdd.empty())
    {
        this->processAddForEvent(this->toAdd.begin()->first);
    }
    else if (!this->toRemove.empty())
    {
        this->processRemoveForEvent(this->toRemove.begin()->first);
    }
}

NS_CC_END
