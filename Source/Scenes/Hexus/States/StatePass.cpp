#include "StatePass.h"

const std::string StatePass::StringKeyHexusPass = "Menu_Hexus_Pass";

StatePass* StatePass::create()
{
	StatePass* instance = new StatePass();

	instance->autorelease();

	return instance;
}

StatePass::StatePass() : StateBase(GameState::StateType::Pass)
{
	Label* passLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* passLabelHover = Label::create(Localization::resolveString(StatePass::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* passLabelClick = Label::create(Localization::resolveString(StatePass::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	passLabel->enableOutline(Color4B::BLACK, 2);
	passLabelHover->enableOutline(Color4B::BLACK, 2);
	passLabelClick->enableOutline(Color4B::BLACK, 2);

	this->passButton = TextMenuSprite::create(
		passLabel,
		passLabelHover,
		passLabelClick,
		Resources::Minigames_Hexus_Button,
		Resources::Minigames_Hexus_ButtonHover,
		Resources::Minigames_Hexus_ButtonClick
	);
	this->passButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	passButton->setOpacity(0);

	this->addChild(this->passButton);
}

StatePass::~StatePass()
{
}

void StatePass::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->passButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
}

void StatePass::onPassClick(MenuSprite* menuSprite, GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::Pass);
}

void StatePass::onStateChange(GameState* gameState)
{
	StateBase::onStateChange(gameState);

	// Keep hidden if enemy has not triggered a last stand
	if (!gameState->enemyLastStanded)
	{
		this->passButton->runAction(FadeTo::create(0.25f, 0));
		this->passButton->disableInteraction();
		this->passButton->setClickCallback(nullptr);

		return;
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
			this->passButton->runAction(FadeTo::create(0.25f, 255));
			this->passButton->setClickCallback(CC_CALLBACK_1(StatePass::onPassClick, this, gameState));
			this->passButton->enableInteraction();
			break;
		default:
			this->passButton->disableInteraction();
			this->passButton->setClickCallback(nullptr);
			break;
	}
}

void StatePass::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePass::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			gameState->playerPassed = true;
			break;
		case GameState::Turn::Enemy:
			gameState->enemyPassed = true;
			break;
		default:
			break;
	}

	this->runAction(Sequence::create(
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
		}),
		nullptr
	));
}

void StatePass::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
