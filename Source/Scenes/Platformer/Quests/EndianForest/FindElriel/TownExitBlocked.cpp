#include "TownExitBlocked.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TownExitBlocked::MapKeyQuest = "town-exit-blocked";
const std::string TownExitBlocked::TagBlockedExit = "blocked-exit";

TownExitBlocked* TownExitBlocked::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TownExitBlocked* instance = new TownExitBlocked(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TownExitBlocked::TownExitBlocked(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TownExitBlocked::MapKeyQuest, questTag, false)
{
	this->dialogueCooldown = 0.0f;
	this->isEngagedInDialogue = false;
	this->chiron = static_cast<Chiron*>(owner);
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
		ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
		{
			this->squally = squally;
		}, Squally::MapKeySqually);

		ObjectEvents::watchForObject<Portal>(this, [=](Portal* portal)
		{
			this->townExitPortal = portal;
			this->townExitPortal->disable();
		}, TownExitBlocked::TagBlockedExit);
	}
}

void TownExitBlocked::onActivate(bool isActiveThroughSkippable)
{
	this->defer([=]()
	{
		this->chiron->attachBehavior(LookAtSquallyBehavior::create(this->chiron));

		this->chironCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(this->chiron->getMovementSize(), 1.0f, 8.0f, 0.0f),
			(CollisionType)PlatformerCollisionType::SolidPlayerOnly,
			false,
			false
		);
		this->chironCollision->getPhysicsBody()->setPositionOffset(this->chiron->getCollisionOffset() + Vec2(0.0f, this->chiron->getEntitySize().height / 2.0f));

		this->chiron->addChild(this->chironCollision);

		this->chironCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::PlayerMovement }, [=](CollisionObject::CollisionData collisionData)
		{
			if (!this->isEngagedInDialogue && this->dialogueCooldown <= 0.0f)
			{
				this->isEngagedInDialogue = true;

				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_FindElriel_Chiron_CantLeaveTown::create(),
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
			
			return CollisionObject::CollisionResult::CollideWithPhysics;
		});
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
