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
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/GuanoPetrified/RopedMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Petrification/GuanoUnpetrifyParticleBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Petrification/GuanoUnpetrifySoundBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
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
	this->scrappy = nullptr;
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

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;

		this->attachGuanoSpawnBehaviors();
	}, Scrappy::MapKey);

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
		this->runCinematicSequencePt1();
	});
}

void ObtainMirror::onComplete()
{
}

void ObtainMirror::onSkipped()
{
}

void ObtainMirror::runCinematicSequencePt1()
{
	// IMPORTANT: Add a redundant save now to prevent a timing issue where the user pauses and quits in the middle of this cinematic.
	SaveManager::SaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));

	Objectives::SetCurrentObjective(ObjectiveKeys::URCureTownspeople);
	
	if (this->inventory == nullptr)
	{
		this->regainGuano();
		return;
	}

	this->defer([=]()
	{
		Item* mirror = this->inventory->getItemOfType<MedusaMirror>();

		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(mirror, false));

		this->runCinematicSequencePt2();
	});
}

void ObtainMirror::runCinematicSequencePt2()
{
	if (this->guanoPetrified == nullptr)
	{
		return;
	}
	
	PlatformerEvents::TriggerCinematicHijack();

	this->doBehaviorAttach = true;

	this->guanoPetrified->watchForAttachedBehavior<RopedMovementBehavior>([=](RopedMovementBehavior* ropedMovementBehavior)
	{
		ropedMovementBehavior->detach();
	});

	GuanoUnpetrifySoundBehavior* unpetrifySfxBehavior = GuanoUnpetrifySoundBehavior::create(this->guano);

	this->guanoPetrified->attachBehavior(unpetrifySfxBehavior);

	unpetrifySfxBehavior->unpetrify();

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
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->runCinematicSequencePt3();
		}),
		nullptr
	));
}

void ObtainMirror::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Guano_A_OhNoImDead::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ObtainMirror::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Guano_B_WithAllTheStealing::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ObtainMirror::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Guano_C_YoureNotDead::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runCinematicSequencePt6();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void ObtainMirror::runCinematicSequencePt6()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Guano_D_OhOkay::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceShort(),
		true
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

	GuanoUnpetrifyParticleBehavior* unpetrifyParticleBehavior = GuanoUnpetrifyParticleBehavior::create(this->guano);

	this->guano->attachBehavior(unpetrifyParticleBehavior);

	unpetrifyParticleBehavior->unpetrify();
}
