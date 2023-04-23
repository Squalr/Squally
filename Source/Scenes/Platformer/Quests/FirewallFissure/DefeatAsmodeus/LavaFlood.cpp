#include "LavaFlood.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/PrincessDawn.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Physics/Lifts/CartLift.h"
#include "Objects/Platformer/Interactables/Computer/Computer.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaFlood::MapKeyQuest = "lava-flood";
const std::string LavaFlood::MapEventPowerRestored = "lava-flooded";

LavaFlood* LavaFlood::create(GameObject* owner, QuestLine* questLine)
{
	LavaFlood* instance = new LavaFlood(owner, questLine);

	instance->autorelease();

	return instance;
}

LavaFlood::LavaFlood(GameObject* owner, QuestLine* questLine) : super(owner, questLine, LavaFlood::MapKeyQuest, false)
{
}

LavaFlood::~LavaFlood()
{
}

void LavaFlood::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (questState == QuestState::Complete)
	{
		this->applyLavaFlood();
	}
	
	this->listenForMapEvent(LavaFlood::MapEventPowerRestored, [=](ValueMap)
	{
		Objectives::SetCurrentObjective(ObjectiveKeys::DMReturnToPrincessDawn);
		this->complete();
	});
}

void LavaFlood::onActivate(bool isActiveThroughSkippable)
{
}

void LavaFlood::onComplete()
{
	this->applyLavaFlood();
}

void LavaFlood::onSkipped()
{
}

void LavaFlood::applyLavaFlood()
{
	/*
	ObjectEvents::QueryObjects<Computer>([=](Computer* computer)
	{
		computer->turnOn();
	}, Computer::MapKey);
	*/
}
