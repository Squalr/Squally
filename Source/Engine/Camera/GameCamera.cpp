#include "GameCamera.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Strings/Debugging/CameraX.h"
#include "Strings/Debugging/CameraY.h"

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
	this->debugCameraLabelX = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Debugging_CameraX::create());
	this->debugCameraLabelY = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Debugging_CameraY::create());
	this->debugCameraStringX = ConstantString::create();
	this->debugCameraStringY = ConstantString::create();
	this->hud->setZOrder(9999);
	this->hud->setVisible(false);

	this->debugCameraLabelX->setStringReplacementVariables(this->debugCameraStringX);
	this->debugCameraLabelY->setStringReplacementVariables(this->debugCameraStringY);

	this->debugCameraLabelX->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->debugCameraLabelY->setAnchorPoint(Vec2(0.0f, 0.0f));

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
	super::onEnter();

	this->setCameraPositionWorkAround();
	this->scheduleUpdate();
}

void GameCamera::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

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

	super::initializePositions();

	this->debugCameraRectangle->setPosition(visibleSize / 2.0f);
	this->debugCameraLabelX->setPosition(Vec2(visibleSize.width - 320.0f, 16.0f + 48.0f));
	this->debugCameraLabelY->setPosition(Vec2(visibleSize.width - 320.0f, 16.0f));
}

void GameCamera::initializeListeners()
{
	super::initializeListeners();

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

	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		switch (trackingData.scrollType)
		{
			default:
			case CameraTrackingData::CameraScrollType::Rectangle:
			{
				cameraPosition = this->boundCameraByRectangle();
				break;
			}
			case CameraTrackingData::CameraScrollType::Ellipse:
			{
				cameraPosition = this->boundCameraByEllipses();
				break;
			}
		}
	}

	// Prevent camera from leaving level bounds
	cameraPosition.x = MathUtils::clamp(cameraPosition.x, this->cameraBounds.getMinX() + visibleSize.width / 2.0f, this->cameraBounds.getMaxX() - visibleSize.width / 2.0f);
	cameraPosition.y = MathUtils::clamp(cameraPosition.y, this->cameraBounds.getMinY() + visibleSize.height / 2.0f, this->cameraBounds.getMaxY() - visibleSize.height / 2.0f);

	this->setCameraPositionReal(cameraPosition);
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

Vec2 GameCamera::boundCameraByEllipses()
{
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		if (trackingData.target == nullptr)
		{
			return cameraPosition;
		}

		Vec2 targetPosition = trackingData.customPositionFunction == nullptr ? trackingData.target->getPosition() : trackingData.customPositionFunction();

		// Don't even bother if the input data is bad
		if (trackingData.scrollOffset.x <= 0.0f || trackingData.scrollOffset.y <= 0.0f)
		{
			return cameraPosition;
		}

		// Bounds check first
		if (((targetPosition.x - cameraPosition.x) * (targetPosition.x - cameraPosition.x)) / (trackingData.scrollOffset.x * trackingData.scrollOffset.x) +
			((targetPosition.y - cameraPosition.y) * (targetPosition.y - cameraPosition.y)) / (trackingData.scrollOffset.y * trackingData.scrollOffset.y) <= 1.0f)
		{
			return cameraPosition;
		}

		Vec2 idealPosition = AlgoUtils::pointOnEllipse(cameraPosition, trackingData.scrollOffset.x, trackingData.scrollOffset.y, targetPosition);
		float deltaX = targetPosition.x - idealPosition.x;
		float deltaY = targetPosition.y - idealPosition.y;

		if (trackingData.followSpeed.x > 0.0f)
		{
			cameraPosition.x = cameraPosition.x + deltaX * trackingData.followSpeed.x;
		}
		else
		{
			cameraPosition.x = idealPosition.x;
		}

		if (trackingData.followSpeed.y > 0.0f)
		{
			cameraPosition.y = cameraPosition.y + deltaY * trackingData.followSpeed.y;
		}
		else
		{
			cameraPosition.y = idealPosition.y;
		}
	}

	return cameraPosition;
}

Vec2 GameCamera::boundCameraByRectangle()
{
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		if (trackingData.target == nullptr)
		{
			return cameraPosition;
		}

		Vec2 targetPosition = trackingData.customPositionFunction == nullptr ? trackingData.target->getPosition() : trackingData.customPositionFunction();

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
	}

	return cameraPosition;
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

	this->debugCameraRectangle->clear();

	switch (trackingData.scrollType)
	{
		default:
		case CameraTrackingData::CameraScrollType::Rectangle:
		{
			this->debugCameraRectangle->drawRect(Vec2(-trackingData.scrollOffset.x, -trackingData.scrollOffset.y), Vec2(trackingData.scrollOffset.x, trackingData.scrollOffset.y), Color4F::GRAY);
			break;
		}
		case CameraTrackingData::CameraScrollType::Ellipse:
		{
			this->debugCameraRectangle->drawEllipse(Vec2::ZERO, trackingData.scrollOffset.x, trackingData.scrollOffset.y, 0.0f, 48, false, Color4F::GRAY);
			break;
		}
	}

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
	static Vec2 cachedCameraPosition = Vec2::ZERO;

	if (Camera::getDefaultCamera() == nullptr)
	{
		return;
	}

	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	if (cachedCameraPosition == cameraPosition)
	{
		return;
	}
	else
	{
		cachedCameraPosition = cameraPosition;
	}

	std::stringstream streamX = std::stringstream();
	std::stringstream streamY = std::stringstream();

	streamX << std::fixed << std::setprecision(2) << cameraPosition.x;
	streamY << std::fixed << std::setprecision(2) << cameraPosition.y;

	this->debugCameraStringX->setString(streamX.str());
	this->debugCameraStringY->setString(streamY.str());
}
