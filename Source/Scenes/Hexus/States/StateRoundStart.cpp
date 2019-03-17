#include "StateRoundStart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/SoundManager.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

StateRoundStart* StateRoundStart::create()
{
	StateRoundStart* instance = new StateRoundStart();

	instance->autorelease();

	return instance;
}

StateRoundStart::StateRoundStart() : super(GameState::StateType::RoundStart)
{
}

StateRoundStart::~StateRoundStart()
{
}

void StateRoundStart::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateRoundStart::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->turnNumber = 0;
	gameState->playerPassed = false;
	gameState->enemyPassed = false;

	SoundManager::playSoundResource(SoundResources::Hexus_Medieval_War_Horn);

	this->runAction(Sequence::create(
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::DrawInitialCards);
		}),
		nullptr
	));
}

void StateRoundStart::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateRoundStart::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
