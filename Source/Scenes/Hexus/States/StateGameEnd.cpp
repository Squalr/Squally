#include "StateGameEnd.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Analytics/AnalyticsCategories.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StateGameEnd* StateGameEnd::create()
{
	StateGameEnd* instance = new StateGameEnd();

	instance->autorelease();

	return instance;
}

StateGameEnd::StateGameEnd() : super(GameState::StateType::GameEnd)
{
	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel* backButtonLabelHover = backButtonLabel->clone();

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);
	this->defeatSound = Sound::create(SoundResources::Hexus_Defeat);
	this->victorySound = Sound::create(SoundResources::Hexus_Victory);

	this->backButton->setOpacity(0);

	this->addChild(this->backButton);
	this->addChild(this->defeatSound);
	this->addChild(this->victorySound);
}

StateGameEnd::~StateGameEnd()
{
}

void StateGameEnd::onEnter()
{
	super::onEnter();

	this->backButton->setOpacity(0);
}

void StateGameEnd::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE, InputEvents::KeyCode::KEY_ENTER }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this) || !this->backButton->canInteract())
		{
			return;
		}

		args->handle();

		this->backButton->interact();
	});
}

void StateGameEnd::initializePositions()
{
	super::initializePositions();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backButton->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - 196.0f);
}

void StateGameEnd::onBackClick(GameState* gameState)
{
	this->backButton->disableInteraction(0);
	this->backButton->setMouseClickCallback(nullptr);

	std::string winsKey = HexusOpponentData::winsPrefix + gameState->opponentData->enemyAnalyticsIdentifier;
	std::string lossesKey = HexusOpponentData::lossesPrefix + gameState->opponentData->enemyAnalyticsIdentifier;

	Analytics::sendEvent(AnalyticsCategories::Hexus, "game_duration", gameState->opponentData->enemyAnalyticsIdentifier, gameState->gameDurationInSeconds);
	bool isDraw = gameState->playerLosses >= 2 && gameState->enemyLosses >= 2;
	bool isWin = gameState->playerLosses < 2 && gameState->enemyLosses >= 2;

	if (isDraw)
	{
		int losses = SaveManager::GetGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::SaveGlobalData(lossesKey, cocos2d::Value(losses));

		// Analytics for losing (as a tie)
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyAnalyticsIdentifier, losses);
		
		if (gameState->opponentData->onRoundEnd != nullptr)
		{
			gameState->opponentData->onRoundEnd(HexusOpponentData::Result::Draw);
		}
	}
	else if (isWin)
	{
		int wins = SaveManager::GetGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;
		int losses = SaveManager::GetGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt();

		SaveManager::SaveGlobalData(winsKey, cocos2d::Value(wins));

		if (wins == 1 && losses == 0)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyAnalyticsIdentifier, 1);
		}

		if (wins == 1)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "attempts_for_first_win", gameState->opponentData->enemyAnalyticsIdentifier, losses + wins);
		}

		// Analytics for winning
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_wins", gameState->opponentData->enemyAnalyticsIdentifier, wins);

		if (gameState->opponentData->onRoundEnd != nullptr)
		{
			gameState->opponentData->onRoundEnd(HexusOpponentData::Result::Win);
		}
	}
	else
	{
		int wins = SaveManager::GetGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt();
		int losses = SaveManager::GetGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::SaveGlobalData(lossesKey, cocos2d::Value(losses));

		if (wins == 0 && losses == 1)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyAnalyticsIdentifier, 0);
		}

		// Analytics for losing
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyAnalyticsIdentifier, losses);

		if (gameState->opponentData->onRoundEnd != nullptr)
		{
			gameState->opponentData->onRoundEnd(HexusOpponentData::Result::Loss);
		}
	}

	GameState::updateState(gameState, GameState::StateType::GameExit);
	HexusEvents::TriggerExitHexus(HexusEvents::HexusExitArgs());
}

void StateGameEnd::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateGameEnd::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	if (gameState->playerLosses >= 2)
	{
		this->defeatSound->play();
	}
	else if (gameState->enemyLosses >= 2)
	{
		this->victorySound->play();
	}

	this->backButton->enableInteraction(0);
	this->backButton->runAction(FadeTo::create(HexusConfig::replaceEndButtonFadeSpeed, 255));
	this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onBackClick(gameState);
	});
}

void StateGameEnd::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateGameEnd::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
