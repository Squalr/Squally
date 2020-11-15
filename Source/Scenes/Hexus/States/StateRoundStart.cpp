#include "StateRoundStart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/Sound.h"
#include "Scenes/Hexus/HexusConfig.h"

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
	this->roundStartSound = Sound::create(SoundResources::Hexus_Medieval_War_Horn);

	this->addChild(this->roundStartSound);
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

	this->roundStartSound->play();

	gameState->turnNumber = 0;
	gameState->playerPassed = false;
	gameState->enemyPassed = false;

	this->runAction(Sequence::create(
		DelayTime::create(HexusConfig::bannerDisplayDuration),
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
