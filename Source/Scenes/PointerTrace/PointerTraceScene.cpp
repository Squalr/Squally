#include "PointerTraceScene.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/PointerTrace/PointerTrace.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

PointerTraceScene* PointerTraceScene::instance = nullptr;

void PointerTraceScene::registerGlobalScene()
{
	if (PointerTraceScene::instance == nullptr)
	{
		PointerTraceScene::instance = new PointerTraceScene();

		PointerTraceScene::instance->autorelease();
		PointerTraceScene::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PointerTraceScene::instance);
}

PointerTraceScene::PointerTraceScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pointerTrace = PointerTrace::create();
	this->menuBackDrop = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->optionsMenu = OptionsMenu::create();
	this->pauseMenu = PauseMenu::create();

	this->addChild(this->pointerTrace);
	this->addChild(this->menuBackDrop);
	this->addChild(this->optionsMenu);
	this->addChild(this->pauseMenu);
}

PointerTraceScene::~PointerTraceScene()
{
}

void PointerTraceScene::onEnter()
{
	super::onEnter();

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
}

void PointerTraceScene::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void PointerTraceScene::initializePositions()
{
	super::initializePositions();
}

void PointerTraceScene::initializeListeners()
{
	super::initializeListeners();

	PointerTraceScene::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigatePointerTrace, [](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateCipherArgs* args = static_cast<NavigationEvents::NavigateCipherArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			GlobalDirector::loadScene(PointerTraceScene::instance);
		}
	}));

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(PointerTraceScene::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(PointerTraceScene::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(PointerTraceScene::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(PointerTraceScene::onExitClick, this));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = (CC_CALLBACK_2(PointerTraceScene::onKeyPressed, this));

	this->addEventListener(keyboardListener);
}

void PointerTraceScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			this->openPauseMenu();
			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}

void PointerTraceScene::onOptionsExit()
{
	this->optionsMenu->setVisible(false);
	this->openPauseMenu();
}

void PointerTraceScene::openPauseMenu()
{
	this->menuBackDrop->setOpacity(196);
	this->pauseMenu->setVisible(true);
	GameUtils::focus(this->pauseMenu);
}

void PointerTraceScene::onResumeClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	GameUtils::focus(this);
}

void PointerTraceScene::onOptionsClick()
{
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(true);
	GameUtils::focus(this->optionsMenu);
}

void PointerTraceScene::onExitClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	NavigationEvents::navigateTitle();
}

