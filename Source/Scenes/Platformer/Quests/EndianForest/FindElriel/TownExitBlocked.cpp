#include "TownExitBlocked.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/Npcs/EndianForest/Bard.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TownExitBlocked::MapKeyQuest = "town-exit-blocked";
const std::string TownExitBlocked::TagBlockedExit = "blocked-exit";

TownExitBlocked* TownExitBlocked::create(GameObject* owner, QuestLine* questLine)
{
	TownExitBlocked* instance = new TownExitBlocked(owner, questLine);

	instance->autorelease();

	return instance;
}

TownExitBlocked::TownExitBlocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TownExitBlocked::MapKeyQuest, false)
{
	this->dialogueCooldown = 0.0f;
	this->isEngagedInDialogue = false;
	this->chiron = dynamic_cast<Chiron*>(owner);
	this->bard = nullptr;
	this->squally = nullptr;
}

TownExitBlocked::~TownExitBlocked()
{
}

void TownExitBlocked::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void TownExitBlocked::onLoad(QuestState questState)
{
	if (questState == QuestState::Complete)
	{
		this->defer([=]()
		{
			this->chiron->despawn();
		});
	}
	else
	{
		this->defer([=]()
		{
			this->attachChironBehavior();
		});

		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			this->squally = squally;
		}, Squally::MapKey);

		ObjectEvents::WatchForObject<Bard>(this, [=](Bard* bard)
		{
			this->bard = bard;

			this->attachBardBehavior();

		}, Bard::MapKey);

		ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
		{
			this->townExitPortal = portal;
			this->townExitPortal->disable();
		}, TownExitBlocked::TagBlockedExit);
	}
}

void TownExitBlocked::onActivate(bool isActiveThroughSkippable)
{
}

void TownExitBlocked::attachChironBehavior()
{
	this->chiron->attachBehavior(LookAtSquallyBehavior::create(this->chiron));

	this->chironCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->chiron->getEntitySize(), 8.0f),
		(CollisionType)PlatformerCollisionType::Cinematic,
		CollisionObject::Properties(false, false)
	);
	this->chironCollision->setPosition(this->chiron->getCollisionOffset() + Vec2(0.0f, this->chiron->getEntitySize().height / 2.0f));

	this->chiron->addChild(this->chironCollision);

	this->chironCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerMovement, (int)PlatformerCollisionType::Hover }, [=](CollisionData collisionData)
	{
		if (!this->isEngagedInDialogue && this->dialogueCooldown <= 0.0f)
		{
			this->isEngagedInDialogue = true;

			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Chiron_A_CantLeaveTown::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->chiron, true)
				),
				[=]()
				{
					this->isEngagedInDialogue = false;
					this->dialogueCooldown = 6.0f;
				},
				SoundResources::Platformer_Entities_Generic_ChatterAnnoyed1
			));
		}
		
		return CollisionResult::CollideWithPhysics;
	});
}

void TownExitBlocked::attachBardBehavior()
{
	if (bard == nullptr)
	{
		return;
	}

	this->bard->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_EndianForest_FindElriel_Bard_A_WhereAreDocks::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_FindElriel_Bard_B_RightButTalkToQueen::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->bard, true)
					),
					[=]()
					{
						Objectives::SetCurrentObjective(ObjectiveKeys::EFVisitQueen);
					},
					Voices::GetNextVoiceLong()
				));
			}),
			1.0f
		);
	});
}

void TownExitBlocked::onComplete()
{
}

void TownExitBlocked::onSkipped()
{
	this->removeAllListeners();
}

void TownExitBlocked::update(float dt)
{
	super::update(dt);

	if (!isEngagedInDialogue && this->dialogueCooldown > 0.0f)
	{
		this->dialogueCooldown -= dt;
	}
}
