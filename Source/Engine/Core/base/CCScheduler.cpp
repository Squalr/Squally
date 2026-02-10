/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#include "base/ccCArray.h"
#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCScheduler.h"
#include "base/utlist.h"

NS_CC_BEGIN

// implementation Timer

Timer::Timer()
: _scheduler(nullptr)
, _elapsed(-1)
, _runForever(false)
, _timesExecuted(0)
, _repeat(0)
, _interval(0.0f)
, _aborted(false)
{
}

void Timer::setupTimerWithInterval(float seconds, unsigned int repeat)
{
    _elapsed = -1;
    _interval = seconds;
    _repeat = repeat;
    _runForever = (_repeat == CC_REPEAT_FOREVER) ? true : false;
    _timesExecuted = 0;
}

void Timer::update(float dt)
{
    if (_elapsed == -1)
    {
        _elapsed = 0;
        _timesExecuted = 0;
        return;
    }

    // accumulate elapsed time
    _elapsed += dt;
    
    // if _interval == 0, should trigger once every frame
    float interval = (_interval > 0) ? _interval : _elapsed;

    while ((_elapsed >= interval) && !_aborted)
    {
        _timesExecuted += 1; // important to increment before call trigger
        trigger(interval);
        _elapsed -= interval;

        if (isExhausted())
        {
            cancel();
            break;
        }

        if (_elapsed <= 0.f)
        {
            break;
        }
    }
}

bool Timer::isExhausted() const
{
    return !_runForever && _timesExecuted > _repeat;
}

// TimerTargetCallback

TimerTargetCallback::TimerTargetCallback()
: _target(nullptr)
, _callback(nullptr)
{
}

bool TimerTargetCallback::initWithCallback(Scheduler* scheduler, const std::function<void(float)>& callback, void* target, const std::string& key, float seconds, unsigned int repeat)
{
    _scheduler = scheduler;
    _target = target;
    _callback = callback;
    _key = key;
    setupTimerWithInterval(seconds, repeat);
    return true;
}

void TimerTargetCallback::trigger(float dt)
{
    if (_callback)
    {
        _callback(dt);
    }
}

void TimerTargetCallback::cancel()
{
    _scheduler->unschedule(_key, _target);
}

// implementation of Scheduler

Scheduler::Scheduler()
: _hashForTimers(nullptr)
, _currentTarget(nullptr)
, _currentTargetSalvaged(false)
, updateHashLocked(false)
{
    this->taskTable = std::unordered_map<Node*, ScheduledUpdateTask>();
    this->scheduledDeleteTable = std::set<Node*>();
    this->scheduledAddTable = std::unordered_map<Node*, ScheduledUpdateTask>();
    this->_functionsToPerform.reserve(32); // Not expecting more than 32 functions to all per frame
}

Scheduler::~Scheduler(void)
{
    unscheduleAll();
}

void Scheduler::removeHashElement(ScheduledTask* element)
{
    ccArrayFree(element->timers);
    HASH_DEL(_hashForTimers, element);
    free(element);
}

void Scheduler::scheduleUpdate(Node* target, bool paused)
{
    if (this->taskTable.find(target) != this->taskTable.end()
        || this->scheduledAddTable.find(target) != this->scheduledAddTable.end())
    {
        return;
    }

    if (this->updateHashLocked)
    {
        this->scheduledAddTable[target] = ScheduledUpdateTask(CC_CALLBACK_1(Node::update, target), target, paused);
    }
    else
    {
        this->taskTable[target] = ScheduledUpdateTask(CC_CALLBACK_1(Node::update, target), target, paused);
    }
}

void Scheduler::schedule(const std::function<void(float)>& callback, void *target, const std::string& key, float interval, unsigned int repeat, bool paused)
{
    CCASSERT(target, "Argument target must be non-nullptr");
    CCASSERT(!key.empty(), "key should not be empty!");

    ScheduledTask *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (!element)
    {
        element = (ScheduledTask *)calloc(sizeof(*element), 1);
        element->target = target;

        HASH_ADD_PTR(_hashForTimers, target, element);

        // Is this the 1st element ? Then set the pause level to all the selectors of this target
        element->paused = paused;
    }
    else
    {
        // CCASSERT(element->paused == paused, "element's paused should be paused!");
    }

    if (element->timers == nullptr)
    {
        element->timers = ccArrayNew(10);
    }
    else 
    {
        for (int i = 0; i < element->timers->num; ++i)
        {
            TimerTargetCallback *timer = dynamic_cast<TimerTargetCallback*>(element->timers->arr[i]);

            if (timer && !timer->isExhausted() && key == timer->getKey())
            {
                CCLOG("CCScheduler#schedule. Reiniting timer with interval %.4f, repeat %u", interval, repeat);
                timer->setupTimerWithInterval(interval, repeat);
                return;
            }
        }
        ccArrayEnsureExtraCapacity(element->timers, 1);
    }

    TimerTargetCallback *timer = new (std::nothrow) TimerTargetCallback();
    timer->initWithCallback(this, callback, target, key, interval, repeat);
    ccArrayAppendObject(element->timers, timer);
    timer->release();
}

void Scheduler::unschedule(const std::string &key, void *target)
{
    // explicit handle nil arguments when removing an object
    if (target == nullptr || key.empty())
    {
        return;
    }

    //CCASSERT(target);
    //CCASSERT(selector);

    ScheduledTask *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (element)
    {
        for (int index = 0; index < element->timers->num; index++)
        {
            TimerTargetCallback *timer = dynamic_cast<TimerTargetCallback*>(element->timers->arr[index]);

            if (timer && key == timer->getKey())
            {
                if (timer == element->currentTimer && (! timer->isAborted()))
                {
                    timer->retain();
                    timer->setAborted();
                }

                ccArrayRemoveObjectAtIndex(element->timers, index, true);

                // update timerIndex in case we are in tick:, looping over the actions
                if (element->timerIndex >= index)
                {
                    element->timerIndex--;
                }

                if (element->timers->num == 0)
                {
                    if (_currentTarget == element)
                    {
                        _currentTargetSalvaged = true;
                    }
                    else
                    {
                        removeHashElement(element);
                    }
                }

                return;
            }
        }
    }
}

bool Scheduler::isScheduled(const std::string& key, const void *target) const
{
    CCASSERT(!key.empty(), "Argument key must not be empty");
    CCASSERT(target, "Argument target must be non-nullptr");
    
    ScheduledTask *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    
    if (!element)
    {
        return false;
    }
    
    if (element->timers == nullptr)
    {
        return false;
    }
    
    for (int i = 0; i < element->timers->num; ++i)
    {
        TimerTargetCallback *timer = dynamic_cast<TimerTargetCallback*>(element->timers->arr[i]);
        
        if (timer && !timer->isExhausted() && key == timer->getKey())
        {
            return true;
        }
    }
    
    return false;
}

void Scheduler::unscheduleUpdate(Node* target)
{
    if (this->taskTable.find(target) != this->taskTable.end())
    {
        if (this->updateHashLocked)
        {
            this->scheduledDeleteTable.insert(target);
        }
        else
        {
            this->taskTable.erase(target);
        }
    }
}

void Scheduler::unscheduleAll()
{
}

void Scheduler::unscheduleAllForTarget(void* target)
{
    // explicit nullptr handling
    if (target == nullptr)
    {
        return;
    }

    // Custom Selectors
    ScheduledTask *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (element)
    {
        if (ccArrayContainsObject(element->timers, element->currentTimer)
            && (! element->currentTimer->isAborted()))
        {
            element->currentTimer->retain();
            element->currentTimer->setAborted();
        }
        ccArrayRemoveAllObjects(element->timers);

        if (_currentTarget == element)
        {
            _currentTargetSalvaged = true;
        }
        else
        {
            removeHashElement(element);
        }
    }
}

void Scheduler::resumeTarget(Node* target)
{
    CCASSERT(target != nullptr, "target can't be nullptr!");

    // custom selectors
    ScheduledTask *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (element)
    {
        element->paused = false;
    }

    // update selector
    if (this->taskTable.find(target) != this->taskTable.end())
    {
        this->taskTable[target].paused = false;
    }

    if (this->scheduledAddTable.find(target) != this->scheduledAddTable.end())
    {
        this->scheduledAddTable[target].paused = false;
    }
}

void Scheduler::pauseTarget(Node* target)
{
    CCASSERT(target != nullptr, "target can't be nullptr!");

    // custom selectors
    ScheduledTask* element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    
    if (element)
    {
        element->paused = true;
    }

    // update selector
    if (this->taskTable.find(target) != this->taskTable.end())
    {
        this->taskTable[target].paused = true;
    }
}

bool Scheduler::isTargetPaused(Node* target)
{
    CCASSERT( target != nullptr, "target must be non nil" );

    // Custom selectors
    ScheduledTask* element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if(element)
    {
        return element->paused;
    }
    
    // We should check update selectors if target does not have custom selectors
    if (this->taskTable.find(target) != this->taskTable.end())
    {
        return this->taskTable[target].paused;
    }
    
    return false;  // should never get here
}

void Scheduler::performFunctionInCocosThread(std::function<void ()> function)
{
    std::lock_guard<std::mutex> lock(_performMutex);
    _functionsToPerform.push_back(std::move(function));
}

void Scheduler::removeAllFunctionsToBePerformedInCocosThread()
{
    std::unique_lock<std::mutex> lock(_performMutex);
    _functionsToPerform.clear();
}

// main loop
void Scheduler::update(float dt)
{
    this->updateHashLocked = true;

    for (const auto& taskEntry : this->taskTable)
    {
        auto& key = taskEntry.first;
        auto& task = taskEntry.second;
        
        if (!task.paused && this->scheduledDeleteTable.find(key) == this->scheduledDeleteTable.end())
        {
            task.callback(dt);
        }
    }

    // Iterate over all the custom selectors
    for (ScheduledTask* scheduledTask = this->_hashForTimers; scheduledTask != nullptr;)
    {
        this->_currentTarget = scheduledTask;
        this->_currentTargetSalvaged = false;

        if (!this->_currentTarget->paused)
        {
            // The 'timers' array may change while inside this loop
            for (scheduledTask->timerIndex = 0; scheduledTask->timerIndex < scheduledTask->timers->num; ++(scheduledTask->timerIndex))
            {
                scheduledTask->currentTimer = (Timer*)(scheduledTask->timers->arr[scheduledTask->timerIndex]);
                CCASSERT(!scheduledTask->currentTimer->isAborted(), "An aborted timer should not be updated");

                scheduledTask->currentTimer->update(dt);

                if (scheduledTask->currentTimer->isAborted())
                {
                    // The currentTimer told the remove itself. To prevent the timer from
                    // accidentally deallocating itself before finishing its step, we retained
                    // it. Now that step is done, it's safe to release it.
                    scheduledTask->currentTimer->release();
                }

                scheduledTask->currentTimer = nullptr;
            }
        }

        // scheduledTask, at this moment, is still valid
        // so it is safe to ask this here (issue #490)
        scheduledTask = (ScheduledTask*)scheduledTask->hh.next;

        // only delete currentTarget if no actions were scheduled during the cycle (issue #481)
        if (this->_currentTargetSalvaged && this->_currentTarget->timers->num == 0)
        {
            this->removeHashElement(_currentTarget);
        }
    }

    for (auto& target : this->scheduledAddTable)
    {
        this->taskTable[target.first] = target.second;
    }
 
    // delete all updates that are removed in update
    for (auto& target : this->scheduledDeleteTable)
    {
        this->taskTable.erase(target);
    }

    this->scheduledAddTable.clear();
    this->scheduledDeleteTable.clear();

    this->updateHashLocked = false;
    this->_currentTarget = nullptr;

    //
    // Functions allocated from another thread
    //

    // Testing size is faster than locking / unlocking.
    // And almost never there will be functions scheduled to be called.
    if(!this->_functionsToPerform.empty())
    {
        this->_performMutex.lock();
        // fixed #4123: Save the callback functions, they must be invoked after '_performMutex.unlock()', otherwise if new functions are added in callback, it will cause thread deadlock.
        auto temp = std::move(_functionsToPerform);
        this->_performMutex.unlock();
        
        for (const auto &function : temp)
        {
            function();
        }
    }
}

NS_CC_END
