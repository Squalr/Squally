#include "Banners.h"

Banners* Banners::create()
{
	Banners* instance = new Banners();

	instance->autorelease();

	return instance;
}

Banners::Banners()
{
	this->statusBanner = LayerColor::create(Color4B(0, 0, 0, 127), 1920.0f, 144.0f);
	this->statusLabel = Label::create("", Localization::getMainFont(), 48.0f);
	this->playerBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->playerBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->enemyBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->enemyBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->roundBanner1 = Sprite::create(Resources::Minigames_Hexus_RoundBanner);
	this->roundBanner2 = Sprite::create(Resources::Minigames_Hexus_RoundBanner);

	this->statusBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusBanner->setOpacity(0);
	this->statusLabel->setOpacity(0);

	this->playerBanner1->setOpacity(0);
	this->playerBanner2->setOpacity(0);
	this->enemyBanner1->setOpacity(0);
	this->enemyBanner2->setOpacity(0);
	this->roundBanner1->setOpacity(0);
	this->roundBanner2->setOpacity(0);

	this->addChild(this->statusBanner);
	this->addChild(this->statusLabel);
	this->addChild(this->playerBanner1);
	this->addChild(this->playerBanner2);
	this->addChild(this->enemyBanner1);
	this->addChild(this->enemyBanner2);
	this->addChild(this->roundBanner1);
	this->addChild(this->roundBanner2);
}

Banners::~Banners()
{
}

void Banners::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statusBanner->setPosition(0.0f, visibleSize.height / 2.0f - this->statusBanner->getContentSize().height / 2 + 320.0f);
	this->statusLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
	this->playerBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->roundBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->roundBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void Banners::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->previousStateType != gameState->stateType) {
		this->hideAllBanners();
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::RoundStart: {
			if (this->activeGameState->round == 0) {
				GameState::updateState(this->activeGameState, GameState::StateType::DrawInitialCards);
			} else {
				this->displayRoundStartBannner();
				this->runAction(Sequence::create(
					DelayTime::create(Config::bannerFadeSpeed),
					DelayTime::create(Config::bannerDisplayDuration),
					CallFunc::create([=] {
						GameState::updateState(this->activeGameState, GameState::StateType::ControlReplaceCards);
					}),
					nullptr
				));	
			}
			
			break;
		}
		case GameState::StateType::FirstSideBanner:
		case GameState::StateType::TurnBanner:
		{
			if (gameState->showPassBanner)
			{
				if (gameState->turn == GameState::Turn::Enemy && !gameState->enemyPass)
				{
					this->displayEnemyTurnBanner();
				}
				else if (gameState->turn == GameState::Turn::Player && !gameState->playerPass)
				{
					this->displayPlayerTurnBanner();
				}

				this->runAction(Sequence::create(
					DelayTime::create(Config::bannerFadeSpeed),
					DelayTime::create(Config::bannerDisplayDuration),
					CallFunc::create([=] {
						GameState::updateState(this->activeGameState, GameState::StateType::ControlNeutral);
					}),
					nullptr
				));

				gameState->showPassBanner = false;
			}
			else
			{
				this->runAction(Sequence::create(
					CallFunc::create([=] {
						GameState::updateState(this->activeGameState, GameState::StateType::ControlNeutral);
					}),
					nullptr
				));
			}

			break;
		}
		case GameState::StateType::ControlReplaceCards:
			this->displayCardReplaceBanner();
			break;
		case GameState::StateType::Win:
		case GameState::StateType::Lose:
			this->displayWinLoseBanner();
			break;	
		default:
			break;
		}
}

void Banners::displayPlayerTurnBanner()
{
	if (this->activeGameState->previousStateType == GameState::CoinFlip) {
		this->activeGameState->bannerMessage = "YOU GO FIRST";
	} else {
		this->activeGameState->bannerMessage = "YOUR TURN";
	}

	this->statusLabel->setString(this->activeGameState->bannerMessage);
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));

	this->playerBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->playerBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
}

void Banners::displayEnemyTurnBanner()
{
	if (this->activeGameState->previousStateType == GameState::CoinFlip) {
		this->activeGameState->bannerMessage = "OPPONENT GOES FIRST";
	} else {
		this->activeGameState->bannerMessage = "OPPONENT'S TURN";
	}

	this->statusLabel->setString(this->activeGameState->bannerMessage);
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));

	this->enemyBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->enemyBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
}

void Banners::displayWinLoseBanner()
{
	if (this->activeGameState->stateType == GameState::Win) {
		this->activeGameState->bannerMessage = "VICTORY!";
	} else {
		this->activeGameState->bannerMessage = "DEFEAT!";
	}

	this->statusLabel->setString(this->activeGameState->bannerMessage);
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
}

void Banners::displayRoundStartBannner()
{
	this->activeGameState->bannerMessage = this->activeGameState->round >= 2 ? "FINAL ROUND" : "NEXT ROUND";

	this->statusLabel->setString(this->activeGameState->bannerMessage);
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::roundBannerDisplayDuration),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));

	this->roundBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->roundBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
}

void Banners::displayCardReplaceBanner()
{
	this->activeGameState->bannerMessage = 
		"REMAINING CARD REPLACEMENTS: " + std::to_string(this->activeGameState->cardReplaceCount);

	this->statusLabel->setString(this->activeGameState->bannerMessage);
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
}

void Banners::hideAllBanners()
{
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
	this->roundBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
	this->roundBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
	this->playerBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->playerBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->enemyBanner1->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));
	this->enemyBanner2->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		DelayTime::create(Config::bannerDisplayDuration),
		nullptr
	));

	this->activeGameState->bannerMessage = "";
}
