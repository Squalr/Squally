#include "StateGameExit.h"

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
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StateGameExit* StateGameExit::create()
{
	StateGameExit* instance = new StateGameExit();

	instance->autorelease();

	return instance;
}

StateGameExit::StateGameExit() : super(GameState::StateType::GameExit)
{
}

StateGameExit::~StateGameExit()
{
}

void StateGameExit::onEnter()
{
	super::onEnter();
}

void StateGameExit::initializeListeners()
{
	super::initializeListeners();
}

void StateGameExit::initializePositions()
{
	super::initializePositions();
}

void StateGameExit::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateGameExit::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	GameState::updateState(gameState, GameState::StateType::EmptyState);
}

void StateGameExit::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateGameExit::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
