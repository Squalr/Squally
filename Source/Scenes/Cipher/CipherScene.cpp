#include "CipherScene.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherScene* CipherScene::create(CipherPuzzleData* cipherPuzzleData)
{
	CipherScene* instance = new CipherScene(cipherPuzzleData);

	instance->autorelease();

	return instance;
}

CipherScene::CipherScene(CipherPuzzleData* cipherPuzzleData)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipher = Cipher::create();
	this->menuBackDrop = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->optionsMenu = OptionsMenu::create();
	this->pauseMenu = PauseMenu::create();
	this->cipherPuzzleData = cipherPuzzleData == nullptr ? cipherPuzzleData : cipherPuzzleData->clone();

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
	
	if (this->cipherPuzzleData != nullptr)
	{
		this->cipher->openCipher(this->cipherPuzzleData->clone());
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

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(CipherScene::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(CipherScene::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(CipherScene::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(CipherScene::onExitClick, this));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isFocused(this))
		{
			return;
		}
		args->handled = true;

		this->openPauseMenu();
	});
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
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(TitleScreen::getInstance()));
}

