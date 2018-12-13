#include "GameCamera.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

GameCamera* GameCamera::cameraInstance = nullptr;

void GameCamera::registerGlobalNode()
{
	GlobalDirector::getInstance()->registerGlobalNode(GameCamera::getInstance());
}

GameCamera* GameCamera::getInstance()
{
	if (GameCamera::cameraInstance == nullptr)
	{
		GameCamera::cameraInstance = new GameCamera();
	}

	return GameCamera::cameraInstance;
}

GameCamera::GameCamera()
{
	this->useStoredNextCameraPosition = false;
	this->targetStack = std::stack<Node*>();
	this->cameraScrollOffset = Vec2::ZERO;
	this->cameraBounds = Rect::ZERO;

	this->defaultDistance = Director::getInstance()->getZEye();
}

GameCamera::~GameCamera()
{
}

void GameCamera::onEnter()
{
	SmartNode::onEnter();

	this->scheduleUpdate();
}

void GameCamera::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* beforeSceneChangeListener = EventListenerCustom::create(
		SceneEvents::BeforeSceneChangeEvent,
		CC_CALLBACK_0(GameCamera::beforeSceneChange, this)
	);

	this->addEventListenerIgnorePause(beforeSceneChangeListener);
}

void GameCamera::beforeSceneChange()
{
	this->clearTargets();
}

void GameCamera::update(float dt)
{
	// This is a work around from a bug where setting the camera position during the loading of a scene can cause
	// A stupid crash inside the physics engine in code with no symbols -- this can't be easily diagnosed,
	// So this is a work around to delay setting the position in the update loop instead, bypassing the crash
	if (this->useStoredNextCameraPosition)
	{
		this->setCameraPositionInternal(this->storedNextCameraPosition);
		this->useStoredNextCameraPosition = false;
	}

	if (this->targetStack.size() > 0)
	{
		Vec2 targetPosition = this->targetStack.top()->getPosition();
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// Handle camera scrolling from target traveling past scroll distance
		if (this->cameraPosition.x < targetPosition.x - this->cameraScrollOffset.x)
		{
			float idealPositionX = targetPosition.x - this->cameraScrollOffset.x + this->trackOffset.x;

			if (followSpeed.x <= 0.0f)
			{
				this->cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - this->cameraPosition.x;
				this->cameraPosition.x = this->cameraPosition.x + distance * this->followSpeed.x;
			}
		}
		else if (this->cameraPosition.x > targetPosition.x + this->cameraScrollOffset.x)
		{
			float idealPositionX = targetPosition.x + this->cameraScrollOffset.x + this->trackOffset.x;

			if (followSpeed.x <= 0.0f)
			{
				this->cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - this->cameraPosition.x;
				this->cameraPosition.x = this->cameraPosition.x + distance * this->followSpeed.x;
			}
		}

		if (this->cameraPosition.y < targetPosition.y - this->cameraScrollOffset.y)
		{
			float idealPositionY = targetPosition.y - this->cameraScrollOffset.y + this->trackOffset.y;

			if (followSpeed.y <= 0.0f)
			{
				this->cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - this->cameraPosition.y;
				this->cameraPosition.y = this->cameraPosition.y + distance * this->followSpeed.y;
			}
		}
		else if (this->cameraPosition.y > targetPosition.y + this->cameraScrollOffset.y)
		{
			float idealPositionY = targetPosition.y + this->cameraScrollOffset.y + this->trackOffset.y;

			if (followSpeed.y <= 0.0f)
			{
				this->cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - this->cameraPosition.y;
				this->cameraPosition.y = this->cameraPosition.y + distance * this->followSpeed.y;
			}
		}

		// Prevent camera from leaving level bounds
		this->cameraPosition.x = MathUtils::clamp(this->cameraPosition.x, this->cameraBounds.getMinX() + visibleSize.width / 2.0f, this->cameraBounds.getMaxX() + visibleSize.width / 2.0f);
		this->cameraPosition.y = MathUtils::clamp(this->cameraPosition.y, this->cameraBounds.getMinY() + visibleSize.height / 2.0f, this->cameraBounds.getMaxY() + visibleSize.height / 2.0f);

		this->setCameraPositionInternal(this->cameraPosition);
	}
}

float GameCamera::getCameraDistance()
{
	return Camera::getDefaultCamera()->getPositionZ();
}

void GameCamera::setCameraDistance(float distance)
{
	this->setPositionZ(distance - this->defaultDistance);
	Camera::getDefaultCamera()->setPositionZ(distance);
}

Vec2 GameCamera::getCameraPosition()
{
	return Camera::getDefaultCamera()->getPosition();
}

void GameCamera::setCameraPosition(Vec2 position, bool addTrackOffset)
{
	this->storedNextCameraPosition = position;
	this->useStoredNextCameraPosition = true;

	if (addTrackOffset)
	{
		this->storedNextCameraPosition += this->trackOffset;
	}
}

void GameCamera::setCameraPositionInternal(Vec2 position, bool addTrackOffset)
{
	this->cameraPosition = position;

	if (addTrackOffset)
	{
		this->cameraPosition += this->trackOffset;
	}

	Camera::getDefaultCamera()->setPosition(this->cameraPosition);
}

Rect GameCamera::getBounds()
{
	return this->cameraBounds;
}

void GameCamera::setBounds(Rect bounds)
{
	this->cameraBounds = bounds;
}

Vec2 GameCamera::getScrollOffset()
{
	return this->cameraScrollOffset;
}

void GameCamera::setScrollOffset(Vec2 offset)
{
	this->cameraScrollOffset = offset;
}

Vec2 GameCamera::getTrackOffset()
{
	return this->trackOffset;
}

void GameCamera::setTrackOffset(Vec2 trackOffset)
{
	this->trackOffset = trackOffset;
}

Vec2 GameCamera::getFollowSpeed()
{
	return this->followSpeed;
}

void GameCamera::setFollowSpeed(Vec2 speed)
{
	speed.x = MathUtils::clamp(speed.x, 0.0f, 1.0f);
	speed.y = MathUtils::clamp(speed.y, 0.0f, 1.0f);

	this->followSpeed = speed;
}

void GameCamera::setTarget(Node* newTarget, Vec2 trackOffset)
{
	this->clearTargets();

	this->setTrackOffset(trackOffset);

	if (newTarget != nullptr)
	{
		this->pushTarget(newTarget);
		this->setCameraPosition(newTarget->getPosition(), true);
	}
}

void GameCamera::pushTarget(Node* newTarget)
{
	this->targetStack.push(newTarget);
}

void GameCamera::popTarget()
{
	this->targetStack.pop();
}

void GameCamera::clearTargets()
{
	while(!this->targetStack.empty())
	{
		this->targetStack.pop();
	}
}
