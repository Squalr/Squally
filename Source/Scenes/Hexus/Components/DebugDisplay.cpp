#include "DebugDisplay.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

DebugDisplay* DebugDisplay::create()
{
	DebugDisplay* instance = new DebugDisplay();

	instance->autorelease();

	return instance;
}

DebugDisplay::DebugDisplay()
{
	this->stateStr = ConstantString::create();
	this->stateLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->stateStr);
	this->loseButton = ClickableNode::create(UIResources::Menus_Icons_BloodGoblet, UIResources::Menus_Icons_BloodGoblet);
	this->drawButton = ClickableNode::create(UIResources::Menus_Icons_YinYang, UIResources::Menus_Icons_YinYang);
	this->winButton = ClickableNode::create(UIResources::Menus_Icons_Medals, UIResources::Menus_Icons_Medals);
	this->activeGameState = nullptr;

	this->stateLabel->enableOutline(Color4B::BLACK, 2);

	this->setVisible(false);

	this->addChild(this->stateLabel);
	this->addChild(this->loseButton);
	this->addChild(this->drawButton);
	this->addChild(this->winButton);
}

DebugDisplay::~DebugDisplay()
{
}

void DebugDisplay::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	this->setVisible(true);
}

void DebugDisplay::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->setVisible(false);
}

void DebugDisplay::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->stateLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter, visibleSize.height - 32.0f);
	this->loseButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter - 64.0f - 112.0f, visibleSize.height - 372.0f);
	this->drawButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter - 64.0f, visibleSize.height - 372.0f);
	this->winButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter - 64.0f + 112.0f, visibleSize.height - 372.0f);
}

void DebugDisplay::initializeListeners()
{
	super::initializeListeners();

	this->loseButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->activeGameState != nullptr)
		{
			this->activeGameState->playerLosses = 2;
			this->activeGameState->enemyLosses = 0;
		}

		GameState::updateState(this->activeGameState, GameState::StateType::GameEnd);
	});

	this->drawButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->activeGameState != nullptr)
		{
			this->activeGameState->playerLosses = 2;
			this->activeGameState->enemyLosses = 2;
		}

		GameState::updateState(this->activeGameState, GameState::StateType::GameEnd);
	});

	this->winButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->activeGameState != nullptr)
		{
			this->activeGameState->playerLosses = 0;
			this->activeGameState->enemyLosses = 2;
		}
		
		GameState::updateState(this->activeGameState, GameState::StateType::GameEnd);
	});
}

void DebugDisplay::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void DebugDisplay::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	this->activeGameState = gameState;

	switch (gameState->stateType)
	{
		case GameState::StateType::EmptyState:
		{
			this->stateStr->setString("EmptyState");
			break;
		}
		case GameState::StateType::GameStart:
		{
			this->stateStr->setString("GameStart");
			break;
		}
		case GameState::StateType::DrawInitialCards:
		{
			this->stateStr->setString("DrawInitialCards");
			break;
		}
		case GameState::StateType::Draw:
		{
			this->stateStr->setString("Draw");
			break;
		}
		case GameState::StateType::CoinFlip:
		{
			this->stateStr->setString("CoinFlip");
			break;
		}
		case GameState::StateType::RoundStart:
		{
			this->stateStr->setString("RoundStart");
			break;
		}
		case GameState::StateType::CardReplace:
		{
			this->stateStr->setString("CardReplace");
			break;
		}
		case GameState::StateType::PlayerTurnStart:
		{
			this->stateStr->setString("PlayerTurnStart");
			break;
		}
		case GameState::StateType::OpponentTurnStart:
		{
			this->stateStr->setString("OpponentTurnStart");
			break;
		}
		case GameState::StateType::Neutral:
		{
			this->stateStr->setString("Neutral");
			break;
		}
		case GameState::StateType::SelectionStaged:
		{
			this->stateStr->setString("SelectionStaged");
			break;
		}
		case GameState::StateType::CombineStaged:
		{
			this->stateStr->setString("CombineStaged");
			break;
		}
		case GameState::StateType::PlayCard:
		{
			this->stateStr->setString("PlayCard");
			break;
		}
		case GameState::StateType::Pass:
		{
			this->stateStr->setString("Pass");
			break;
		}
		case GameState::StateType::AIDecideCard:
		{
			this->stateStr->setString("AIDecideCard");
			break;
		}
		case GameState::StateType::AIDecideCardReplace:
		{
			this->stateStr->setString("AIDecideCardReplace");
			break;
		}
		case GameState::StateType::AIDecideTarget:
		{
			this->stateStr->setString("AIDecideTarget");
			break;
		}
		case GameState::StateType::TurnEnd:
		{
			this->stateStr->setString("TurnEnd");
			break;
		}
		case GameState::StateType::RoundEnd:
		{
			this->stateStr->setString("RoundEnd");
			this->stateLabel->setStringReplacementVariables(ConstantString::create(""));
			break;
		}
		case GameState::StateType::GameEnd:
		{
			this->stateStr->setString("GameEnd");
			break;
		}
		case GameState::StateType::GameExit:
		{
			this->stateStr->setString("GameExit");
			break;
		}
		case GameState::StateType::Tutorial:
		{
			this->stateStr->setString("Tutorial");
			break;
		}
		default:
		{
			this->stateStr->setString("EmptyInvalidState");
			break;
		}
	}
}
