#include "Cipher.h"

#include "cocos/2d/CCLayer.h"
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
#include "Scenes/Cipher/Components/InputsOutputsPanel.h"
#include "Scenes/Cipher/Components/QuitButton.h"
#include "Scenes/Cipher/Components/TestButton.h"
#include "Scenes/Cipher/Components/ToolBox.h"
#include "Scenes/Cipher/Components/UnlockButton.h"
#include "Scenes/Cipher/States/CipherStateGameEnd.h"
#include "Scenes/Cipher/States/CipherStateLoadInitialState.h"
#include "Scenes/Cipher/States/CipherStateNeutral.h"
#include "Scenes/Cipher/States/CipherStateStartGame.h"
#include "Scenes/Cipher/States/CipherStateTesting.h"
#include "Scenes/Cipher/States/CipherStateTransitionNeutral.h"
#include "Scenes/Cipher/States/CipherStateTransitionUnlocking.h"
#include "Scenes/Cipher/States/CipherStateUnlocking.h"
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
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backClickCallback = nullptr;
	this->cipherBackground = CipherBackground::create();
	this->cipherLock = CipherLock::create();
	this->toolBox = ToolBox::create();
	this->cipherStateTransitionNeutral = CipherStateTransitionNeutral::create();
	this->cipherStateTransitionUnlocking = CipherStateTransitionUnlocking::create();
	this->cipherFrame = CipherFrame::create();
	this->cipherDecor = CipherDecor::create();
	this->inputsOutputsPanel = InputsOutputsPanel::create();
	this->displayModeToggles = DisplayModeToggles::create();
	this->testButton = TestButton::create();
	this->unlockButton = UnlockButton::create();
	this->quitButton = QuitButton::create();
	this->asciiButton = AsciiButton::create();
	this->cipherState = CipherState::create();
	this->cipherStateGameEnd = CipherStateGameEnd::create();
	this->cipherStateLoadInitialState = CipherStateLoadInitialState::create();
	this->cipherStateNeutral = CipherStateNeutral::create();
	this->cipherStateStartGame = CipherStateStartGame::create();
	this->cipherStateTesting = CipherStateTesting::create();
	this->cipherStateUnlocking = CipherStateUnlocking::create();
	this->cipherStateVictory = CipherStateVictory::create();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->asciiTable = AsciiTable::create();

	this->cipherState->lockPointer = this->cipherLock;
	this->cipherState->toolBoxPointer = this->toolBox;

	this->addChild(this->cipherBackground);
	this->addChild(this->cipherLock);
	this->addChild(this->toolBox);
	this->addChild(this->cipherStateTransitionNeutral);
	this->addChild(this->cipherStateTransitionUnlocking);
	this->addChild(this->cipherFrame);
	this->addChild(this->cipherDecor);
	this->addChild(this->inputsOutputsPanel);
	this->addChild(this->displayModeToggles);
	this->addChild(this->testButton);
	this->addChild(this->unlockButton);
	this->addChild(this->quitButton);
	this->addChild(this->asciiButton);
	this->addChild(this->cipherState);
	this->addChild(this->cipherStateGameEnd);
	this->addChild(this->cipherStateLoadInitialState);
	this->addChild(this->cipherStateNeutral);
	this->addChild(this->cipherStateTesting);
	this->addChild(this->cipherStateUnlocking);
	this->addChild(this->cipherStateStartGame);
	this->addChild(this->cipherStateVictory);
	this->addChild(this->backdrop);
	this->addChild(this->asciiTable);
}

Cipher::~Cipher()
{
}

void Cipher::onEnter()
{
	super::onEnter();

	this->setVisible(false);
	this->backdrop->setVisible(false);
	this->asciiTable->setVisible(false);
}

void Cipher::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(CipherEvents::EventOpenAsciiTable, ([=](EventCustom* eventCustom)
	{
		CipherEvents::CipherOpenAsciiTableArgs* args = static_cast<CipherEvents::CipherOpenAsciiTableArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->backdrop->setVisible(true);
			this->asciiTable->open(args->immediateBlock, [=]()
			{
				this->backdrop->setVisible(false);
			});
		}
	})));
}

void Cipher::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop->setPosition(Vec2::ZERO);
}

void Cipher::openCipher(CipherPuzzleData* cipherPuzzleData)
{
	this->cipherState->loadPuzzleData(cipherPuzzleData);
	this->cipherState->updateState(this->cipherState, CipherState::StateType::GameStart);
}

void Cipher::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void Cipher::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}
