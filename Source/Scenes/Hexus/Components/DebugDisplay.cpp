#include "DebugDisplay.h"

const bool DebugDisplay::enabled = false;

DebugDisplay* DebugDisplay::create()
{
	DebugDisplay* instance = new DebugDisplay();

	instance->autorelease();

	return instance;
}

DebugDisplay::DebugDisplay()
{
	this->stateLabel = Label::createWithTTF("", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->stateLabel->enableOutline(Color4B::BLACK, 2);

	if (!DebugDisplay::enabled)
	{
		this->setVisible(false);
	}

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
			this->stateLabel->setString("EmptyState");
			break;
		case GameState::StateType::GameStart:
			this->stateLabel->setString("GameStart");
			break;
		case GameState::StateType::DrawInitialCards:
			this->stateLabel->setString("DrawInitialCards");
			break;
		case GameState::StateType::Draw:
			this->stateLabel->setString("Draw");
			break;
		case GameState::StateType::CoinFlip:
			this->stateLabel->setString("CoinFlip");
			break;
		case GameState::StateType::RoundStart:
			this->stateLabel->setString("RoundStart");
			break;
		case GameState::StateType::CardReplace:
			this->stateLabel->setString("CardReplace");
			break;
		case GameState::StateType::PlayerTurnStart:
			this->stateLabel->setString("PlayerTurnStart");
			break;
		case GameState::StateType::OpponentTurnStart:
			this->stateLabel->setString("OpponentTurnStart");
			break;
		case GameState::StateType::Neutral:
			this->stateLabel->setString("Neutral");
			break;
		case GameState::StateType::SelectionStaged:
			this->stateLabel->setString("SelectionStaged");
			break;
		case GameState::StateType::CombineStaged:
			this->stateLabel->setString("CombineStaged");
			break;
		case GameState::StateType::PlayCard:
			this->stateLabel->setString("PlayCard");
			break;
		case GameState::StateType::Pass:
			this->stateLabel->setString("Pass");
			break;
		case GameState::StateType::AIDecideCard:
			this->stateLabel->setString("AIDecideCard");
			break;
		case GameState::StateType::AIDecideCardReplace:
			this->stateLabel->setString("AIDecideCardReplace");
			break;
		case GameState::StateType::AIDecideTarget:
			this->stateLabel->setString("AIDecideTarget");
			break;
		case GameState::StateType::TurnEnd:
			this->stateLabel->setString("TurnEnd");
			break;
		case GameState::StateType::RoundEnd:
			this->stateLabel->setString("RoundEnd");
			break;
		case GameState::StateType::GameEnd:
			this->stateLabel->setString("GameEnd");
			break;
		default:
			this->stateLabel->setString("InvalidState");
			break;
	}
}
