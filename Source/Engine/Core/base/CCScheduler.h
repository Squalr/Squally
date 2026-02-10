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

#ifndef __CCSCHEDULER_H__
#define __CCSCHEDULER_H__

#include <functional>
#include <mutex>
#include <set>
#include <unordered_map>
#include <vector>

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/uthash.h"

NS_CC_BEGIN

struct _ccArray;

class Node;
class Scheduler;

/**
 * @cond
 */
class CC_DLL Timer : public Ref
{
protected:
    Timer();
public:
    void setupTimerWithInterval(float seconds, unsigned int repeat);
    void setAborted() { _aborted = true; }
    bool isAborted() const { return _aborted; }
    bool isExhausted() const;
    
    virtual void trigger(float dt) = 0;
    virtual void cancel() = 0;
    
    /** triggers the timer */
    void update(float dt);
    
protected:
    Scheduler* _scheduler; // weak ref
    float _elapsed;
    bool _runForever;
    unsigned int _timesExecuted;
    unsigned int _repeat; //0 = once, 1 is 2 x executed
    float _interval;
    bool _aborted;
};


class CC_DLL TimerTargetCallback : public Timer
{
public:
    TimerTargetCallback();
    
    // Initializes a timer with a target, a lambda and an interval in seconds, repeat in number of times to repeat.
    bool initWithCallback(Scheduler* scheduler, const std::function<void(float)>& callback, void *target, const std::string& key, float seconds, unsigned int repeat);
    
    const std::function<void(float)>& getCallback() const { return _callback; }
    const std::string& getKey() const { return _key; }
    
    virtual void trigger(float dt) override;
    virtual void cancel() override;
    
protected:
    void* _target;
    std::function<void(float)> _callback;
    std::string _key;
};

/**
 * @endcond
 */

/**
 * @addtogroup base
 * @{
 */

struct ScheduledUpdateTask
{
    std::function<void(float)> callback;
    Node* target;
    bool paused;

    ScheduledUpdateTask() : callback(nullptr), target(nullptr), paused(false) { }
    ScheduledUpdateTask(std::function<void(float)> callback, Node* target, bool paused) : callback(callback), target(target), paused(paused) { }
};

struct ScheduledTask
{
    _ccArray            *timers;
    void                *target;
    int                 timerIndex;
    Timer               *currentTimer;
    bool                paused;
    UT_hash_handle      hh;
};

/** @brief Scheduler is responsible for triggering the scheduled callbacks.
You should not use system timer for your game logic. Instead, use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

*/
class CC_DLL Scheduler : public Ref
{
public:
    /**
     * Constructor
     *
     * @js ctor
     */
    Scheduler();
    
    /**
     * Destructor
     *
     * @js NA
     * @lua NA
     */
    virtual ~Scheduler();

    /** 'update' the scheduler.
     * You should NEVER call this method, unless you know what you are doing.
     * @lua NA
     */
    void update(float dt);

    /////////////////////////////////////
    
    /** The scheduled method will be called every 'interval' seconds for ever.
     @param callback The callback function.
     @param target The target of the callback function.
     @param key The key to identify the callback function, because there is not way to identify a std::function<>.
     @param interval The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     @param repeat Number of times to repeat the task.
     @param paused Whether or not to pause the schedule.
     @since v3.0
     */
    void schedule(const std::function<void(float)>& callback, void *target, const std::string& key, float interval = 0.0f, unsigned int repeat = CC_REPEAT_FOREVER, bool paused = false);
    
    /** Schedules the 'update' selector for a given target.
     The 'update' selector will be called every frame.
     @since v3.0
     @lua NA
     */
    void scheduleUpdate(Node* target, bool paused);

    /////////////////////////////////////

    /** Unschedules a callback for a key and a given target.
     If you want to unschedule the 'callbackPerFrame', use unscheduleUpdate.
     @param key The key to identify the callback function, because there is not way to identify a std::function<>.
     @param target The target to be unscheduled.
     @since v3.0
     */
    void unschedule(const std::string& key, void *target);
    
    /** Unschedules the update selector for a given target
     @param target The target to be unscheduled.
     @since v0.99.3
     */
    void unscheduleUpdate(Node* target);
    
    /** Unschedules all selectors for a given target.
     This also includes the "update" selector.
     @param target The target to be unscheduled.
     @since v0.99.3
     @lua NA
     */
    void unscheduleAllForTarget(void* target);
    
    /** Unschedules all selectors from all targets.
     You should NEVER call this method, unless you know what you are doing.
     @since v0.99.3
     */
    void unscheduleAll();
    
    /////////////////////////////////////
    
    // isScheduled
    
    /** Checks whether a callback associated with 'key' and 'target' is scheduled.
     @param key The key to identify the callback function, because there is not way to identify a std::function<>.
     @param target The target of the callback.
     @return True if the specified callback is invoked, false if not.
     @since v3.0.0
     */
    bool isScheduled(const std::string& key, const void *target) const;
    
    /////////////////////////////////////
    
    /** Pauses the target.
     All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
     If the target is not present, nothing happens.
     @param target The target to be paused.
     @since v0.99.3
     */
    void pauseTarget(Node* target);

    /** Resumes the target.
     The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
     If the target is not present, nothing happens.
     @param target The target to be resumed.
     @since v0.99.3
     */
    void resumeTarget(Node* target);

    /** Returns whether or not the target is paused.
     * @param target The target to be checked.
     * @return True if the target is paused, false if not.
     * @since v1.0.0
     * @lua NA
     */
    bool isTargetPaused(Node* target);

    /** Calls a function on the cocos2d thread. Useful when you need to call a cocos2d function from another thread.
     This function is thread safe.
     @param function The function to be run in cocos2d thread.
     @since v3.0
     @js NA
     */
    void performFunctionInCocosThread(std::function<void()> function);
    
    /**
     * Remove all pending functions queued to be performed with Scheduler::performFunctionInCocosThread
     * Functions unscheduled in this manner will not be executed
     * This function is thread safe
     * @since v3.14
     * @js NA
     */
    void removeAllFunctionsToBePerformedInCocosThread();
    
protected:
    void removeHashElement(struct ScheduledTask *element);

    // Tasks that must be explicitly unscheduled
    std::unordered_map<Node*, ScheduledUpdateTask> taskTable;           // hash used to fetch quickly the list entries for pause, delete, etc
    std::set<Node*> scheduledDeleteTable;                               // the vector holds list entries that needs to be deleted after update
    std::unordered_map<Node*, ScheduledUpdateTask> scheduledAddTable;   // the vector holds list entries that needs to be deleted after update

    // Used for "selectors with interval"
    struct ScheduledTask* _hashForTimers;
    struct ScheduledTask* _currentTarget;
    bool _currentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
    bool updateHashLocked;
    
    // Used for "perform Function"
    std::vector<std::function<void()>> _functionsToPerform;
    std::mutex _performMutex;
};

// end of base group
/** @} */

NS_CC_END

#endif // __CCSCHEDULER_H__
