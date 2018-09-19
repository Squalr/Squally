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

	this->statusBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusBanner->setOpacity(0);
	this->statusLabel->setOpacity(0);

	this->playerBanner1->setOpacity(0);
	this->playerBanner2->setOpacity(0);
	this->enemyBanner1->setOpacity(0);
	this->enemyBanner2->setOpacity(0);

	this->addChild(this->statusBanner);
	this->addChild(this->statusLabel);
	this->addChild(this->playerBanner1);
	this->addChild(this->playerBanner2);
	this->addChild(this->enemyBanner1);
	this->addChild(this->enemyBanner2);
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
}

void Banners::onStateChange(GameState* gameState)
{
	this->updateBanner(gameState);
}

void Banners::updateBanner(GameState* gameState)
{
	CallFunc* stateTransition = nullptr;

	switch (gameState->stateType)
	{
	case GameState::StateType::FirstSideBanner:
		if (gameState->turn == GameState::Turn::Enemy)
		{
			gameState->bannerMessage = "OPPONENT GOES FIRST";
		}
		else if (gameState->turn == GameState::Turn::Player)
		{
			gameState->bannerMessage = "YOU GO FIRST";
		}
		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::ControlNeutral);
		});
		break;
	case GameState::StateType::ControlReplaceCards:
		gameState->bannerMessage = "REMAINING CARD REPLACEMENTS: " + std::to_string(gameState->cardReplaceCount);
		break;
	case GameState::StateType::TurnBanner:
		if (gameState->turn == GameState::Turn::Enemy)
		{
			gameState->bannerMessage = "OPPONENT'S TURN";
		}
		else if (gameState->turn == GameState::Turn::Player)
		{
			gameState->bannerMessage = "YOUR TURN";
		}

		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::ControlNeutral);
		});
		break;
	default:
		stateTransition = CallFunc::create([](){});
		break;
	}

	this->statusLabel->setString(gameState->bannerMessage);

	switch (gameState->stateType)
	{
		case GameState::StateType::FirstSideBanner:
		case GameState::StateType::TurnBanner:
		case GameState::StateType::ControlReplaceCards:
			// Initial fade in if just entering a banner state
			switch (gameState->previousStateType)
			{
				case GameState::StateType::FirstSideBanner:
				case GameState::StateType::TurnBanner:
				case GameState::StateType::ControlReplaceCards:
					break;
				default:
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

					if (gameState->stateType == GameState::StateType::FirstSideBanner || gameState->stateType == GameState::StateType::TurnBanner)
					{
						if (gameState->turn == GameState::Turn::Player)
						{
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
						else if (gameState->turn == GameState::Turn::Enemy)
						{
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
					}

					break;
			}

			// New state transition
			this->runAction(Sequence::create(
				DelayTime::create(Config::bannerDisplayDuration),
				stateTransition,
				nullptr
			));
		break;
		default:
			// Fade banner out on new gamestate
			switch (gameState->previousStateType)
			{
				case GameState::StateType::FirstSideBanner:
				case GameState::StateType::TurnBanner:
				case GameState::StateType::ControlReplaceCards:
					this->statusLabel->runAction(Sequence::create(
						FadeTo::create(Config::bannerFadeSpeed, 0),
						nullptr
					));
					this->statusBanner->runAction(Sequence::create(
						FadeTo::create(Config::bannerFadeSpeed, 0),
						nullptr
					));

					if (gameState->previousStateType == GameState::StateType::FirstSideBanner || gameState->previousStateType == GameState::StateType::TurnBanner)
					{
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
					}
				break;
				default:
					break;
			}
			break;
	}
	
	gameState->bannerMessage = "";
}
