/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
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

#include "2d/CCNode.h"

#include <algorithm>
#include <string>
#include <regex>

#include "2d/CCCamera.h"
#include "2d/CCActionManager.h"
#include "2d/CCScene.h"
#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCEventDispatcher.h"
#include "base/ccUTF8.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "math/TransformUtils.h"

#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif


NS_CC_BEGIN

// FIXME:: Yes, nodes might have a sort problem once every 30 days if the game runs at 60 FPS and each frame sprites are reordered.
std::uint32_t Node::s_globalOrderOfArrival = 0;

// MARK: Constructor, Destructor, Init

Node::Node()
: _rotationX(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _position(Vec2::ZERO)
, _positionZ(0.0f)
, _usingNormalizedPosition(false)
, _normalizedPositionDirty(false)
, _selfFlags(FLAGS_DIRTY_MASK)
, _contentSize(CSize::ZERO)
, _transformDirty(true)
, _inverseDirty(true)
// children (lazy allocs)
// lazy alloc
, _localZOrder$Arrival(0LL)
, _parent(nullptr)
// "whole screen" objects. like Scenes and Layers, should set _ignoreAnchorPointForPosition to true
, _name("")
, _glProgramState(nullptr)
, _running(false)
, _paused(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)
, _isTransitionFinished(false)
, _displayedOpacity(255)
, _realOpacity(255)
, _displayedColor(Color3B::WHITE)
, _realColor(Color3B::WHITE)
, _cascadeColorEnabled(false)
, _cascadeOpacityEnabled(true)
, _anchorPoint(0, 0)
{
    // set default scheduler and actionManager
    _director = Director::getInstance();
    _actionManager = _director->getActionManager();
    _actionManager->retain();
    _scheduler = _director->getScheduler();
    _scheduler->retain();
    _eventDispatcher = _director->getEventDispatcher();
    _eventDispatcher->retain();

    _transform = _inverse = Mat4::IDENTITY;
}

Node * Node::create()
{
    Node * ret = new (std::nothrow) Node();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

Node::~Node()
{
    // attributes
    CC_SAFE_RELEASE_NULL(_glProgramState);

    for (auto& child : _children)
    {
        child->_parent = nullptr;
    }
    
    stopAllActions();
    unscheduleAllCallbacks();
    CC_SAFE_RELEASE_NULL(_actionManager);
    CC_SAFE_RELEASE_NULL(_scheduler);

    // CCASSERT(!_running, "Node still marked as running on node destruction! Was base class onExit() called in derived class onExit() implementations?");
    CC_SAFE_RELEASE(_eventDispatcher);
}

bool Node::init()
{
    return true;
}

void Node::cleanup()
{
    // actions
    this->stopAllActions();
    // timers
    this->unscheduleAllCallbacks();
    
    for( const auto &child: _children)
    {
        child->cleanup();
    }
}

std::string Node::getDescription() const
{
    return "Node";
}

void Node::setLocalZOrder(std::int32_t z)
{
    if (getLocalZOrder() == z)
    {
        return;
    }

    _setLocalZOrder(z);

    if (_parent)
    {
        _parent->reorderChild(this, z);
    }
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually
void Node::_setLocalZOrder(std::int32_t z)
{
    _localZOrder = z;
}

void Node::updateOrderOfArrival()
{
    _orderOfArrival = (++s_globalOrderOfArrival);
}

/// rotation getter
float Node::getRotation() const
{
    return _rotationX;
}

void Node::makeDirty()
{
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    _selfFlags |= FLAGS_CONTENT_SIZE_DIRTY;
}

/// rotation setter
void Node::setRotation(float rotation)
{
    if (_rotationX == rotation)
        return;
    
    _rotationX = rotation;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    
    updateRotationQuat();
}

void Node::updateRotationQuat()
{
    // convert Euler angle to quaternion
    float halfRadz = -CC_DEGREES_TO_RADIANS(_rotationX / 2.0f);
    float coshalfRadz = cosf(halfRadz);
    float sinhalfRadz = sinf(halfRadz);

    _rotationQuat.x = 0.0f;
    _rotationQuat.y = 0.0f;
    _rotationQuat.z = sinhalfRadz;
    _rotationQuat.w = coshalfRadz;
}

void Node::setRotationQuat(const Quaternion& quat)
{
    _rotationQuat = quat;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}

Quaternion Node::getRotationQuat() const
{
    return _rotationQuat;
}

/// scale getter
float Node::getScale(void) const
{
    // CCASSERT( _scaleX == _scaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
    return _scaleX;
}

/// scale setter
void Node::setScale(float scale)
{
    setScaleX(scale);
    setScaleY(scale);
}

void Node::setScale(const Vec2& scale)
{
    setScaleX(scale.x);
    setScaleY(scale.y);
}

/// scaleX getter
float Node::getScaleX() const
{
    return _scaleX;
}

/// scale setter
void Node::setScale(float scaleX, float scaleY)
{
    setScaleX(scaleX);
    setScaleY(scaleY);
}

/// scaleX setter
void Node::setScaleX(float scaleX)
{
    if (_scaleX == scaleX)
        return;
    
    _scaleX = scaleX;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}

/// scaleY getter
float Node::getScaleY() const
{
    return _scaleY;
}

/// scaleY setter
void Node::setScaleY(float scaleY)
{
    if (_scaleY == scaleY)
        return;
    
    _scaleY = scaleY;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}


/// position getter
const Vec2& Node::getPosition() const
{
    return _position;
}

/// position setter
void Node::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

void Node::getPosition(float* x, float* y) const
{
    *x = _position.x;
    *y = _position.y;
}

Vec2* Node::getPositionPtr()
{
    return &_position;
}

float* Node::getPositionZPtr()
{
    return &_positionZ;
}

void Node::setPosition(float x, float y)
{
    if (_position.x == x && _position.y == y)
        return;
    
    _position.x = x;
    _position.y = y;
    
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    _usingNormalizedPosition = false;
}

void Node::setPosition3D(const Vec3& position)
{
    setPositionZ(position.z);
    setPosition(position.x, position.y);
}

Vec3 Node::getPosition3D() const
{
    return Vec3(_position.x, _position.y, _positionZ);
}

float Node::getPositionX() const
{
    return _position.x;
}

void Node::setPositionX(float x)
{
    setPosition(x, _position.y);
}

float Node::getPositionY() const
{
    return  _position.y;
}

void Node::setPositionY(float y)
{
    setPosition(_position.x, y);
}

float Node::getPositionZ() const
{
    return _positionZ;
}

void Node::setPositionZ(float positionZ)
{
    if (_positionZ == positionZ)
        return;
    
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;

    _positionZ = positionZ;
}

/// position getter
const Vec2& Node::getPositionNormalized() const
{
    return _normalizedPosition;
}

/// position setter
void Node::setPositionNormalized(const Vec2& position)
{
    if (_normalizedPosition.equals(position))
        return;

    _normalizedPosition = position;
    _usingNormalizedPosition = true;
    _normalizedPositionDirty = true;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}

ssize_t Node::getChildrenCount() const
{
    return _children.size();
}

/// isVisible getter
bool Node::isVisible() const
{
    return _visible;
}

/// isVisible setter
void Node::setVisible(bool visible)
{
    if(visible != _visible)
    {
        _visible = visible;
        if(_visible)
        {
            _transformDirty = _inverseDirty = true;
            _selfFlags |= FLAGS_TRANSFORM_DIRTY;
        }
    }
}

const Vec2& Node::getAnchorPointInPoints() const
{
    return _anchorPointInPoints;
}

/// anchorPoint getter
const Vec2& Node::getAnchorPoint() const
{
    return _anchorPoint;
}

void Node::setAnchorPoint(const Vec2& point)
{
    if (! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
        _transformDirty = _inverseDirty = true;
        _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    }
}

/// contentSize getter
const CSize& Node::getContentSize() const
{
    return _contentSize;
}

void Node::setContentSize(const CSize & size)
{
    if (! size.equals(_contentSize))
    {
        _contentSize = size;

        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
        _transformDirty = _inverseDirty = true;
        _selfFlags |= FLAGS_CONTENT_SIZE_DIRTY;
        _selfFlags |= FLAGS_CONTENT_SIZE_DIRTY;
    }
}

// isRunning getter
bool Node::isRunning() const
{
    return _running;
}

/// parent setter
void Node::setParent(Node * parent)
{
    _parent = parent;
    _transformDirty = _inverseDirty = true;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}

/// isRelativeAnchorPoint getter
bool Node::isIgnoreAnchorPointForPosition() const
{
    return _ignoreAnchorPointForPosition;
}

/// isRelativeAnchorPoint setter
void Node::setIgnoreAnchorPointForPosition(bool newValue)
{
    if (newValue != _ignoreAnchorPointForPosition) 
    {
        _ignoreAnchorPointForPosition = newValue;
        _transformDirty = _inverseDirty = true;
        _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    }
}

const std::string& Node::getName() const
{
    return _name;
}

void Node::setName(const std::string& name)
{
    _name = name;
}

GLProgramState* Node::getGLProgramState() const
{
    return _glProgramState;
}

void Node::setGLProgramState(cocos2d::GLProgramState* glProgramState)
{
    if (glProgramState != _glProgramState)
    {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        CC_SAFE_RETAIN(_glProgramState);

        if (_glProgramState)
            _glProgramState->setNodeBinding(this);
    }
}


void Node::setGLProgram(GLProgram* glProgram)
{
    if (_glProgramState == nullptr || (_glProgramState && _glProgramState->getGLProgram() != glProgram))
    {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = GLProgramState::getOrCreateWithGLProgram(glProgram);
        _glProgramState->retain();

        _glProgramState->setNodeBinding(this);
    }
}

GLProgram * Node::getGLProgram() const
{
    return _glProgramState ? _glProgramState->getGLProgram() : nullptr;
}

Scene* Node::getScene() const
{
    if (!_parent)
        return nullptr;
    
    auto sceneNode = _parent;
    while (sceneNode->_parent)
    {
        sceneNode = sceneNode->_parent;
    }

    return dynamic_cast<Scene*>(sceneNode);
}

CRect Node::getBoundingBox() const
{
	CRect rect(0, 0, _contentSize.width, _contentSize.height);
	return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

CRect Node::getBoundingBoxNoTransform() const
{
	return CRect(0, 0, _contentSize.width, _contentSize.height);
}

// MARK: Children logic

void Node::addChild(Node* child, int localZOrder, const std::string &name)
{
    CCASSERT(child != nullptr, "Argument must be non-nil");

	if (child == nullptr)
	{
		return;
	}

    CCASSERT(child->_parent == nullptr, "child already added. It can't be added again");
    
    addChildHelper(child, localZOrder, name);
}

void Node::addChildHelper(Node* child, int localZOrder, const std::string &name, bool isReentry)
{
	if (child == nullptr)
	{
		return;
	}
    
    this->insertChild(child, localZOrder);
    
    child->setName(name);
    child->setParent(this);
    child->updateOrderOfArrival();

    if(this->_running)
    {
		if (!isReentry)
		{
			child->onEnter();
			// prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
			if (_isTransitionFinished)
			{
				child->onEnterTransitionDidFinish();
			}
		}
		else
		{
			child->onReenter();
		}
    }
    
    if (_cascadeColorEnabled)
    {
        child->updateDisplayedColor(_displayedColor);
    }
    
    if (_cascadeOpacityEnabled)
    {
        child->updateDisplayedOpacity(_displayedOpacity);
    }
}

void Node::addChildInsert(Node *child, int index, bool isReentry)
{
	if (child == nullptr)
	{
		return;
	}

    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
	_reorderChildDirty = true;
	_children.insert(std::min(index, (int)_children.size()), child);
	child->_setLocalZOrder(0);

	child->setName("");

	child->setParent(this);

	for (auto it = this->_children.begin(); it != this->_children.end(); it++)
	{
		(*it)->updateOrderOfArrival();
	}

	if (_running)
	{
		if (!isReentry)
		{
			child->onEnter();
			// prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
			if (_isTransitionFinished)
			{
				child->onEnterTransitionDidFinish();
			}
		}
		else
		{
			child->onReenter();
		}
	}

	if (_cascadeColorEnabled)
	{
		updateCascadeColor();
	}

	if (_cascadeOpacityEnabled)
	{
		updateCascadeOpacity();
	}
}

void Node::addChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");

	if (child == nullptr)
	{
		return;
	}

    this->addChild(child, zOrder, child->_name);
}

void Node::addChild(Node *child)
{
	CCASSERT(child != nullptr, "Argument must be non-nil");

	if (child == nullptr)
	{
		return;
	}

	this->addChild(child, child->getLocalZOrder(), child->_name);
}

void Node::addChildAsReentry(Node *child)
{
	CCASSERT(child != nullptr, "Argument must be non-nil");

	if (child == nullptr)
	{
		return;
	}

	CCASSERT(child->_parent == nullptr, "child already added. It can't be added again");

	addChildHelper(child, child->getLocalZOrder(), child->_name, true);
}

void Node::removeFromParent()
{
    this->removeFromParentAndCleanup(true);
}

void Node::removeFromParentAndCleanup(bool cleanup)
{
    if (_parent != nullptr)
    {
        _parent->removeChild(this,cleanup);
    } 
}

void Node::removeChildNoExit(Node* child)
{
    // explicit nil handling
    if (_children.empty() || child == nullptr)
    {
        return;
    }

    ssize_t index = _children.getIndex(child);

    if( index != CC_INVALID_INDEX )
    {
        child->setParent(nullptr);

        _children.erase(index);
    }
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void Node::removeChild(Node* child, bool cleanup /* = true */)
{
    // explicit nil handling
    if (_children.empty())
    {
        return;
    }

    ssize_t index = _children.getIndex(child);
    if( index != CC_INVALID_INDEX )
        this->detachChild( child, index, cleanup );
}

void Node::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}

void Node::removeAllChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    for (const auto& child : _children)
    {
        // IMPORTANT:
        //  -1st do onExit
        //  -2nd cleanup
        if(_running)
        {
            child->onExitTransitionDidStart();
            child->onExit();
        }

        if (cleanup)
        {
            child->cleanup();
        }

        // set parent nil at the end
        child->setParent(nullptr);
    }
    
    _children.clear();
}

void Node::detachChild(Node *child, ssize_t childIndex, bool doCleanup)
{
	if (child == nullptr)
	{
		return;
	}

    // IMPORTANT:
    //  -1st do onExit
    //  -2nd cleanup
    if (_running)
    {
        child->onExitTransitionDidStart();
        child->onExit();
    }

    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }

    // set parent nil at the end
    child->setParent(nullptr);

    _children.erase(childIndex);
}


// helper used by reorderChild & add
void Node::insertChild(Node* child, int z)
{
	if (child == nullptr)
	{
		return;
	}
    
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
    _reorderChildDirty = true;
    _children.pushBack(child);
    child->_setLocalZOrder(z);
}

void Node::reorderChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Child must be non-nil");
    _reorderChildDirty = true;
    child->updateOrderOfArrival();
    child->_setLocalZOrder(zOrder);
}

void Node::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        sortNodes(_children);
        _reorderChildDirty = false;
    }
}

// MARK: draw / visit

void Node::draw()
{
    auto renderer = _director->getRenderer();
    draw(renderer, _modelViewTransform, true);
}

void Node::draw(Renderer* /*renderer*/, const Mat4 & /*transform*/, uint32_t /*flags*/)
{
}

void Node::visit()
{
    auto renderer = _director->getRenderer();
    auto& parentTransform = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    visit(renderer, parentTransform, true);
}

void Node::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    _selfFlags |= parentFlags;

    // quick return if not visible. children won't be drawn.
    if (!_visible || (_displayedOpacity == 0 && _cascadeOpacityEnabled))
    {
        return;
    }
    
    if(_selfFlags & FLAGS_DIRTY_MASK)
    {
        _modelViewTransform = parentTransform * getNodeToParentTransform();
    }

    // self draw
    this->draw(renderer, _modelViewTransform, _selfFlags);

    const int size = _children.size();

    this->sortAllChildren();

    for (int index = 0; index < size; index++)
    {
        _children[index]->visit(renderer, _modelViewTransform, _selfFlags);
    }

    _selfFlags = 0;
}

void Node::onEnter()
{
	_isTransitionFinished = false;

    sortAllChildren();

	for (const auto &child : _children)
    {
		child->onEnter();
    }
    
	this->resume();

	_running = true;
}

void Node::onReenter()
{
	// _isTransitionFinished = false;
	_isTransitionFinished = true;

	for (const auto &child : _children)
		child->onReenter();

	this->resume();

	_running = true;
}

void Node::onEnterTransitionDidFinish()
{
    _isTransitionFinished = true;
    for( const auto &child: _children)
        child->onEnterTransitionDidFinish();
}

void Node::onExitTransitionDidStart()
{
    for( const auto &child: _children)
        child->onExitTransitionDidStart();
}

void Node::onExit()
{
    this->_running = false;
    
    for(const auto &child: _children)
    {
        child->onExit();
    }
}

void Node::setActionManager(ActionManager* actionManager)
{
    if(actionManager != _actionManager)
    {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }
}

// MARK: actions
Action* Node::runAction(Action* action)
{
    CCASSERT( action != nullptr, "Argument must be non-nil");
    _actionManager->addAction(action, this, !_running);
    return action;
}

void Node::stopAllActions()
{
    if (this->_actionManager != nullptr)
    {
        this->_actionManager->removeAllActionsFromTarget(this);
    }
}

void Node::stopAction(Action* action)
{
    if (this->_actionManager != nullptr)
    {
        this->_actionManager->removeAction(action);
    }
}

ssize_t Node::getNumberOfRunningActions() const
{
    return _actionManager->getNumberOfRunningActionsInTarget(this);
}

// MARK: Callbacks

void Node::setScheduler(Scheduler* scheduler)
{
    if(scheduler != _scheduler)
    {
        this->unscheduleAllCallbacks();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

bool Node::isScheduled(const std::string &key) const
{
    return _scheduler->isScheduled(key, this);
}

void Node::scheduleUpdate()
{
    _scheduler->scheduleUpdate(this, !_running);
}

void Node::unscheduleUpdate()
{
    _scheduler->unscheduleUpdate(this);
}

void Node::schedule(const std::function<void(float)>& callback, const std::string& key, float interval, unsigned int repeat)
{
    _scheduler->schedule(callback, this, key, interval, repeat, !_running);
}

void Node::unschedule(const std::string &key)
{
    _scheduler->unschedule(key, this);
}

void Node::unscheduleAllCallbacks()
{
    _scheduler->unscheduleAllForTarget(this);
    _scheduler->unscheduleUpdate(this);
}

bool Node::isPaused()
{
    return _paused;
}

void Node::resume()
{
    _paused = false;
    _scheduler->resumeTarget(this);
    _actionManager->resumeTarget(this);
}

void Node::pause()
{
    _paused = true;
    _scheduler->pauseTarget(this);
    _actionManager->pauseTarget(this);
}

// override me
void Node::update(float fDelta)
{
}

// MARK: coordinates

AffineTransform Node::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    GLToCGAffine(getNodeToParentTransform().m, &ret);

    return ret;
}


Mat4 Node::getNodeToParentTransform(Node* ancestor) const
{
    Mat4 t(this->getNodeToParentTransform());

    for (Node *p = _parent;  p != nullptr && p != ancestor ; p = p->getParent())
    {
        t = p->getNodeToParentTransform() * t;
    }

    return t;
}

AffineTransform Node::getNodeToParentAffineTransform(Node* ancestor) const
{
    AffineTransform t(this->getNodeToParentAffineTransform());

    for (Node *p = _parent; p != nullptr && p != ancestor; p = p->getParent())
    {
        t = AffineTransformConcat(t, p->getNodeToParentAffineTransform());
    }

    return t;
}
const Mat4& Node::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        // Translate values
        float x = _position.x;
        float y = _position.y;
        float z = _positionZ;
        
        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }

        // Build Transform Matrix = translation * rotation * scale
        Mat4 translation;
        Mat4::createTranslation(x, y, z, &translation);
        Mat4::createRotation(_rotationQuat, &_transform);

        _transform = translation * _transform;

        _transform.m[0] *= _scaleX;
        _transform.m[1] *= _scaleX;
        _transform.m[2] *= _scaleX;
        _transform.m[4] *= _scaleY;
        _transform.m[5] *= _scaleY;
        _transform.m[6] *= _scaleY;

        // adjust anchor point
        _transform.m[12] += _transform.m[0] * -_anchorPointInPoints.x + _transform.m[4] * -_anchorPointInPoints.y;
        _transform.m[13] += _transform.m[1] * -_anchorPointInPoints.x + _transform.m[5] * -_anchorPointInPoints.y;
        _transform.m[14] += _transform.m[2] * -_anchorPointInPoints.x + _transform.m[6] * -_anchorPointInPoints.y;
    }

    _transformDirty = false;

    return _transform;
}

void Node::setNodeToParentTransform(const Mat4& transform)
{
    _transform = transform;
    _transformDirty = false;
    _selfFlags |= FLAGS_TRANSFORM_DIRTY;
}

AffineTransform Node::getParentToNodeAffineTransform() const
{
    AffineTransform ret;

    GLToCGAffine(getParentToNodeTransform().m,&ret);
    return ret;
}

const Mat4& Node::getParentToNodeTransform() const
{
    if ( _inverseDirty )
    {
        _inverse = getNodeToParentTransform().getInversed();
        _inverseDirty = false;
    }

    return _inverse;
}


AffineTransform Node::getNodeToWorldAffineTransform() const
{
    return this->getNodeToParentAffineTransform(nullptr);
}

Mat4 Node::getNodeToWorldTransform() const
{
    return this->getNodeToParentTransform(nullptr);
}

AffineTransform Node::getWorldToNodeAffineTransform() const
{
    return AffineTransformInvert(this->getNodeToWorldAffineTransform());
}

Mat4 Node::getWorldToNodeTransform() const
{
    return getNodeToWorldTransform().getInversed();
}

Vec2 Node::convertToNodeSpace(const Vec2& worldPoint) const
{
	Mat4 tmp = getWorldToNodeTransform();
	Vec3 vec3(worldPoint.x, worldPoint.y, 0);
	Vec3 ret;
	tmp.transformPoint(vec3, &ret);
	return Vec2(ret.x, ret.y);
}

Vec2 Node::convertToWorldSpace(const Vec2& nodePoint) const
{
	Mat4 tmp = getNodeToWorldTransform();
	Vec3 vec3(nodePoint.x, nodePoint.y, 0);
	Vec3 ret;
	tmp.transformPoint(vec3, &ret);
	return Vec2(ret.x, ret.y);

}

Vec3 Node::convertToNodeSpace3(const Vec3& worldPoint) const
{
	Mat4 tmp = getWorldToNodeTransform();
	Vec3 vec3(worldPoint);
	Vec3 ret;
	tmp.transformPoint(vec3, &ret);
	return ret;
}

Vec3 Node::convertToWorldSpace3(const Vec3& nodePoint) const
{
	Mat4 tmp = getNodeToWorldTransform();
	Vec3 vec3(nodePoint);
	Vec3 ret;
	tmp.transformPoint(vec3, &ret);
	return ret;

}

Vec2 Node::convertToNodeSpaceAR(const Vec2& worldPoint) const
{
    Vec2 nodePoint(convertToNodeSpace(worldPoint));
    return nodePoint - _anchorPointInPoints;
}

Vec2 Node::convertToWorldSpaceAR(const Vec2& nodePoint) const
{
    return convertToWorldSpace(nodePoint + _anchorPointInPoints);
}

Vec2 Node::convertToWindowSpace(const Vec2& nodePoint) const
{
    Vec2 worldPoint(this->convertToWorldSpace(nodePoint));
    return _director->convertToUI(worldPoint);
}

void Node::updateTransform()
{
    // Recursively iterate over children
    for( const auto &child: _children)
        child->updateTransform();
}

// MARK: Opacity and Color

GLubyte Node::getOpacity(void) const
{
    return _realOpacity;
}

GLubyte Node::getDisplayedOpacity() const
{
    return _displayedOpacity;
}

void Node::setOpacity(GLubyte opacity)
{
    if (opacity == _realOpacity)
    {
        return;
    }

    _displayedOpacity = _realOpacity = opacity;
    
    updateCascadeOpacity();
}

void Node::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();
    
    if (_cascadeOpacityEnabled)
    {
        for(const auto& child : _children)
        {
            child->updateDisplayedOpacity(_displayedOpacity);
        }
    }
}

bool Node::isCascadeOpacityEnabled(void) const
{
    return _cascadeOpacityEnabled;
}

void Node::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    if (_cascadeOpacityEnabled == cascadeOpacityEnabled)
    {
        return;
    }
    
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
    
    if (cascadeOpacityEnabled)
    {
        updateCascadeOpacity();
    }
    else
    {
        disableCascadeOpacity();
    }
}

void Node::updateCascadeOpacity()
{
    GLubyte parentOpacity = 255;
    
    if (_parent != nullptr && _parent->isCascadeOpacityEnabled())
    {
        parentOpacity = _parent->getDisplayedOpacity();
    }
    
    updateDisplayedOpacity(parentOpacity);
}

void Node::disableCascadeOpacity()
{
    _displayedOpacity = _realOpacity;
    
    for(const auto& child : _children)
    {
        child->updateDisplayedOpacity(255);
    }
}

void Node::setOpacityModifyRGB(bool /*value*/)
{}

bool Node::isOpacityModifyRGB() const
{
    return false;
}

const Color3B& Node::getColor(void) const
{
    return _realColor;
}

const Color3B& Node::getDisplayedColor() const
{
    return _displayedColor;
}

void Node::setColor(const Color3B& color)
{
    _displayedColor = _realColor = color;
    
    updateCascadeColor();
}

void Node::updateDisplayedColor(const Color3B& parentColor)
{
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
    _displayedColor.g = _realColor.g * parentColor.g/255.0;
    _displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();
    
    if (_cascadeColorEnabled)
    {
        for(const auto &child : _children)
        {
            child->updateDisplayedColor(_displayedColor);
        }
    }
}

bool Node::isCascadeColorEnabled(void) const
{
    return _cascadeColorEnabled;
}

void Node::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    if (_cascadeColorEnabled == cascadeColorEnabled)
    {
        return;
    }
    
    _cascadeColorEnabled = cascadeColorEnabled;
    
    if (_cascadeColorEnabled)
    {
        updateCascadeColor();
    }
    else
    {
        disableCascadeColor();
    }
}

void Node::updateCascadeColor()
{
    Color3B parentColor = Color3B::WHITE;
    if (_parent && _parent->isCascadeColorEnabled())
    {
        parentColor = _parent->getDisplayedColor();
    }
    
    updateDisplayedColor(parentColor);
}

void Node::disableCascadeColor()
{
    for(const auto& child : _children)
    {
        child->updateDisplayedColor(Color3B::WHITE);
    }
}

bool isScreenPointInRect(const Vec2 &pt, const Camera* camera, const Mat4& w2l, const CRect& rect, Vec3 *p)
{
    if (nullptr == camera || rect.size.width <= 0 || rect.size.height <= 0)
    {
        return false;
    }
    
    // first, convert pt to near/far plane, get Pn and Pf
    Vec3 Pn(pt.x, pt.y, -1), Pf(pt.x, pt.y, 1);
    Pn = camera->unprojectGL(Pn);
    Pf = camera->unprojectGL(Pf);
    
    //  then convert Pn and Pf to node space
    w2l.transformPoint(&Pn);
    w2l.transformPoint(&Pf);

    // Pn and Pf define a line Q(t) = D + t * E which D = Pn
    auto E = Pf - Pn;
    
    // second, get three points which define content plane
    //  these points define a plane P(u, w) = A + uB + wC
    Vec3 A = Vec3(rect.origin.x, rect.origin.y, 0);
    Vec3 B(rect.origin.x + rect.size.width, rect.origin.y, 0);
    Vec3 C(rect.origin.x, rect.origin.y + rect.size.height, 0);
    B = B - A;
    C = C - A;
    
    //  the line Q(t) intercept with plane P(u, w)
    //  calculate the intercept point P = Q(t)
    //      (BxC).A - (BxC).D
    //  t = -----------------
    //          (BxC).E
    Vec3 BxC;
    Vec3::cross(B, C, &BxC);
    auto BxCdotE = BxC.dot(E);
    if (BxCdotE == 0) {
        return false;
    }
    auto t = (BxC.dot(A) - BxC.dot(Pn)) / BxCdotE;
    Vec3 P = Pn + t * E;
    if (p) {
        *p = P;
    }
    return rect.containsPoint(Vec2(P.x, P.y));
}

// MARK: Deprecated

__NodeRGBA::__NodeRGBA()
{
    CCLOG("NodeRGBA deprecated.");
}

NS_CC_END
