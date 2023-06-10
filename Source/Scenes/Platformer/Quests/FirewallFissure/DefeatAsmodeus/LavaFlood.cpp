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
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Enemies/FirewallFissure/Asmodeus.h"
#include "Entities/Platformer/Npcs/DataMines/PrincessDawn.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Physics/Lifts/CartLift.h"
#include "Objects/Platformer/Interactables/Computer/Computer.h"
#include "Objects/Platformer/Liquids/Lava.h"
#include "Objects/Platformer/Decor/LavaFall.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaFlood::MapKeyQuest = "lava-flood";
const std::string LavaFlood::MapEventLavaFlooded = "lava-flooded";

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
		this->applyLavaFlood(true, false);
	}
	
	this->listenForMapEventOnce(LavaFlood::MapEventLavaFlooded, [=](ValueMap)
	{
		Objectives::SetCurrentObjective(ObjectiveKeys::FFFindAsmodeus);
		this->complete();
	});
}

void LavaFlood::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	bool isFlooded = !isActiveThroughSkippable;
	bool animate = isInitialActivation;
}

void LavaFlood::onComplete()
{
	this->applyLavaFlood(true, true);
}

void LavaFlood::onSkipped()
{
}

void LavaFlood::applyLavaFlood(bool isFlooded, bool animate)
{
	if (isFlooded)
	{
		float duration = animate ? 2.0f : 0.0f;
		Vec2 delta = Vec2(0.0f, 144.0f);

		ObjectEvents::QueryObjects<Lava>([=](Lava* lava)
		{
			lava->runAction(EaseSineInOut::create(MoveBy::create(duration, delta)));
		});

		ObjectEvents::QueryObjects<LavaFall>([=](LavaFall* lavaFall)
		{
			lavaFall->runAction(EaseSineInOut::create(MoveBy::create(duration, delta)));
		});

		ObjectEvents::QueryObjects<PlatformerEnemy>([=](PlatformerEnemy* platformerEnemy)
		{
			platformerEnemy->despawn();
		}, "lava-killable");

		ObjectEvents::QueryObjects<Asmodeus>([=](Asmodeus* asmodeus)
		{
			asmodeus->despawn();
		}, Asmodeus::MapKey);
	}
	else
	{
		ObjectEvents::QueryObjects<TerrainObject>([=](TerrainObject* terrainObject)
		{
			terrainObject->despawn();
		}, "revealed-platform");

		ObjectEvents::QueryObjects<Portal>([=](Portal* portal)
		{
			portal->disable();
		}, "revealed-pathway");
	}
}
