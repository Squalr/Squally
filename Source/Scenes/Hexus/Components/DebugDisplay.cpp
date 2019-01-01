#include "DebugDisplay.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Strings/LateBound.h"

using namespace cocos2d;

DebugDisplay* DebugDisplay::create()
{
	DebugDisplay* instance = new DebugDisplay();

	instance->autorelease();

	return instance;
}

DebugDisplay::DebugDisplay()
{
	this->stateLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::LateBound::create());

	this->stateLabel->enableOutline(Color4B::BLACK, 2);

	this->setVisible(false);

	this->addChild(this->stateLabel);
}

DebugDisplay::~DebugDisplay()
{
}

void DebugDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->stateLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter, visibleSize.height - 32.0f);
}

void DebugDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DebugDisplay::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::EmptyState:
		{
			this->stateLabel->setStringReplacementVariables({ "EmptyState" });
			break;
		}
		case GameState::StateType::GameStart:
		{
			this->stateLabel->setStringReplacementVariables({ "GameStart" });
			break;
		}
		case GameState::StateType::DrawInitialCards:
		{
			this->stateLabel->setStringReplacementVariables({ "DrawInitialCards" });
			break;
		}
		case GameState::StateType::Draw:
		{
			this->stateLabel->setStringReplacementVariables({ "Draw" });
			break;
		}
		case GameState::StateType::CoinFlip:
		{
			this->stateLabel->setStringReplacementVariables({ "CoinFlip" });
			break;
		}
		case GameState::StateType::RoundStart:
		{
			this->stateLabel->setStringReplacementVariables({ "RoundStart" });
			break;
		}
		case GameState::StateType::CardReplace:
		{
			this->stateLabel->setStringReplacementVariables({ "CardReplace" });
			break;
		}
		case GameState::StateType::PlayerTurnStart:
		{
			this->stateLabel->setStringReplacementVariables({ "PlayerTurnStart" });
			break;
		}
		case GameState::StateType::OpponentTurnStart:
		{
			this->stateLabel->setStringReplacementVariables({ "OpponentTurnStart" });
			break;
		}
		case GameState::StateType::Neutral:
		{
			this->stateLabel->setStringReplacementVariables({ "Neutral" });
			break;
		}
		case GameState::StateType::SelectionStaged:
		{
			this->stateLabel->setStringReplacementVariables({ "SelectionStaged" });
			break;
		}
		case GameState::StateType::CombineStaged:
		{
			this->stateLabel->setStringReplacementVariables({ "CombineStaged" });
			break;
		}
		case GameState::StateType::PlayCard:
		{
			this->stateLabel->setStringReplacementVariables({ "PlayCard" });
			break;
		}
		case GameState::StateType::Pass:
		{
			this->stateLabel->setStringReplacementVariables({ "Pass" });
			break;
		}
		case GameState::StateType::AIDecideCard:
		{
			this->stateLabel->setStringReplacementVariables({ "AIDecideCard" });
			break;
		}
		case GameState::StateType::AIDecideCardReplace:
		{
			this->stateLabel->setStringReplacementVariables({ "AIDecideCardReplace" });
			break;
		}
		case GameState::StateType::AIDecideTarget:
		{
			this->stateLabel->setStringReplacementVariables({ "AIDecideTarget" });
			break;
		}
		case GameState::StateType::TurnEnd:
		{
			this->stateLabel->setStringReplacementVariables({ "TurnEnd" });
			break;
		}
		case GameState::StateType::RoundEnd:
		{
			this->stateLabel->setStringReplacementVariables({ "RoundEnd" });
			break;
		}
		case GameState::StateType::GameEnd:
		{
			this->stateLabel->setStringReplacementVariables({ "GameEnd" });
			break;
		}
		default:
		{
			this->stateLabel->setStringReplacementVariables({ "InvalidState" });
			break;
		}
	}
}
