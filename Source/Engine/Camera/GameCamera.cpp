#include "GameCamera.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCScheduler.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GameCamera* GameCamera::cameraInstance = nullptr;
const std::string GameCamera::SchedulerKeyCameraShake = "SCHEDULER_KEY_CAMERA_SHAKE";

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
	this->defaultDistance = Director::getInstance()->getZEye();
	this->targetStack = std::stack<CameraTrackingData>();
	this->mapBounds = Rect::ZERO;
	this->hud = Hud::create();
	this->debugCameraRectangle = DrawNode::create();
	this->debugCameraLabelX = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Debugging_CameraX::create());
	this->debugCameraLabelY = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Debugging_CameraY::create());
	this->debugCameraLabelZoom = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Debugging_CameraZoom::create());
	this->debugCameraStringX = ConstantString::create();
	this->debugCameraStringY = ConstantString::create();
	this->debugCameraStringZoom = ConstantString::create();
	this->debugScrollHitbox = ClickableNode::create();
	this->hud->setLocalZOrder(9999);
	this->hud->setVisible(false);

	this->debugCameraLabelX->setStringReplacementVariables(this->debugCameraStringX);
	this->debugCameraLabelY->setStringReplacementVariables(this->debugCameraStringY);
	this->debugCameraLabelZoom->setStringReplacementVariables(this->debugCameraStringZoom);

	this->debugCameraLabelX->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->debugCameraLabelY->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->debugCameraLabelZoom->setAnchorPoint(Vec2(0.0f, 0.0f));

	Hud* debugScrollHud = Hud::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->debugScrollHitbox->setContentSize(visibleSize);

	debugScrollHud->addChild(this->debugScrollHitbox);
	this->hud->addChild(this->debugCameraRectangle);
	this->hud->addChild(this->debugCameraLabelX);
	this->hud->addChild(this->debugCameraLabelY);
	this->hud->addChild(this->debugCameraLabelZoom);
	this->addChild(debugScrollHud);
	this->addChild(this->hud);
}

GameCamera::~GameCamera()
{
}

void GameCamera::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void GameCamera::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	this->updateCameraDebugLabels();
	this->debugScrollHitbox->enableInteraction();
	this->hud->setVisible(true);
}

void GameCamera::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->debugScrollHitbox->disableInteraction();
	this->hud->setVisible(false);
}

void GameCamera::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	super::initializePositions();

	this->debugScrollHitbox->setPosition(visibleSize / 2.0f);
	this->debugCameraRectangle->setPosition(visibleSize / 2.0f);
	this->debugCameraLabelX->setPosition(Vec2(visibleSize.width - 320.0f, 16.0f + 48.0f));
	this->debugCameraLabelY->setPosition(Vec2(visibleSize.width - 320.0f, 16.0f));
	this->debugCameraLabelZoom->setPosition(Vec2(visibleSize.width - 320.0f, 16.0f + 96.0f));
}

void GameCamera::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(
		SceneEvents::EventBeforeSceneChange,
		[=](EventCustom* eventCustom)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();

			this->unscheduleUpdate();
			this->setBounds(Rect(Vec2::ZERO, visibleSize));
			this->resetCamera();
			this->clearTargets();
		}
	));

	this->debugScrollHitbox->setMouseScrollCallback([=](InputEvents::MouseEventArgs* args)
	{
		args->unhandle();
		float delta = args->scrollDelta.y * 64.0f;
		this->setCameraDistance(this->getCameraDistance() + delta);
	});
}

void GameCamera::update(float dt)
{
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		if (!DeveloperModeController::isDeveloperModeEnabled())
		{
			const float intendedZoom = trackingData.zoom;
			const float distance = intendedZoom - this->getCameraZoom();

			this->setCameraZoom(this->getCameraZoom() + distance * dt);
		}

		switch (trackingData.scrollType)
		{
			default:
			case CameraTrackingData::CameraScrollType::Rectangle:
			{
				cameraPosition = this->boundCameraByRectangle(this->getCameraPosition());
				break;
			}
			case CameraTrackingData::CameraScrollType::Ellipse:
			{
				cameraPosition = this->boundCameraByEllipses(this->getCameraPosition());
				break;
			}
		}
	}

	this->setCameraPosition(cameraPosition, false);
}

float GameCamera::getCameraDistance()
{
	if (Camera::getDefaultCamera() == nullptr)
	{
		return 0.0f;
	}

	return Camera::getDefaultCamera()->getPositionZ();
}

void GameCamera::setCameraDistance(float distance)
{
	if (Camera::getDefaultCamera() == nullptr)
	{
		return;
	}

	this->setPositionZ(distance - this->getIntendedCameraDistance());
	Camera::getDefaultCamera()->setPositionZ(distance);
}

float GameCamera::getCameraZoomOnTarget(cocos2d::Node* target)
{
	return ((this->getCameraDistance() - GameUtils::getDepth(target)) / this->getIntendedCameraDistance());
}

float GameCamera::getCameraZoom()
{
	return (this->getCameraDistance() / this->getIntendedCameraDistance());
}

void GameCamera::setCameraZoom(float zoom)
{

	this->setCameraDistance(this->getIntendedCameraDistance() * zoom);
}

void GameCamera::resetCamera()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setCameraPosition(Vec2(visibleSize / 2.0f));
	this->setCameraZoom(1.0f);
}

float GameCamera::getIntendedCameraDistance()
{
	float distance = this->defaultDistance;

	if (this->getCurrentTrackingData() != nullptr && this->getCurrentTrackingData()->target != nullptr)
	{
		distance += GameUtils::getDepth(this->getCurrentTrackingData()->target);
	}

	return distance;
}

Vec2 GameCamera::getCameraPosition()
{
	if (Camera::getDefaultCamera() == nullptr)
	{
		return Vec2::ZERO;
	}

	return Camera::getDefaultCamera()->getPosition();
}

Vec3 GameCamera::getCameraPosition3()
{
	if (Camera::getDefaultCamera() == nullptr)
	{
		return Vec3::ZERO;
	}

	return Camera::getDefaultCamera()->getPosition3D();
}

void GameCamera::setCameraPosition(Vec2 position, bool addTrackOffset)
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

	if (Camera::getDefaultCamera() != nullptr)
	{
		Camera::getDefaultCamera()->setPosition(cameraPosition);
	}
}

void GameCamera::setCameraPosition3(Vec3 position, bool addTrackOffset)
{
	Vec3 cameraPosition = position;

	if (addTrackOffset && this->targetStack.size() > 0)
	{
		cameraPosition.x += this->targetStack.top().trackOffset.x;
		cameraPosition.y += this->targetStack.top().trackOffset.y;
	}

	if (this->isDeveloperModeEnabled())
	{
		this->updateCameraDebugLabels();
	}

	if (Camera::getDefaultCamera() != nullptr)
	{
		Camera::getDefaultCamera()->setPosition3D(cameraPosition);
	}
}

Rect GameCamera::getBounds()
{
	return this->mapBounds;
}

void GameCamera::setBounds(Rect bounds)
{
	this->mapBounds = bounds;
}

void GameCamera::shakeCamera(float magnitude, float shakesPerSecond, float duration)
{
	// Static such that the lambda can access these. These shouldn't create any significant "double usage" issues if this method is called twice.
	static float elapsed = 0.0f;
	static int ticks = 0;
	static int elapsedTicks = 0;
	float waveLength = (shakesPerSecond / 100.0f);

	// Reset state
	elapsed = 0.0f;
	ticks = int(60.0f * duration); // 60fps
	elapsedTicks = 0;

	Director::getInstance()->getScheduler()->schedule([=](float dt)
	{
		elapsed += dt;

		if (++elapsedTicks < ticks)
		{
			if (Camera::getDefaultCamera() != nullptr)
			{
				Camera::getDefaultCamera()->setRotation(std::sin(elapsed * ((2.0f * float(M_PI)) / waveLength)) * magnitude);
			}
		}
		else
		{
			if (Camera::getDefaultCamera() != nullptr)
			{
				Camera::getDefaultCamera()->setRotation(0.0f);
			}
		}

	}, this, 0.0f, ticks, 0.0f, false, GameCamera::SchedulerKeyCameraShake);
}

Vec2 GameCamera::boundCameraByEllipses(Vec2 cameraPosition)
{
	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		if (trackingData.target == nullptr)
		{
			return cameraPosition;
		}

		Vec2 targetPosition = trackingData.customPositionFunction == nullptr
			? (trackingData.target->getPosition() + trackingData.trackOffset)
			: trackingData.customPositionFunction();

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
		idealPosition = this->boundCameraByMapBounds(idealPosition);

		const Vec2 distance = targetPosition - idealPosition;

		cameraPosition.x = (trackingData.followSpeed.x > 0.0f) ? (cameraPosition.x + distance.x * trackingData.followSpeed.x) : idealPosition.x;
		cameraPosition.y = (trackingData.followSpeed.y > 0.0f) ? (cameraPosition.y + distance.y * trackingData.followSpeed.y) : idealPosition.y;
	}

	return cameraPosition;
}

Vec2 GameCamera::boundCameraByRectangle(Vec2 cameraPosition)
{
	Vec2 idealPosition = cameraPosition;

	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		if (trackingData.target == nullptr)
		{
			return cameraPosition;
		}

		const Vec2 targetPosition = trackingData.customPositionFunction == nullptr
			? (GameUtils::getWorldCoords(trackingData.target) + trackingData.trackOffset)
			: trackingData.customPositionFunction();

		// Handle camera scrolling from target traveling past scroll distance
		if (cameraPosition.x < targetPosition.x - trackingData.scrollOffset.x)
		{
			idealPosition.x = targetPosition.x - trackingData.scrollOffset.x;
		}
		else if (cameraPosition.x > targetPosition.x + trackingData.scrollOffset.x)
		{
			idealPosition.x = targetPosition.x + trackingData.scrollOffset.x;
		}

		if (cameraPosition.y < targetPosition.y - trackingData.scrollOffset.y)
		{
			idealPosition.y = targetPosition.y - trackingData.scrollOffset.y;
		}
		else if (cameraPosition.y > targetPosition.y + trackingData.scrollOffset.y)
		{
			idealPosition.y = targetPosition.y + trackingData.scrollOffset.y;
		}

		idealPosition = this->boundCameraByMapBounds(idealPosition);

		const Vec2 distance = idealPosition - cameraPosition;
		
		cameraPosition.x = (trackingData.followSpeed.x > 0.0f) ? (cameraPosition.x + distance.x * trackingData.followSpeed.x) : idealPosition.x;
		cameraPosition.y = (trackingData.followSpeed.y > 0.0f) ? (cameraPosition.y + distance.y * trackingData.followSpeed.y) : idealPosition.y;
	}

	return cameraPosition;
}

Vec2 GameCamera::boundCameraByMapBounds(Vec2 cameraPosition)
{
	const float CameraZoom = this->getCameraZoom();
	const Size CameraSize = Director::getInstance()->getVisibleSize() * CameraZoom;

	const float MinX = this->mapBounds.getMinX() + CameraSize.width / 2.0f;
	const float MaxX = this->mapBounds.getMaxX() - CameraSize.width / 2.0f;
	const float MinY = this->mapBounds.getMinY() + CameraSize.height / 2.0f;
	const float MaxY = this->mapBounds.getMaxY() - CameraSize.height / 2.0f;

	// Prevent camera from leaving level bounds. Note: Only constrain if out of bounds in one direction, otherwise bounds are irrelevant
	if ((cameraPosition.x < MinX) ^ (cameraPosition.x > MaxX))
	{
		cameraPosition.x = MathUtils::bound(cameraPosition.x, MinX, MaxX);
	}

	if ((cameraPosition.y < MinY) ^ (cameraPosition.y > MaxY))
	{
		cameraPosition.y = MathUtils::bound(cameraPosition.y, MinY, MaxY);
	}

	return cameraPosition;
}

void GameCamera::setTarget(CameraTrackingData trackingData, bool immediatelyTrack)
{
	this->clearTargets();

	this->pushTarget(trackingData, immediatelyTrack);
}

void GameCamera::pushTarget(CameraTrackingData trackingData, bool immediatelyTrack)
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

	if (immediatelyTrack)
	{
		this->setCameraPositionToTrackedTarget();
	}
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
	static Vec3 cachedCameraPosition = Vec3::ZERO;

	if (Camera::getDefaultCamera() == nullptr)
	{
		return;
	}

	Vec3 cameraPosition = this->getCameraPosition3();

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
	std::stringstream streamZoom = std::stringstream();

	streamX << std::fixed << std::setprecision(2) << cameraPosition.x;
	streamY << std::fixed << std::setprecision(2) << cameraPosition.y;
	streamZoom << std::fixed << std::setprecision(2) << this->getCameraZoom();

	this->debugCameraStringX->setString(streamX.str());
	this->debugCameraStringY->setString(streamY.str());
	this->debugCameraStringZoom->setString(streamZoom.str());
}

void GameCamera::setCameraPositionToTrackedTarget()
{
	if (!this->targetStack.empty())
	{
		CameraTrackingData trackingData = this->targetStack.top();

		Vec2 targetPosition = trackingData.customPositionFunction == nullptr ? GameUtils::getWorldCoords(trackingData.target) : trackingData.customPositionFunction();

		this->setCameraPosition(targetPosition, true);
		this->setCameraZoom(trackingData.zoom);
	}
}
