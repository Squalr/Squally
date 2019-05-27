#include "PointerTraceLevelSelect.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Sound/Music.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"

#include "Resources/IsometricMapResources.h"
#include "Resources/IsometricMapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/PointerTraceResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

PointerTraceLevelSelect* PointerTraceLevelSelect::instance = nullptr;

void PointerTraceLevelSelect::registerGlobalScene()
{
	if (PointerTraceLevelSelect::instance == nullptr)
	{
		PointerTraceLevelSelect::instance = new PointerTraceLevelSelect();

		PointerTraceLevelSelect::instance->autorelease();
		PointerTraceLevelSelect::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PointerTraceLevelSelect::instance);
}

PointerTraceLevelSelect::PointerTraceLevelSelect() : super(false)
{
	this->music = Music::create(MusicResources::PointerTrace);

	this->addChild(this->music);
}

PointerTraceLevelSelect::~PointerTraceLevelSelect()
{
}

void PointerTraceLevelSelect::onEnter()
{
	super::onEnter();

	this->music->play(true);

	const float delay = 0.5f;
	const float duration = 0.75f;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (this->map == nullptr)
	{
		this->loadMap(IsometricMapResources::LevelSelectMap);
	}
}

void PointerTraceLevelSelect::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void PointerTraceLevelSelect::initializeListeners()
{
	super::initializeListeners();

	PointerTraceLevelSelect::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigatePointerTraceLevelSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(PointerTraceLevelSelect::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(PointerTraceLevelSelect::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void PointerTraceLevelSelect::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}
