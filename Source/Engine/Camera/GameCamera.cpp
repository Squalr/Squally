#include "GameCamera.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/HUD/Hud.h"
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
	this->defaultDistance = Director::getInstance()->getZEye();
	this->targetStack = std::stack<CameraTrackingData>();
	this->cameraBounds = Rect::ZERO;
	this->hud = Hud::create();
	this->debugCameraRectangle = DrawNode::create();
	this->debugCameraLabelX = Label::create("", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	this->debugCameraLabelY = Label::create("", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	this->hud->setZOrder(9999);
	this->hud->setVisible(false);

	this->debugCameraLabelX->setAnchorPoint(Vec2(1.0f, 0.0f));
	this->debugCameraLabelY->setAnchorPoint(Vec2(1.0f, 0.0f));

	this->hud->addChild(this->debugCameraRectangle);
	this->hud->addChild(this->debugCameraLabelX);
	this->hud->addChild(this->debugCameraLabelY);
	this->addChild(this->hud);
}

GameCamera::~GameCamera()
{
}

void GameCamera::onEnter()
{
	SmartNode::onEnter();

	this->setCameraPositionWorkAround();
	this->scheduleUpdate();
}

void GameCamera::onDeveloperModeEnable()
{
	SmartNode::onDeveloperModeEnable();

	this->updateCameraDebugLabels();
	this->hud->setVisible(true);
}

void GameCamera::onDeveloperModeDisable()
{
	GameCamera::onDeveloperModeEnable();

	this->hud->setVisible(false);
}

void GameCamera::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	SmartNode::initializePositions();

	this->debugCameraRectangle->setPosition(visibleSize / 2.0f);
	this->debugCameraLabelX->setPosition(Vec2(visibleSize.width - 16.0f, 16.0f + 48.0f));
	this->debugCameraLabelY->setPosition(Vec2(visibleSize.width - 16.0f, 16.0f));
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
	this->setCameraPositionWorkAround();

	if (this->targetStack.size() > 0)
	{
		CameraTrackingData trackingData = this->targetStack.top();

		Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();
		Vec2 targetPosition = trackingData.customPositionFunction == nullptr ? trackingData.target->getPosition() : trackingData.customPositionFunction();
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// Handle camera scrolling from target traveling past scroll distance
		if (cameraPosition.x < targetPosition.x - trackingData.scrollOffset.x)
		{
			float idealPositionX = targetPosition.x - trackingData.scrollOffset.x + trackingData.trackOffset.x;

			if (trackingData.followSpeed.x <= 0.0f)
			{
				cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - cameraPosition.x;
				cameraPosition.x = cameraPosition.x + distance * trackingData.followSpeed.x;
			}
		}
		else if (cameraPosition.x > targetPosition.x + trackingData.scrollOffset.x)
		{
			float idealPositionX = targetPosition.x + trackingData.scrollOffset.x + trackingData.trackOffset.x;

			if (trackingData.followSpeed.x <= 0.0f)
			{
				cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - cameraPosition.x;
				cameraPosition.x = cameraPosition.x + distance * trackingData.followSpeed.x;
			}
		}

		if (cameraPosition.y < targetPosition.y - trackingData.scrollOffset.y)
		{
			float idealPositionY = targetPosition.y - trackingData.scrollOffset.y + trackingData.trackOffset.y;

			if (trackingData.followSpeed.y <= 0.0f)
			{
				cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - cameraPosition.y;
				cameraPosition.y = cameraPosition.y + distance * trackingData.followSpeed.y;
			}
		}
		else if (cameraPosition.y > targetPosition.y + trackingData.scrollOffset.y)
		{
			float idealPositionY = targetPosition.y + trackingData.scrollOffset.y + trackingData.trackOffset.y;

			if (trackingData.followSpeed.y <= 0.0f)
			{
				cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - cameraPosition.y;
				cameraPosition.y = cameraPosition.y + distance * trackingData.followSpeed.y;
			}
		}

		// Prevent camera from leaving level bounds
		cameraPosition.x = MathUtils::clamp(cameraPosition.x, this->cameraBounds.getMinX() + visibleSize.width / 2.0f, this->cameraBounds.getMaxX() - visibleSize.width / 2.0f);
		cameraPosition.y = MathUtils::clamp(cameraPosition.y, this->cameraBounds.getMinY() + visibleSize.height / 2.0f, this->cameraBounds.getMaxY() - visibleSize.height / 2.0f);

		this->setCameraPositionReal(cameraPosition);
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
	// Don't actually set the position -- store it to use later to work around a cocos bug
	this->storedNextCameraPosition = position;
	this->useStoredNextCameraPosition = true;

	if (addTrackOffset && this->targetStack.size() > 0)
	{
		this->storedNextCameraPosition += this->targetStack.top().trackOffset;
	}
}

void GameCamera::setCameraPositionWorkAround()
{
	// This is a work around from a bug where setting the camera position during the loading of a scene can cause
	// A stupid crash inside the physics engine in code with no symbols -- this can't be easily diagnosed,
	// So this is a work around to delay setting the position in the update loop after the scene is loaded instead, bypassing the crash
	if (this->useStoredNextCameraPosition)
	{
		this->setCameraPositionReal(this->storedNextCameraPosition);
		this->useStoredNextCameraPosition = false;
	}
}

void GameCamera::setCameraPositionReal(Vec2 position, bool addTrackOffset)
{
	Vec2 cameraPosition = position;

	if (addTrackOffset && this->targetStack.size() > 0)
	{
		cameraPosition += this->targetStack.top().trackOffset;
	}

	if (this->isDeveloperModeEnabled())
	{
		this->updateCameraDebugLabels();
	}

	Camera::getDefaultCamera()->setPosition(cameraPosition);
}

Rect GameCamera::getBounds()
{
	return this->cameraBounds;
}

void GameCamera::setBounds(Rect bounds)
{
	this->cameraBounds = bounds;
}

void GameCamera::setTarget(CameraTrackingData trackingData)
{
	this->clearTargets();

	this->pushTarget(trackingData);

	if (trackingData.target != nullptr)
	{
		this->setCameraPosition(trackingData.target->getPosition(), true);
	}
}

void GameCamera::pushTarget(CameraTrackingData trackingData)
{
	trackingData.followSpeed.x = MathUtils::clamp(trackingData.followSpeed.x, 0.0f, 1.0f);
	trackingData.followSpeed.y = MathUtils::clamp(trackingData.followSpeed.y, 0.0f, 1.0f);

	this->debugCameraRectangle->removeAllChildren();
	this->debugCameraRectangle->drawRect(Vec2(-trackingData.scrollOffset.x, -trackingData.scrollOffset.y), Vec2(trackingData.scrollOffset.x, trackingData.scrollOffset.y), Color4F::GRAY);

	this->targetStack.push(trackingData);
}

CameraTrackingData* GameCamera::getCurrentTrackingData()
{
	if (this->targetStack.size() > 0)
	{
		return &this->targetStack.top();
	}

	return nullptr;
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

void GameCamera::updateCameraDebugLabels()
{
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	this->debugCameraLabelX->setString("Camera X: " + std::to_string(cameraPosition.x));
	this->debugCameraLabelY->setString("Camera Y: " + std::to_string(cameraPosition.y));
}
