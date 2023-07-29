#include "StatePass.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Sound/Sound.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StatePass* StatePass::create()
{
	StatePass* instance = new StatePass();

	instance->autorelease();

	return instance;
}

StatePass::StatePass() : super(GameState::StateType::Pass)
{
	// Pass
	this->passSprite = Sprite::create(HexusResources::Flags);

	Node* passContent = Sprite::create(HexusResources::WoodSquareButton);
	Node* passIcon = Sprite::create(HexusResources::Flags);
	
	passContent->addChild(passIcon);

	Node* passContentSelected = Sprite::create(HexusResources::WoodSquareButtonSelected);
	Node* passIconSelected = Sprite::create(HexusResources::FlagsSelected);
	
	passContentSelected->addChild(passIconSelected);
	passIcon->setPosition(Vec2(passContent->getContentSize() / 2.0f) + Vec2(0.0f, 12.0f));
	passIconSelected->setPosition(Vec2(passContentSelected->getContentSize() / 2.0f) + Vec2(0.0f, 12.0f));

	this->passButton = ClickableNode::create(passContent, passContentSelected);
	this->passPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->passLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Pass::create());

	this->passParticles = SmartParticles::create(ParticleResources::Hexus_WhiteAura);
	this->enemyPassSprite = Sprite::create(HexusResources::Flags);
	this->enemyPassParticles = SmartParticles::create(ParticleResources::Hexus_WhiteAura);

	// Last stand
	this->lastStandSprite = Sprite::create(HexusResources::ShieldButton);

	Sprite* lastStandContent = Sprite::create(HexusResources::WoodSquareButton);
	Sprite* lastStandIcon = Sprite::create(HexusResources::ShieldButton);
	
	lastStandContent->addChild(lastStandIcon);

	Sprite* lastStandContentSelected = Sprite::create(HexusResources::WoodSquareButtonSelected);
	Sprite* lastStandIconSelected = Sprite::create(HexusResources::ShieldButtonSelected);
	
	lastStandContentSelected->addChild(lastStandIconSelected);
	lastStandIcon->setPosition(Vec2(lastStandContent->getContentSize() / 2.0f) + Vec2(0.0f, 6.0f));
	lastStandIconSelected->setPosition(Vec2(lastStandContentSelected->getContentSize() / 2.0f) + Vec2(0.0f, 6.0f));

	this->lastStandButton = ClickableNode::create(lastStandContent, lastStandContentSelected);
	this->lastStandPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->lastStandLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_LastStand::create());
	
	this->lastStandParticles = SmartParticles::create(ParticleResources::Hexus_Aura);
	this->enemyLastStandSprite = Sprite::create(HexusResources::ShieldButton);
	this->enemyLastStandParticles = SmartParticles::create(ParticleResources::Hexus_Aura);

	// Claim victory
	this->claimVictorySprite = Sprite::create(HexusResources::Victory);

	Sprite* claimVictoryContent = Sprite::create(HexusResources::WoodSquareButton);
	Sprite* claimVictoryIcon = Sprite::create(HexusResources::Victory);
	
	claimVictoryContent->addChild(claimVictoryIcon);

	Node* claimVictoryContentSelected = Sprite::create(HexusResources::WoodSquareButtonSelected);
	Node* claimVictoryIconSelected = Sprite::create(HexusResources::VictorySelected);
	
	claimVictoryContentSelected->addChild(claimVictoryIconSelected);
	claimVictoryIcon->setPosition(Vec2(claimVictoryContent->getContentSize() / 2.0f) + Vec2(0.0f, 4.0f));
	claimVictoryIconSelected->setPosition(Vec2(claimVictoryContentSelected->getContentSize() / 2.0f) + Vec2(0.0f, 4.0f));

	this->claimVictoryButton = ClickableNode::create(claimVictoryContent, claimVictoryContentSelected);
	this->claimVictoryPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->claimVictoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_ClaimVictory::create());
	
	this->claimVictoryParticles = SmartParticles::create(ParticleResources::Hexus_Aura);
	this->enemyClaimVictorySprite = Sprite::create(HexusResources::Victory);
	this->enemyClaimVictoryParticles = SmartParticles::create(ParticleResources::Hexus_Aura);

	this->passSound = Sound::create(SoundResources::Hexus_Pass);
	this->lastStandSound = Sound::create(SoundResources::Hexus_LastStand);
	this->claimVictorySound = Sound::create(SoundResources::Hexus_ClaimVictory);

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

	this->addChild(this->passSound);
	this->addChild(this->lastStandSound);
	this->addChild(this->claimVictorySound);
}

StatePass::~StatePass()
{
}

void StatePass::onEnter()
{
	super::onEnter();

	this->currentVisiblePlayerButton = nullptr;
	this->playerChoiceLocked = false;
	this->enemyChoiceLocked = false;

	// Default this button to visible
	this->passButton->setOpacity(255);
	this->passSprite->setOpacity(0);
	this->passPanel->setOpacity(0);
	this->passLabel->setOpacity(0);
	this->enemyPassSprite->setOpacity(0);

	this->lastStandButton->setOpacity(0);
	this->lastStandSprite->setOpacity(0);
	this->lastStandPanel->setOpacity(0);
	this->lastStandLabel->setOpacity(0);
	this->enemyLastStandSprite->setOpacity(0);

	this->claimVictoryButton->setOpacity(0);
	this->claimVictorySprite->setOpacity(0);
	this->claimVictoryPanel->setOpacity(0);
	this->claimVictoryLabel->setOpacity(0);
	this->enemyClaimVictorySprite->setOpacity(0);
}

void StatePass::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	// Pass
	const float playerPassCorrectionY = 12.0f;

	this->passParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerPassCorrectionY);
	this->passSprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerPassCorrectionY);
	this->passButton->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY);
	
	this->passPanel->setPosition(
		visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX - this->passPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f - this->passPanel->getContentSize().height / 2.0f
	);
	this->passLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f);

	this->enemyPassSprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);
	this->enemyPassParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);

	// Last stand
	const float playerLastStandCorrectionY = 6.0f;

	this->lastStandParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerLastStandCorrectionY);
	this->lastStandSprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerLastStandCorrectionY);
	this->lastStandButton->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY);
	
	this->lastStandPanel->setPosition(
		visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX - this->lastStandPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f - this->lastStandPanel->getContentSize().height / 2.0f
	);
	this->lastStandLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f);

	this->enemyLastStandSprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);
	this->enemyLastStandParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);

	// Claim victory
	const float playerClaimVictoryCorrectionY = 4.0f;

	this->claimVictoryParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerClaimVictoryCorrectionY);
	this->claimVictorySprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + playerClaimVictoryCorrectionY);
	this->claimVictoryButton->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY);
	
	this->claimVictoryPanel->setPosition(
		visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX - this->claimVictoryPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f - this->claimVictoryPanel->getContentSize().height / 2.0f
	);
	this->claimVictoryLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f + HexusConfig::passButtonOffsetY + 64.0f);

	this->enemyClaimVictorySprite->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);
	this->enemyClaimVictoryParticles->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::passButtonOffsetX, visibleSize.height / 2.0f - HexusConfig::passButtonOffsetY);
}

void StatePass::onPassClick(GameState* gameState)
{
	if (gameState->stateType == GameState::StateType::Neutral)
	{
		GameState::updateState(gameState, GameState::StateType::Pass);
	}
}

void StatePass::hideAndDisableAllButtons()
{
	// Pass
	this->passSprite->runAction(FadeTo::create(0.25f, 0));
	this->passButton->runAction(FadeTo::create(0.25f, 0));
	this->passButton->disableInteraction();
	this->passButton->setMouseClickCallback(nullptr);
	this->passButton->setMouseOverCallback(nullptr);
	this->passButton->setMouseOutCallback(nullptr);
	this->onPassMouseOut();

	// Last stand
	this->lastStandSprite->runAction(FadeTo::create(0.25f, 0));
	this->lastStandButton->runAction(FadeTo::create(0.25f, 0));
	this->lastStandButton->disableInteraction();
	this->lastStandButton->setMouseClickCallback(nullptr);
	this->lastStandButton->setMouseOverCallback(nullptr);
	this->lastStandButton->setMouseOutCallback(nullptr);
	this->onLastStandMouseOut();

	// Claim victory
	this->claimVictorySprite->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryButton->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryButton->disableInteraction();
	this->claimVictoryButton->setMouseClickCallback(nullptr);
	this->claimVictoryButton->setMouseOverCallback(nullptr);
	this->claimVictoryButton->setMouseOutCallback(nullptr);
	this->onClaimVictoryMouseOut();
}

void StatePass::hideOpponenentPassSprites()
{
	this->enemyPassSprite->runAction(FadeTo::create(0.25f, 0));

	this->enemyLastStandSprite->runAction(FadeTo::create(0.25f, 0));

	this->enemyClaimVictorySprite->runAction(FadeTo::create(0.25f, 0));
}

void StatePass::enablePassButtonInteraction(GameState* gameState)
{
	this->passButton->setMouseClickCallback(CC_CALLBACK_0(StatePass::onPassClick, this, gameState));
	this->passButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onPassMouseOver, this));
	this->passButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onPassMouseOut, this));

	if (gameState->stateType == GameState::StateType::Neutral && !gameState->playerPassed)
	{
		this->passButton->enableInteraction();
	}
	else
	{
		this->passButton->disableInteraction();
	}
}

void StatePass::enableLastStandButtonInteraction(GameState* gameState)
{
	this->lastStandButton->setMouseClickCallback(CC_CALLBACK_0(StatePass::onPassClick, this, gameState));
	this->lastStandButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onLastStandMouseOver, this));
	this->lastStandButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onLastStandMouseOut, this));

	if (gameState->stateType == GameState::StateType::Neutral && !gameState->playerPassed)
	{
		this->lastStandButton->enableInteraction();
	}
	else
	{
		this->lastStandButton->disableInteraction();
	}
}

void StatePass::enableClaimVictoryButtonInteraction(GameState* gameState)
{
	this->claimVictoryButton->setMouseClickCallback(CC_CALLBACK_0(StatePass::onPassClick, this, gameState));
	this->claimVictoryButton->setMouseOverCallback(CC_CALLBACK_0(StatePass::onClaimVictoryMouseOver, this));
	this->claimVictoryButton->setMouseOutCallback(CC_CALLBACK_0(StatePass::onClaimVictoryMouseOut, this));

	if (gameState->stateType == GameState::StateType::Neutral && !gameState->playerPassed)
	{
		this->claimVictoryButton->enableInteraction();
	}
	else
	{
		this->claimVictoryButton->disableInteraction();
	}
}

void StatePass::showPassButton()
{
	this->passButton->runAction(FadeTo::create(0.25f, 255));
	this->passSprite->runAction(FadeTo::create(0.25f, 0));
}

void StatePass::showLastStandButton()
{
	this->lastStandButton->runAction(FadeTo::create(0.25f, 255));
	this->lastStandSprite->runAction(FadeTo::create(0.25f, 0));
}

void StatePass::showClaimVictoryButton()
{
	this->claimVictoryButton->runAction(FadeTo::create(0.25f, 255));
	this->claimVictorySprite->runAction(FadeTo::create(0.25f, 0));
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

void StatePass::onAfterAnyStateChange(GameState* gameState)
{
	super::onAfterAnyStateChange(gameState);

	this->lastStandParticles->stop(5.0f);
	this->claimVictoryParticles->stop(5.0f);
	this->passParticles->stop(5.0f);
	this->enemyLastStandParticles->stop(5.0f);
	this->enemyClaimVictoryParticles->stop(5.0f);
	this->enemyPassParticles->stop(5.0f);

	if (gameState->playerPassed && !this->playerChoiceLocked)
	{
		this->playerChoiceLocked = true;
		this->hideAndDisableAllButtons();

		if (gameState->isPlayerLastStandCondition())
		{
			this->lastStandParticles->start();
			this->lastStandSprite->runAction(FadeTo::create(0.25f, 255));
		}
		else if (gameState->isPlayerClaimVictoryCondition())
		{
			this->claimVictoryParticles->start();
			this->claimVictorySprite->runAction(FadeTo::create(0.25f, 255));
		}
		else
		{
			this->passParticles->start();
			this->passSprite->runAction(FadeTo::create(0.25f, 255));
		}
	}

	if (gameState->enemyPassed && !this->enemyChoiceLocked)
	{
		this->enemyChoiceLocked = true;

		if (gameState->isEnemyLastStandCondition())
		{
			this->enemyLastStandSprite->runAction(FadeTo::create(0.25f, 255));
			this->enemyLastStandParticles->start();
		}
		else if (gameState->isEnemyClaimVictoryCondition())
		{
			this->enemyClaimVictorySprite->runAction(FadeTo::create(0.25f, 255));
			this->enemyClaimVictoryParticles->start();
		}
		else
		{
			this->enemyPassSprite->runAction(FadeTo::create(0.25f, 255));
			this->enemyPassParticles->start();
		}
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::GameStart:
		case GameState::StateType::RoundEnd:
		{
			this->currentVisiblePlayerButton = nullptr;
			this->playerChoiceLocked = false;
			this->enemyChoiceLocked = false;

			this->hideAndDisableAllButtons();
			this->hideOpponenentPassSprites();

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
						this->currentVisiblePlayerButton = this->lastStandButton;
						this->hideAndDisableAllButtons();
					}

					this->showLastStandButton();
				}
				else if (gameState->isPlayerClaimVictoryCondition())
				{
					if (this->currentVisiblePlayerButton != this->claimVictoryButton)
					{
						this->currentVisiblePlayerButton = this->claimVictoryButton;
						this->hideAndDisableAllButtons();
					}

					this->showClaimVictoryButton();
				}
				else
				{
					if (this->currentVisiblePlayerButton != this->passButton)
					{
						this->currentVisiblePlayerButton = this->passButton;
						this->hideAndDisableAllButtons();
					}

					this->showPassButton();
				}
			}

			break;
		}
	}

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
}

void StatePass::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StatePass::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			// Note: We play these on state enter rather than on button click, because button click is not the only way to enter this state
			if (gameState->isPlayerLastStandCondition())
			{
				this->lastStandSound->play();
			}
			else if (gameState->isPlayerClaimVictoryCondition())
			{
				this->claimVictorySound->play();
			}
			else
			{
				this->passSound->play();
			}

			gameState->playerPassed = true;
			break;
		case GameState::Turn::Enemy:
		{
			if (gameState->isEnemyLastStandCondition())
			{
				this->lastStandSound->play();
			}
			else if (gameState->isEnemyClaimVictoryCondition())
			{
				this->claimVictorySound->play();
			}
			else
			{
				this->passSound->play();
			}

			gameState->enemyPassed = true;

			break;
		}
		default:
			break;
	}

	this->runAction(Sequence::create(
		DelayTime::create(HexusConfig::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
		}),
		nullptr
	));
}

void StatePass::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StatePass::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
