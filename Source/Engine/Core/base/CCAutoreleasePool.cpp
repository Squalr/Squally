/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "base/CCAutoreleasePool.h"
#include "base/CCConsole.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

AutoreleasePool::AutoreleasePool()
: _name("")
{
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::AutoreleasePool(const std::string &name)
: _name(name)
{
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
    CCLOGINFO("deallocing AutoreleasePool: %p", this);
    clear();
    
    PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Ref* object)
{
    _managedObjects.insert(object);
}

void AutoreleasePool::clear()
{
    for (const auto &obj : _managedObjects)
    {
        obj->release();
    }
    
    _managedObjects.clear();
}

bool AutoreleasePool::contains(Ref* object) const
{
    return _managedObjects.find(object) != _managedObjects.end();
}

//--------------------------------------------------------------------
//
// PoolManager
//
//--------------------------------------------------------------------

PoolManager* PoolManager::s_singleInstance = nullptr;

PoolManager* PoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) PoolManager();
        // Add the first auto release pool
        new AutoreleasePool("cocos2d autorelease pool");
    }
    return s_singleInstance;
}

void PoolManager::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::PoolManager()
{
    _releasePoolStack.reserve(10);
}

PoolManager::~PoolManager()
{
    CCLOGINFO("deallocing PoolManager: %p", this);
    
    while (!_releasePoolStack.empty())
    {
        AutoreleasePool* pool = _releasePoolStack.back();
        
        delete pool;
    }
}

AutoreleasePool* PoolManager::getCurrentPool() const
{
    return _releasePoolStack.back();
}

bool PoolManager::isObjectInPools(Ref* obj) const
{
    for (const auto& pool : _releasePoolStack)
    {
        if (pool->contains(obj))
        {
            return true;
        }
    }

    return false;
}

void PoolManager::push(AutoreleasePool *pool)
{
    _releasePoolStack.push_back(pool);
}

void PoolManager::pop()
{
    CC_ASSERT(!_releasePoolStack.empty());
    _releasePoolStack.pop_back();
}

NS_CC_END
