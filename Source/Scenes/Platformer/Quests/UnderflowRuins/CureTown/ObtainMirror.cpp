#include "ObtainMirror.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/GuanoPetrified/RopedMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Petrification/GuanoUnpetrifiedBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ObtainMirror::MapKeyQuest = "obtain-mirror";

ObtainMirror* ObtainMirror::create(GameObject* owner, QuestLine* questLine)
{
	ObtainMirror* instance = new ObtainMirror(owner, questLine);

	instance->autorelease();

	return instance;
}

ObtainMirror::ObtainMirror(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ObtainMirror::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->guanoPetrified = nullptr;
	this->squally = nullptr;
	this->inventory = nullptr;
	this->doBehaviorAttach = false;
}

ObtainMirror::~ObtainMirror()
{
}

void ObtainMirror::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<GuanoPetrified>(this, [=](GuanoPetrified* guanoPetrified)
	{
		this->guanoPetrified = guanoPetrified;
	}, GuanoPetrified::MapKey);

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;

		this->attachGuanoSpawnBehaviors();
	}, Guano::MapKey);
}

void ObtainMirror::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(this->owner->getListenEvent(), [=](ValueMap args)
	{
		this->runCinematicSequence();
	});
}

void ObtainMirror::onComplete()
{
}

void ObtainMirror::onSkipped()
{
}

void ObtainMirror::runCinematicSequence()
{
	// IMPORTANT: Add a redundant save now to prevent a timing issue where the user pauses and quits in the middle of this cinematic.
	SaveManager::SaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
	
	if (this->inventory == nullptr)
	{
		this->regainGuano();
		return;
	}

	this->freeGuano();

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			Item* mirror = this->inventory->getItemOfType<MedusaMirror>();

			PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(mirror));
		}),
		nullptr
	));
}

void ObtainMirror::freeGuano()
{
	if (this->guanoPetrified == nullptr)
	{
		return;
	}

	this->doBehaviorAttach = true;
	
	this->guanoPetrified->watchForAttachedBehavior<RopedMovementBehavior>([=](RopedMovementBehavior* ropedMovementBehavior)
	{
		ropedMovementBehavior->detach();
	});

	const float RotationAngle = 2.5f;
	const float RotationSpeed = 0.05f;
	const float HalfRotationSpeed = RotationSpeed / 2.0f;
	const float RumbleTime = 0.55f;
	const int Rumbles = int(std::round((RumbleTime - RotationSpeed) / RotationSpeed));

	this->guanoPetrified->runAction(Sequence::create(
		EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, RotationAngle)),
		Repeat::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationAngle)),
			EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationAngle)),
			nullptr
		), Rumbles),
		EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, 0.0f)),
		CallFunc::create([=]()
		{
			this->regainGuano();
		}),
		nullptr
	));
}

void ObtainMirror::regainGuano()
{
	if (this->guanoPetrified != nullptr)
	{
		Vec2 coords = GameUtils::getWorldCoords(this->guanoPetrified, false);

		this->squally->setState(StateKeys::NewHelperSpawnX, Value(coords.x));
		this->squally->setState(StateKeys::NewHelperSpawnY, Value(coords.y));
	}

	this->squally->setState(StateKeys::NotifyNewHelper, Value(false));
	this->squally->setState(StateKeys::CurrentHelper, Value(Guano::MapKey));
}

void ObtainMirror::attachGuanoSpawnBehaviors()
{
	if (!this->doBehaviorAttach || this->guano == nullptr)
	{
		return;
	}

	GuanoUnpetrifiedBehavior* unpetrifyBehavior = GuanoUnpetrifiedBehavior::create(this->guano);

	this->guano->attachBehavior(unpetrifyBehavior);

	unpetrifyBehavior->unpetrify();
}
