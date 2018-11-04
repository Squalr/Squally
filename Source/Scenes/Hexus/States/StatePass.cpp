#include "StatePass.h"

const std::string StatePass::StringKeyHexusPass = "Menu_Hexus_Pass";
const std::string StatePass::StringKeyHexusLastStand = "Menu_Hexus_Last_Stand";
const std::string StatePass::StringKeyHexusClaimVictory = "Menu_Hexus_Claim_Victory";

StatePass* StatePass::create()
{
	StatePass* instance = new StatePass();

	instance->autorelease();

	return instance;
}

StatePass::StatePass() : StateBase(GameState::StateType::Pass)
{
	this->activatedSprite = nullptr;

	// Pass
	this->passButton = MenuSprite::create(Resources::Minigames_Hexus_Flags, Resources::Minigames_Hexus_FlagsSelected, Resources::Minigames_Hexus_FlagsSelected);
	this->passPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->passLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->passParticles = ParticleSystemQuad::create(Resources::Particles_BlueAura);
	this->enemyPassSprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->enemyPassParticles = ParticleSystemQuad::create(Resources::Particles_BlueAura);

	this->passParticles->setVisible(false);
	this->passPanel->setOpacity(0);
	this->passLabel->setOpacity(0);
	this->enemyPassSprite->setVisible(false);
	this->enemyPassParticles->setVisible(false);

	this->passButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	// Last stand
	this->lastStandButton = MenuSprite::create(Resources::Minigames_Hexus_ShieldButton, Resources::Minigames_Hexus_ShieldButtonSelected,Resources::Minigames_Hexus_ShieldButtonSelected);
	this->lastStandPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->lastStandLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusLastStand), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->lastStandParticles = ParticleSystemQuad::create(Resources::Particles_Aura);
	this->enemyLastStandSprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->enemyLastStandParticles = ParticleSystemQuad::create(Resources::Particles_Aura);

	this->lastStandParticles->setVisible(false);
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
	this->enemyLastStandSprite->setVisible(false);
	this->enemyLastStandParticles->setVisible(false);

	this->lastStandButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	// Claim victory
	this->claimVictoryButton = MenuSprite::create(Resources::Minigames_Hexus_Victory, Resources::Minigames_Hexus_VictorySelected, Resources::Minigames_Hexus_VictorySelected);
	this->claimVictoryPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->claimVictoryLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusClaimVictory), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->claimVictoryParticles = ParticleSystemQuad::create(Resources::Particles_Aura);
	this->enemyClaimVictorySprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->enemyClaimVictoryParticles = ParticleSystemQuad::create(Resources::Particles_Aura);

	this->claimVictoryParticles->setVisible(false);
	this->claimVictoryPanel->setOpacity(0);
	this->claimVictoryLabel->setOpacity(0);
	this->enemyClaimVictorySprite->setVisible(false);
	this->enemyClaimVictoryParticles->setVisible(false);

	this->claimVictoryButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	this->addChild(this->passParticles);
	this->addChild(this->passButton);
	this->addChild(this->passPanel);
	this->addChild(this->passLabel);
	this->addChild(this->enemyPassParticles);
	this->addChild(this->enemyPassSprite);

	this->addChild(this->lastStandParticles);
	this->addChild(this->lastStandButton);
	this->addChild(this->lastStandPanel);
	this->addChild(this->lastStandLabel);
	this->addChild(this->enemyLastStandParticles);
	this->addChild(this->enemyLastStandSprite);

	this->addChild(this->claimVictoryParticles);
	this->addChild(this->claimVictoryButton);
	this->addChild(this->claimVictoryPanel);
	this->addChild(this->claimVictoryLabel);
	this->addChild(this->enemyClaimVictoryParticles);
	this->addChild(this->enemyClaimVictorySprite);
}

StatePass::~StatePass()
{
}

void StatePass::onEnter()
{
	StateBase::onEnter();

	this->passParticles->start();
	this->lastStandParticles->start();
	this->claimVictoryParticles->start();
}

void StatePass::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Pass
	this->passParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->passButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->passPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->passPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->passPanel->getContentSize().height / 2.0
	);
	this->passLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyPassSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyPassParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);

	// Last stand
	this->lastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->lastStandButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->lastStandPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->lastStandPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->lastStandPanel->getContentSize().height / 2.0
	);
	this->lastStandLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyLastStandSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyLastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);

	// Claim victory
	this->claimVictoryParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->claimVictoryButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->claimVictoryPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->claimVictoryPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->claimVictoryPanel->getContentSize().height / 2.0
	);
	this->claimVictoryLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyClaimVictorySprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyClaimVictoryParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
}

void StatePass::onPassClick(MenuSprite* menuSprite, GameState* gameState)
{
	this->activatedSprite = menuSprite;

	GameState::updateState(gameState, GameState::StateType::Pass);
}

void StatePass::hideAndDisableAllButtons()
{
	// Pass
	this->passParticles->setVisible(false);
	this->passButton->runAction(FadeTo::create(0.25f, 0));
	this->passButton->disableInteraction();
	this->passButton->setClickCallback(nullptr);
	this->passButton->setMouseOverCallback(nullptr);
	this->passButton->setMouseOutCallback(nullptr);
	this->enemyPassSprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyPassParticles->setVisible(false);
	this->onPassMouseOut();

	// Last stand
	this->lastStandParticles->setVisible(false);
	this->lastStandButton->runAction(FadeTo::create(0.25f, 0));
	this->lastStandButton->disableInteraction();
	this->lastStandButton->setClickCallback(nullptr);
	this->lastStandButton->setMouseOverCallback(nullptr);
	this->lastStandButton->setMouseOutCallback(nullptr);
	this->enemyLastStandSprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyLastStandParticles->setVisible(false);
	this->onLastStandMouseOut();

	// Claim victory
	this->claimVictoryParticles->setVisible(false);
	this->claimVictoryButton->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryButton->disableInteraction();
	this->claimVictoryButton->setClickCallback(nullptr);
	this->claimVictoryButton->setMouseOverCallback(nullptr);
	this->claimVictoryButton->setMouseOutCallback(nullptr);
	this->enemyClaimVictorySprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyClaimVictoryParticles->setVisible(false);
	this->onClaimVictoryMouseOut();
}

void StatePass::enablePassButtonInteraction(GameState* gameState)
{
	this->passButton->setClickCallback(CC_CALLBACK_1(StatePass::onPassClick, this, gameState));
	this->passButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onPassMouseOver, this));
	this->passButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onPassMouseOut, this));
	this->passButton->enableInteraction();
}

void StatePass::enableLastStandButtonInteraction(GameState* gameState)
{
	this->lastStandButton->setClickCallback(CC_CALLBACK_1(StatePass::onPassClick, this, gameState));
	this->lastStandButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onLastStandMouseOver, this));
	this->lastStandButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onLastStandMouseOut, this));
	this->lastStandButton->enableInteraction();
}

void StatePass::enableClaimVictoryButtonInteraction(GameState* gameState)
{
	this->claimVictoryButton->setClickCallback(CC_CALLBACK_1(StatePass::onPassClick, this, gameState));
	this->claimVictoryButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onClaimVictoryMouseOver, this));
	this->claimVictoryButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onClaimVictoryMouseOut, this));
	this->claimVictoryButton->enableInteraction();
}

void StatePass::showPassButton()
{
	this->passParticles->setVisible(false);
	this->passButton->runAction(FadeTo::create(0.25f, 255));
}

void StatePass::showLastStandButton()
{
	this->lastStandParticles->setVisible(false);
	this->lastStandButton->runAction(FadeTo::create(0.25f, 255));
}

void StatePass::showClaimVictoryButton()
{
	this->claimVictoryParticles->setVisible(false);
	this->claimVictoryButton->runAction(FadeTo::create(0.25f, 255));
}

void StatePass::onPassMouseOver()
{
	this->passPanel->setOpacity(196);
	this->passLabel->setOpacity(255);
}

void StatePass::onPassMouseOut()
{
	this->passPanel->setOpacity(0);
	this->passLabel->setOpacity(0);
}

void StatePass::onLastStandMouseOver()
{
	this->lastStandPanel->setOpacity(196);
	this->lastStandLabel->setOpacity(255);
}

void StatePass::onLastStandMouseOut()
{
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
}

void StatePass::onClaimVictoryMouseOver()
{
	this->claimVictoryPanel->setOpacity(196);
	this->claimVictoryLabel->setOpacity(255);
}

void StatePass::onClaimVictoryMouseOut()
{
	this->claimVictoryPanel->setOpacity(0);
	this->claimVictoryLabel->setOpacity(0);
}

void StatePass::onAnyStateChange(GameState* gameState)
{
	StateBase::onAnyStateChange(gameState);

	this->hideAndDisableAllButtons();

	MenuSprite* displayedPlayerButton = nullptr;

	// Check what button should be displayed for the player
	if (this->activatedSprite == this->lastStandButton || (!gameState->playerPassed && !gameState->enemyPassed && gameState->getPlayerTotal() >=  gameState->getEnemyTotal()))
	{
		this->showLastStandButton();

		displayedPlayerButton = this->lastStandButton;
	}
	else if (this->activatedSprite == this->claimVictoryButton || (gameState->enemyPassed && gameState->getPlayerTotal() > gameState->getEnemyTotal()))
	{
		this->showClaimVictoryButton();

		displayedPlayerButton = this->claimVictoryButton;
	}
	else
	{
		this->showPassButton();

		displayedPlayerButton = this->passButton;
	}

	// Show particles if one of the buttons is activated
	if (this->activatedSprite == this->passButton)
	{
		this->passParticles->setVisible(true);
	}
	else if (this->activatedSprite == this->lastStandButton)
	{
		this->lastStandParticles->setVisible(true);
	}
	else if (this->activatedSprite == this->claimVictoryButton)
	{
		this->claimVictoryParticles->setVisible(true);
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::RoundStart:
		case GameState::StateType::RoundEnd:
		{
			// Clear active button
			this->activatedSprite = nullptr;
			break;
		}
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			if (displayedPlayerButton == this->passButton)
			{
				this->enablePassButtonInteraction(gameState);
			}
			else if (displayedPlayerButton == this->lastStandButton)
			{
				this->enableLastStandButtonInteraction(gameState);
			}
			else if (displayedPlayerButton == this->claimVictoryButton)
			{
				this->enableClaimVictoryButtonInteraction(gameState);
			}

			break;
		}
		default:
		{
			break;
		}
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
