#include "DebugDisplay.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Strings/Generics/Constant.h"

using namespace cocos2d;

DebugDisplay* DebugDisplay::create()
{
	DebugDisplay* instance = new DebugDisplay();

	instance->autorelease();

	return instance;
}

DebugDisplay::DebugDisplay()
{
	this->stateLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());

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
			this->stateLabel->setStringReplacementVariables(ConstantString::create("EmptyState"));
			break;
		}
		case GameState::StateType::GameStart:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("GameStart"));
			break;
		}
		case GameState::StateType::DrawInitialCards:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("DrawInitialCards"));
			break;
		}
		case GameState::StateType::Draw:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("Draw"));
			break;
		}
		case GameState::StateType::CoinFlip:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("CoinFlip"));
			break;
		}
		case GameState::StateType::RoundStart:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("RoundStart"));
			break;
		}
		case GameState::StateType::CardReplace:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("CardReplace"));
			break;
		}
		case GameState::StateType::PlayerTurnStart:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("PlayerTurnStart"));
			break;
		}
		case GameState::StateType::OpponentTurnStart:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("OpponentTurnStart"));
			break;
		}
		case GameState::StateType::Neutral:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("Neutral"));
			break;
		}
		case GameState::StateType::SelectionStaged:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("SelectionStaged"));
			break;
		}
		case GameState::StateType::CombineStaged:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("CombineStaged"));
			break;
		}
		case GameState::StateType::PlayCard:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("PlayCard"));
			break;
		}
		case GameState::StateType::Pass:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("Pass"));
			break;
		}
		case GameState::StateType::AIDecideCard:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("AIDecideCard"));
			break;
		}
		case GameState::StateType::AIDecideCardReplace:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("AIDecideCardReplace"));
			break;
		}
		case GameState::StateType::AIDecideTarget:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("AIDecideTarget"));
			break;
		}
		case GameState::StateType::TurnEnd:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("TurnEnd"));
			break;
		}
		case GameState::StateType::RoundEnd:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("RoundEnd"));
			break;
		}
		case GameState::StateType::GameEnd:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("GameEnd"));
			break;
		}
		default:
		{
			this->stateLabel->setStringReplacementVariables(ConstantString::create("EmptyInvalidStateState"));
			break;
		}
	}
}
