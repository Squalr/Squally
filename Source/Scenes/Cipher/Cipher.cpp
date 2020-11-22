#include "Cipher.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/RenderUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/MemesTab.h"
#include "Menus/Options/VideoTab.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherState.h"
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
#include "Scenes/Cipher/Components/Tutorials/CipherTutorials.h"
#include "Scenes/Cipher/Components/UnlockButton.h"
#include "Scenes/Cipher/States/CipherStateGameEnd.h"
#include "Scenes/Cipher/States/CipherStateLoadInitialState.h"
#include "Scenes/Cipher/States/CipherStateNeutral.h"
#include "Scenes/Cipher/States/CipherStateStartGame.h"
#include "Scenes/Cipher/States/CipherStateTesting.h"
#include "Scenes/Cipher/States/CipherStateTransitionUnlocking.h"
#include "Scenes/Cipher/States/CipherStateUnlocking.h"
#include "Scenes/Cipher/States/CipherStateVictory.h"

#include "Resources/ShaderResources.h"
#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

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
	this->gameNode = Node::create();
	this->tutorialNode = Node::create();
	this->cipherTutorialMap = std::map<std::string, std::function<CipherTutorialBase*()>>();

	this->cipherState->cipherLockPointer = this->cipherLock;
	this->cipherState->unlockPointer = this->unlockButton;
	this->cipherState->displayModeTogglesPointer = this->displayModeToggles;
	this->buildTutorialMap();

	this->gameNode->addChild(this->cipherBackground);
	this->gameNode->addChild(this->cipherLock);
	this->gameNode->addChild(this->cipherStateTransitionUnlocking);
	this->gameNode->addChild(this->cipherFrame);
	this->gameNode->addChild(this->cipherDecor);
	this->gameNode->addChild(this->inputsOutputsPanel);
	this->gameNode->addChild(this->displayModeToggles);
	this->gameNode->addChild(this->testButton);
	this->gameNode->addChild(this->unlockButton);
	this->gameNode->addChild(this->quitButton);
	this->gameNode->addChild(this->asciiButton);
	this->gameNode->addChild(this->cipherState);
	this->gameNode->addChild(this->cipherStateGameEnd);
	this->gameNode->addChild(this->cipherStateLoadInitialState);
	this->gameNode->addChild(this->cipherStateNeutral);
	this->gameNode->addChild(this->cipherStateTesting);
	this->gameNode->addChild(this->cipherStateUnlocking);
	this->gameNode->addChild(this->cipherStateStartGame);
	this->gameNode->addChild(this->cipherStateVictory);
	this->gameNode->addChild(this->backdrop);
	this->gameNode->addChild(this->asciiTable);
	this->gameNode->addChild(this->tutorialNode);
	this->addChild(this->gameNode);
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
		CipherEvents::CipherOpenAsciiTableArgs* args = static_cast<CipherEvents::CipherOpenAsciiTableArgs*>(eventCustom->getData());

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
	this->gameNode->setVisible(false);
	this->tutorialNode->removeAllChildren();

	const std::string tutorialKey = cipherPuzzleData->getTutorial();

	if (this->cipherTutorialMap.find(tutorialKey) != this->cipherTutorialMap.end())
	{
		this->tutorialNode->addChild(this->cipherTutorialMap[tutorialKey]());
	}

	this->gameNode->setVisible(true);
	this->cipherState->loadPuzzleData(cipherPuzzleData);
	this->cipherState->updateState(this->cipherState, CipherState::StateType::GameStart);
}

void Cipher::onMenuExit()
{
	// this->music->pop();
	CipherEvents::TriggerExitCipher(CipherEvents::CipherExitArgs(false));
}

void Cipher::buildTutorialMap()
{
	this->cipherTutorialMap[CipherAdditionTutorial::MapKeyTutorial] = [=]() { return CipherAdditionTutorial::create(); };
	this->cipherTutorialMap[CipherConnectTutorial::MapKeyTutorial] = [=]() { return CipherConnectTutorial::create(); };
	this->cipherTutorialMap[CipherExtraTokensTutorial::MapKeyTutorial] = [=]() { return CipherExtraTokensTutorial::create(); };
	this->cipherTutorialMap[CipherOverflowTutorial::MapKeyTutorial] = [=]() { return CipherOverflowTutorial::create(); };
	this->cipherTutorialMap[CipherShiftLeftTutorial::MapKeyTutorial] = [=]() { return CipherShiftLeftTutorial::create(); };
}
