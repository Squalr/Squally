#include "Cipher.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/RenderUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/MemesTab.h"
#include "Menus/Options/VideoTab.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/Components/AsciiButton.h"
#include "Scenes/Cipher/Components/AsciiTable.h"
#include "Scenes/Cipher/Components/CipherBackground.h"
#include "Scenes/Cipher/Components/CipherDecor.h"
#include "Scenes/Cipher/Components/CipherLock.h"
#include "Scenes/Cipher/Components/CipherFrame.h"
#include "Scenes/Cipher/Components/DisplayModeToggles.h"
#include "Scenes/Cipher/Components/ExecuteButton.h"
#include "Scenes/Cipher/Components/GameBoard.h"
#include "Scenes/Cipher/Components/InputsOutputsPanel.h"
#include "Scenes/Cipher/Components/QuitButton.h"
#include "Scenes/Cipher/Components/ToolBox.h"
#include "Scenes/Cipher/States/CipherStateGameEnd.h"
#include "Scenes/Cipher/States/CipherStateLoadInitialState.h"
#include "Scenes/Cipher/States/CipherStateNeutral.h"
#include "Scenes/Cipher/States/CipherStateRunning.h"
#include "Scenes/Cipher/States/CipherStateStartGame.h"
#include "Scenes/Cipher/States/CipherStateVictory.h"

#include "Resources/ShaderResources.h"
#include "Resources/CipherResources.h"

#include "Strings/Menus/Cancel.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

const Color3B Cipher::TitleColor = Color3B(88, 188, 193);

Cipher* Cipher::create()
{
	Cipher* instance = new Cipher();

	instance->autorelease();

	return instance;
}

Cipher::Cipher()
{
	this->backClickCallback = nullptr;
	this->cipherBackground = CipherBackground::create();
	this->gameBoard = GameBoard::create();
	this->cipherLock = CipherLock::create();
	this->cipherFrame = CipherFrame::create();
	this->cipherDecor = CipherDecor::create();
	this->inputsOutputsPanel = InputsOutputsPanel::create();
	this->toolBox = ToolBox::create();
	this->displayModeToggles = DisplayModeToggles::create();
	this->executeButton = ExecuteButton::create();
	this->quitButton = QuitButton::create();
	this->asciiButton = AsciiButton::create();
	this->asciiTable = AsciiTable::create();
	this->cipherState = CipherState::create();
	this->cipherStateGameEnd = CipherStateGameEnd::create();
	this->cipherStateLoadInitialState = CipherStateLoadInitialState::create();
	this->cipherStateNeutral = CipherStateNeutral::create();
	this->cipherStateRunning = CipherStateRunning::create();
	this->cipherStateStartGame = CipherStateStartGame::create();
	this->cipherStateVictory = CipherStateVictory::create();

	this->addChild(this->cipherBackground);
	this->addChild(this->gameBoard);
	this->addChild(this->cipherLock);
	this->addChild(this->cipherFrame);
	this->addChild(this->cipherDecor);
	this->addChild(this->inputsOutputsPanel);
	this->addChild(this->toolBox);
	this->addChild(this->displayModeToggles);
	this->addChild(this->executeButton);
	this->addChild(this->quitButton);
	this->addChild(this->asciiButton);
	this->addChild(this->asciiTable);
	this->addChild(this->cipherState);
	this->addChild(this->cipherStateGameEnd);
	this->addChild(this->cipherStateLoadInitialState);
	this->addChild(this->cipherStateNeutral);
	this->addChild(this->cipherStateRunning);
	this->addChild(this->cipherStateStartGame);
	this->addChild(this->cipherStateVictory);
}

Cipher::~Cipher()
{
}

void Cipher::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void Cipher::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Cipher::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void Cipher::initializePositions()
{
	super::initializePositions();
}

void Cipher::openCipher(CipherPuzzleData* cipherPuzzleData)
{
	this->cipherState->updateState(this->cipherState, CipherState::StateType::GameStart);
}

void Cipher::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void Cipher::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
			this->onMenuExit();
			break;
		}
		default:
		{
			break;
		}
	}
}

void Cipher::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}
