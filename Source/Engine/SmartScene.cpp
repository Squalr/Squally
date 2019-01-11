#include "SmartScene.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/UI/HUD/Hud.h"

const float SmartScene::defaultFadeSpeed = 0.75f;

using namespace cocos2d;

SmartScene::SmartScene()
{
	this->fadeAction = nullptr;
	this->fadeSpeed = SmartScene::defaultFadeSpeed;
	this->layerColorHud = Hud::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));

	this->layerColor->setContentSize(Director::getInstance()->getVisibleSize());
	this->layerColorHud->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->layerColorHud->setZOrder(99999);

	this->layerColorHud->addChild(this->layerColor);
	this->addChild(this->layerColorHud);
}

SmartScene::~SmartScene()
{
}

void SmartScene::onEnter()
{
	super::onEnter();

	// Make fade in visible, fullscreen, and topmost
	if (this->fadeSpeed > 0.0f)
	{
		this->layerColor->setOpacity(255);

		// Fade into the scene
		this->fadeAction = FadeOut::create(this->fadeSpeed);
		this->layerColor->runAction(this->fadeAction);
	}
	else
	{
		this->layerColor->setOpacity(0);
	}

	this->initializePositions();
	this->initializeListeners();
}

void SmartScene::initializePositions()
{
}

void SmartScene::initializeListeners()
{
	this->removeAllListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::DeveloperModeModeEnableEvent, [=](EventCustom* args)
	{
		this->onDeveloperModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::DeveloperModeModeDisableEvent, [=](EventCustom* args)
	{
		this->onDeveloperModeDisable();
	}));
}

void SmartScene::onDeveloperModeEnable()
{
}

void SmartScene::onDeveloperModeDisable()
{
}

bool SmartScene::isDeveloperModeEnabled()
{
	return DeveloperModeController::getInstance()->isDeveloperModeEnabled();
}

void SmartScene::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartScene::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartScene::removeEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->removeEventListener(listener);
}

void SmartScene::addEventListenerIgnorePause(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIgnorePause(true);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartScene::resume()
{
	super::resume();

	this->initializeListeners();
}

void SmartScene::setFadeSpeed(float newFadeSpeed)
{
	this->fadeSpeed = newFadeSpeed;
}

float SmartScene::getFadeSpeed()
{
	return this->fadeSpeed;
}

void SmartScene::pause()
{
	// On pause cancel the fade in animation
	if (this->fadeAction != nullptr)
	{
		this->stopAction(this->fadeAction);
		this->layerColor->setOpacity(0.0f);
	}

	Scene::pause();
}
