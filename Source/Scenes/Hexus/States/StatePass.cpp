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
	// Pass
	this->passSprite = Sprite::create(Resources::Minigames_Hexus_Flags);
	this->passButton = IconMenuSprite::create(Resources::Minigames_Hexus_Flags, Resources::Minigames_Hexus_FlagsSelected, Resources::Menus_Buttons_WoodSquareButton, Resources::Menus_Buttons_WoodSquareButtonSelected);
	this->passPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->passLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->passParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_WhiteAura);
	this->enemyPassSprite = Sprite::create(Resources::Minigames_Hexus_Flags);
	this->enemyPassParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_WhiteAura);

	// Last stand
	this->lastStandSprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->lastStandButton = IconMenuSprite::create(Resources::Minigames_Hexus_ShieldButton, Resources::Minigames_Hexus_ShieldButtonSelected, Resources::Menus_Buttons_WoodSquareButton, Resources::Menus_Buttons_WoodSquareButtonSelected);
	this->lastStandPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->lastStandLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusLastStand), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->lastStandParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_Aura);
	this->enemyLastStandSprite = Sprite::create(Resources::Minigames_Hexus_ShieldButton);
	this->enemyLastStandParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_Aura);

	// Claim victory
	this->claimVictorySprite = Sprite::create(Resources::Minigames_Hexus_Victory);
	this->claimVictoryButton = IconMenuSprite::create(Resources::Minigames_Hexus_Victory, Resources::Minigames_Hexus_VictorySelected, Resources::Menus_Buttons_WoodSquareButton, Resources::Menus_Buttons_WoodSquareButtonSelected);
	this->claimVictoryPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->claimVictoryLabel = Label::create(Localization::resolveString(StatePass::StringKeyHexusClaimVictory), Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->claimVictoryParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_Aura);
	this->enemyClaimVictorySprite = Sprite::create(Resources::Minigames_Hexus_Victory);
	this->enemyClaimVictoryParticles = ParticleSystemQuad::create(Resources::Particles_Hexus_Aura);

	this->addChild(this->passParticles);
	this->addChild(this->passSprite);
	this->addChild(this->passButton);
	this->addChild(this->passPanel);
	this->addChild(this->passLabel);
	this->addChild(this->enemyPassParticles);
	this->addChild(this->enemyPassSprite);

	this->addChild(this->lastStandParticles);
	this->addChild(this->lastStandSprite);
	this->addChild(this->lastStandButton);
	this->addChild(this->lastStandPanel);
	this->addChild(this->lastStandLabel);
	this->addChild(this->enemyLastStandParticles);
	this->addChild(this->enemyLastStandSprite);

	this->addChild(this->claimVictoryParticles);
	this->addChild(this->claimVictorySprite);
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

	this->currentVisiblePlayerButton = nullptr;
	this->playerChoiceLocked = false;

	this->passParticles->setVisible(false);
	// Default this button to visible
	this->passButton->setOpacity(255);
	this->passSprite->setOpacity(0);
	this->passPanel->setOpacity(0);
	this->passLabel->setOpacity(0);
	this->enemyPassSprite->setOpacity(0);
	this->enemyPassParticles->setVisible(false);

	this->lastStandParticles->setVisible(false);
	this->lastStandButton->setOpacity(0);
	this->lastStandSprite->setOpacity(0);
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
	this->enemyLastStandSprite->setOpacity(0);
	this->enemyLastStandParticles->setVisible(false);

	this->claimVictoryParticles->setVisible(false);
	this->claimVictoryButton->setOpacity(0);
	this->claimVictorySprite->setOpacity(0);
	this->claimVictoryPanel->setOpacity(0);
	this->claimVictoryLabel->setOpacity(0);
	this->enemyClaimVictorySprite->setOpacity(0);
	this->enemyClaimVictoryParticles->setVisible(false);

	this->passParticles->start();
	this->lastStandParticles->start();
	this->claimVictoryParticles->start();
}

void StatePass::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Pass
	const float playerPassCorrectionY = 12.0f;

	this->passParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerPassCorrectionY);
	this->passSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerPassCorrectionY);
	this->passButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->passButton->setIconOffset(Vec2(0.0f, playerPassCorrectionY));
	this->passPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->passPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->passPanel->getContentSize().height / 2.0
	);
	this->passLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyPassSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyPassParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);

	// Last stand
	const float playerLastStandCorrectionY = 6.0f;

	this->lastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerLastStandCorrectionY);
	this->lastStandSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerLastStandCorrectionY);
	this->lastStandButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->lastStandButton->setIconOffset(Vec2(0.0f, playerLastStandCorrectionY));
	this->lastStandPanel->setPosition(
		visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX - this->lastStandPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f - this->lastStandPanel->getContentSize().height / 2.0
	);
	this->lastStandLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 64.0f);

	this->enemyLastStandSprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);
	this->enemyLastStandParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - Config::passButtonOffsetY);

	// Claim victory
	const float playerClaimVictoryCorrectionY = 4.0f;

	this->claimVictoryParticles->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerClaimVictoryCorrectionY);
	this->claimVictorySprite->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + playerClaimVictoryCorrectionY);
	this->claimVictoryButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->claimVictoryButton->setIconOffset(Vec2(0.0f, playerClaimVictoryCorrectionY));
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
	GameState::updateState(gameState, GameState::StateType::Pass);
}

void StatePass::hideAndDisableAllButtons()
{
	// Pass
	this->passParticles->setVisible(false);
	this->passSprite->runAction(FadeTo::create(0.25f, 0));
	this->passButton->runAction(FadeTo::create(0.25f, 0));
	this->passButton->disableInteraction();
	this->passButton->setClickCallback(nullptr);
	this->passButton->setMouseOverCallback(nullptr);
	this->passButton->setMouseOutCallback(nullptr);
	this->onPassMouseOut();

	// Last stand
	this->lastStandParticles->setVisible(false);
	this->lastStandSprite->runAction(FadeTo::create(0.25f, 0));
	this->lastStandButton->runAction(FadeTo::create(0.25f, 0));
	this->lastStandButton->disableInteraction();
	this->lastStandButton->setClickCallback(nullptr);
	this->lastStandButton->setMouseOverCallback(nullptr);
	this->lastStandButton->setMouseOutCallback(nullptr);
	this->onLastStandMouseOut();

	// Claim victory
	this->claimVictoryParticles->setVisible(false);
	this->claimVictorySprite->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryButton->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryButton->disableInteraction();
	this->claimVictoryButton->setClickCallback(nullptr);
	this->claimVictoryButton->setMouseOverCallback(nullptr);
	this->claimVictoryButton->setMouseOutCallback(nullptr);
	this->onClaimVictoryMouseOut();
}

void StatePass::hideOpponenentPassSprites()
{
	this->enemyPassSprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyPassParticles->setVisible(false);

	this->enemyLastStandSprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyLastStandParticles->setVisible(false);

	this->enemyClaimVictorySprite->runAction(FadeTo::create(0.25f, 0));
	this->enemyClaimVictoryParticles->setVisible(false);
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

	switch (gameState->stateType)
	{
		case GameState::StateType::RoundEnd:
		{
			this->currentVisiblePlayerButton = nullptr;
			this->playerChoiceLocked = false;

			this->hideAndDisableAllButtons();
			this->hideOpponenentPassSprites();

			break;
		}
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			if (gameState->turn == GameState::Turn::Player)
			{
				if (gameState->isPlayerLastStandCondition())
				{
					this->enableLastStandButtonInteraction(gameState);
				}
				else if (gameState->isPlayerClaimVictoryCondition())
				{
					this->enableClaimVictoryButtonInteraction(gameState);
				}
				else
				{
					this->enablePassButtonInteraction(gameState);
				}
			}

			break;
		}
		default:
		{
			// Dynamically show the correct user button, if they have not already clicked pass
			if (!this->playerChoiceLocked)
			{
				if (gameState->isPlayerLastStandCondition())
				{
					if (this->currentVisiblePlayerButton != this->lastStandButton)
					{
						this->currentVisiblePlayerButton = currentVisiblePlayerButton;
						this->hideAndDisableAllButtons();
					}

					this->showLastStandButton();
				}
				else if (gameState->isPlayerClaimVictoryCondition())
				{
					if (this->currentVisiblePlayerButton != this->claimVictoryButton)
					{
						this->currentVisiblePlayerButton = currentVisiblePlayerButton;
						this->hideAndDisableAllButtons();
					}

					this->showClaimVictoryButton();
				}
				else
				{
					if (this->currentVisiblePlayerButton != this->passButton)
					{
						this->currentVisiblePlayerButton = currentVisiblePlayerButton;
						this->hideAndDisableAllButtons();
					}

					this->showPassButton();
				}
			}

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
			this->hideAndDisableAllButtons();
			this->playerChoiceLocked = true;

			// Note: We play these on state enter rather than on button click, because button click is not the only way to enter this state
			if (gameState->isPlayerLastStandCondition())
			{
				this->lastStandParticles->setVisible(true);
				this->lastStandSprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_LastStand);
			}
			else if (gameState->isPlayerClaimVictoryCondition())
			{
				this->claimVictoryParticles->setVisible(true);
				this->claimVictorySprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_ClaimVictory);
			}
			else
			{
				this->passParticles->setVisible(true);
				this->passSprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_Pass);
			}

			gameState->playerPassed = true;
			break;
		case GameState::Turn::Enemy:
		{
			if (gameState->isEnemyLastStandCondition())
			{
				this->enemyLastStandParticles->setVisible(true);
				this->enemyLastStandSprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_LastStand);
			}
			else if (gameState->isEnemyClaimVictoryCondition())
			{
				this->enemyClaimVictoryParticles->setVisible(true);
				this->enemyClaimVictorySprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_ClaimVictory);
			}
			else
			{
				this->enemyPassParticles->setVisible(true);
				this->enemyPassSprite->runAction(FadeTo::create(0.25f, 255));

				SoundManager::playSoundResource(Resources::Sounds_Hexus_Pass);
			}

			gameState->enemyPassed = true;

			break;
		}
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
