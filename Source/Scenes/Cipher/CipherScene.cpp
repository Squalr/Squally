#include "CipherScene.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherScene* CipherScene::instance = nullptr;

void CipherScene::registerGlobalScene()
{
	if (CipherScene::instance == nullptr)
	{
		CipherScene::instance = new CipherScene();

		CipherScene::instance->autorelease();
		CipherScene::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherScene::instance);
}

CipherScene::CipherScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipher = Cipher::create();
	this->menuBackDrop = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->optionsMenu = OptionsMenu::create();
	this->pauseMenu = PauseMenu::create();
	this->cipherPuzzleDataRef = nullptr;

	this->addChild(this->cipher);
	this->addChild(this->menuBackDrop);
	this->addChild(this->optionsMenu);
	this->addChild(this->pauseMenu);
}

CipherScene::~CipherScene()
{
}

void CipherScene::onEnter()
{
	super::onEnter();

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
}

void CipherScene::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
	
	if (this->cipherPuzzleDataRef != nullptr)
	{
		this->cipher->openCipher(this->cipherPuzzleDataRef->clone());
		this->cipher->setVisible(true);
	}
}

void CipherScene::initializePositions()
{
	super::initializePositions();
}

void CipherScene::initializeListeners()
{
	super::initializeListeners();

	CipherScene::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipher, [](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateCipherArgs* args = static_cast<NavigationEvents::NavigateCipherArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			GlobalDirector::loadScene(CipherScene::instance);

			CipherScene::instance->cipherPuzzleDataRef = args->cipherPuzzleData;
		}
	}));

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(CipherScene::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(CipherScene::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(CipherScene::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(CipherScene::onExitClick, this));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = (CC_CALLBACK_2(CipherScene::onKeyPressed, this));

	this->addEventListener(keyboardListener);
}

void CipherScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void CipherScene::onOptionsExit()
{
	this->optionsMenu->setVisible(false);
	this->openPauseMenu();
}

void CipherScene::openPauseMenu()
{
	this->menuBackDrop->setOpacity(196);
	this->pauseMenu->setVisible(true);
	GameUtils::focus(this->pauseMenu);
}

void CipherScene::onResumeClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	GameUtils::focus(this);
}

void CipherScene::onOptionsClick()
{
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(true);
	GameUtils::focus(this->optionsMenu);
}

void CipherScene::onExitClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	NavigationEvents::navigateTitle();
}

