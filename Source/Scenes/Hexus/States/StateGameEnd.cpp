#include "StateGameEnd.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Analytics/AnalyticsCategories.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Leave.h"

using namespace cocos2d;

StateGameEnd* StateGameEnd::create()
{
	StateGameEnd* instance = new StateGameEnd();

	instance->autorelease();

	return instance;
}

StateGameEnd::StateGameEnd() : StateBase(GameState::StateType::GameEnd)
{
	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->backButton->setOpacity(0);

	this->addChild(this->backButton);
}

StateGameEnd::~StateGameEnd()
{
}

void StateGameEnd::onEnter()
{
	StateBase::onEnter();

	this->backButton->setOpacity(0);
}

void StateGameEnd::initializeListeners()
{
	StateBase::initializeListeners();
}

void StateGameEnd::initializePositions()
{
	StateBase::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void StateGameEnd::onBackClick(MenuSprite* menuSprite, GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::EmptyState);

	std::string winsKey = HexusOpponentData::winsPrefix + gameState->opponentData->enemyNameKey;
	std::string lossesKey = HexusOpponentData::lossesPrefix + gameState->opponentData->enemyNameKey;

	Analytics::sendEvent(AnalyticsCategories::Hexus, "game_duration", gameState->opponentData->enemyNameKey, gameState->gameDurationInSeconds);
	bool isDraw = gameState->playerLosses >= 2 && gameState->enemyLosses >= 2;
	bool isWin = gameState->playerLosses < 2 && gameState->enemyLosses >= 2;

	if (isDraw)
	{
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::saveGlobalData(lossesKey, cocos2d::Value(losses));

		// Analytics for losing
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyNameKey, losses);

		// Half the reward for a draw
		NavigationEvents::navigateHexusRewards(NavigationEvents::NavigateHexusRewardArgs(gameState->opponentData->reward / 2, true));
	}
	else if (isWin)
	{
		int wins = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt();

		SaveManager::saveGlobalData(winsKey, cocos2d::Value(wins));

		if (!SaveManager::hasGlobalData(winsKey) && !SaveManager::hasGlobalData(lossesKey))
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyNameKey, 1);
		}

		// Analytics for first win
		if (wins == 1)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "attempts_for_first_win", gameState->opponentData->enemyNameKey, losses + wins);
		}

		// Analytics for winning
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_wins", gameState->opponentData->enemyNameKey, wins);

		NavigationEvents::navigateHexusRewards(NavigationEvents::NavigateHexusRewardArgs(gameState->opponentData->reward, false));
	}
	else
	{
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::saveGlobalData(lossesKey, cocos2d::Value(losses));

		if (!SaveManager::hasGlobalData(winsKey) && !SaveManager::hasGlobalData(lossesKey))
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyNameKey, 0);
		}

		// Analytics for losing
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyNameKey, losses);

		NavigationEvents::navigateBack();
	}
}

void StateGameEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateGameEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	if (gameState->playerLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Defeat);
	}
	else if (gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Victory);
	}

	this->backButton->enableInteraction(0);
	this->backButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));
	this->backButton->setClickCallback(CC_CALLBACK_1(StateGameEnd::onBackClick, this, gameState));
}

void StateGameEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateGameEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	this->backButton->disableInteraction(0);
	this->backButton->setClickCallback(nullptr);
}
