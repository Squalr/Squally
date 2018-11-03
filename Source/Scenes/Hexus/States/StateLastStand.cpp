#include "StateLastStand.h"

const std::string StateLastStand::StringKeyHexusLastStand = "Menu_Hexus_Last_Stand";

StateLastStand* StateLastStand::create()
{
	StateLastStand* instance = new StateLastStand();

	instance->autorelease();

	return instance;
}

StateLastStand::StateLastStand() : StateBase(GameState::StateType::LastStand)
{
	this->lastStandButton = MenuSprite::create(
		Resources::Minigames_Hexus_ShieldButton,
		Resources::Minigames_Hexus_ShieldButtonSelected,
		Resources::Minigames_Hexus_ShieldButtonSelected
	);

	this->lastStandPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);

	this->lastStandLabel = Label::create(
		Localization::resolveString(StateLastStand::StringKeyHexusLastStand),
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont())
	);

	this->lastStandBonusLabel = Label::create(
		"",
		Localization::getMainFont(),
		Localization::getFontSizeH1(Localization::getMainFont())
	);

	this->enemyLastStandBonusLabel = Label::create(
		"",
		Localization::getMainFont(),
		Localization::getFontSizeH1(Localization::getMainFont())
	);

	this->lastStandParticles = ParticleSystemQuad::create(Resources::Particles_Aura);

	this->enemyLastStandSprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->enemyLastStandParticles = ParticleSystemQuad::create(Resources::Particles_Aura);

	lastStandBonusLabel->enableOutline(Color4B::BLACK, 2);
	enemyLastStandBonusLabel->enableOutline(Color4B::BLACK, 2);

	this->lastStandParticles->setVisible(false);
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
	this->enemyLastStandSprite->setVisible(false);
	this->enemyLastStandParticles->setVisible(false);

	this->lastStandButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	this->lastStandButton->addChild(this->lastStandBonusLabel);
	this->enemyLastStandSprite->addChild(this->enemyLastStandBonusLabel);
	this->addChild(this->lastStandParticles);
	this->addChild(this->lastStandButton);
	this->addChild(this->lastStandPanel);
	this->addChild(this->lastStandLabel);
	this->addChild(this->enemyLastStandParticles);
	this->addChild(this->enemyLastStandSprite);
}

StateLastStand::~StateLastStand()
{
}

void StateLastStand::onEnter()
{
	StateBase::onEnter();

	this->lastStandParticles->start();
}

void StateLastStand::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->lastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->lastStandButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->lastStandPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->lastStandPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->lastStandPanel->getContentSize().height / 2.0
	);
	this->lastStandLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyLastStandSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyLastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyLastStandBonusLabel->setPosition(this->enemyLastStandSprite->getContentSize() / 2.0f);
}

void StateLastStand::onLastStandClick(MenuSprite* menuSprite, GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::LastStand);
}

void StateLastStand::onLastStandMouseOver()
{
	this->lastStandPanel->setOpacity(196);
	this->lastStandLabel->setOpacity(255);
}

void StateLastStand::onLastStandMouseOut()
{
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
}

void StateLastStand::onStateChange(GameState* gameState)
{
	StateBase::onStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::RoundStart:
		case GameState::StateType::RoundEnd:
		{
			// Show (do not enable though)
			this->lastStandParticles->setVisible(false);
			this->lastStandButton->runAction(FadeTo::create(0.25f, 255));

			this->lastStandBonusLabel->setString("");
			this->enemyLastStandBonusLabel->setString("");

			// Hide enemys last stand icon
			this->enemyLastStandSprite->setVisible(false);
			this->enemyLastStandParticles->setVisible(false);
			break;
		}
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			// Last stand not available if enemy has already used it
			if (gameState->enemyLastStanded)
			{
				this->lastStandParticles->setVisible(false);
				this->lastStandButton->runAction(FadeTo::create(0.25f, 0));
				this->disableLastStandButton();
				return;
			}

			this->enableLastStandButton(gameState);
			break;
		}
		default:
		{
			// Last stand not available if enemy has already used it
			if (gameState->enemyLastStanded)
			{
				this->lastStandParticles->setVisible(false);
				this->lastStandButton->runAction(FadeTo::create(0.25f, 0));
				this->disableLastStandButton();
				return;
			}

			this->disableLastStandButton();
			break;
		}
	}
}

void StateLastStand::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateLastStand::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	// Sanity check -- Prevent last stand if already done
	if (gameState->playerLastStanded || gameState->enemyLastStanded)
	{
		gameState->updateState(gameState, GameState::StateType::Pass);
		return;
	}

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			gameState->lastStandBonus = 0; // std::max(0, gameState->getEnemyTotal() - gameState->getPlayerTotal());
			gameState->playerLastStanded = true;

			//this->lastStandBonusLabel->setString("+" + std::to_string(gameState->lastStandBonus));

			// Start particle effect on activation
			this->lastStandParticles->setVisible(true);
			break;
		case GameState::Turn::Enemy:
			gameState->lastStandBonus = 0; // std::max(0, gameState->getPlayerTotal() - gameState->getEnemyTotal());
			gameState->enemyLastStanded = true;

			//this->enemyLastStandBonusLabel->setString("+" + std::to_string(gameState->lastStandBonus));

			this->enemyLastStandSprite->setVisible(true);
			this->enemyLastStandParticles->setVisible(true);
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

void StateLastStand::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateLastStand::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateLastStand::enableLastStandButton(GameState* gameState)
{
	this->lastStandParticles->setVisible(false);
	this->lastStandButton->setClickCallback(CC_CALLBACK_1(StateLastStand::onLastStandClick, this, gameState));
	this->lastStandButton->setMouseOverCallback(CC_CALLBACK_0(StateLastStand::onLastStandMouseOver, this));
	this->lastStandButton->setMouseOutCallback(CC_CALLBACK_0(StateLastStand::onLastStandMouseOut, this));
	this->lastStandButton->enableInteraction();
}

void StateLastStand::disableLastStandButton()
{
	this->lastStandButton->disableInteraction();
	this->lastStandButton->setClickCallback(nullptr);
	this->lastStandButton->setMouseOverCallback(nullptr);
	this->lastStandButton->setMouseOutCallback(nullptr);
	this->onLastStandMouseOut();
}
