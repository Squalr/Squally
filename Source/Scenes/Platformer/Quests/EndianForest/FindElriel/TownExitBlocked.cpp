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
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Strings/Platformer/Quests/FindElriel/CantLeaveTown.h"

using namespace cocos2d;

const std::string TownExitBlocked::MapKeyQuest = "town-exit-blocked";

TownExitBlocked* TownExitBlocked::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TownExitBlocked* instance = new TownExitBlocked(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TownExitBlocked::TownExitBlocked(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TownExitBlocked::MapKeyQuest, questTag, false)
{
	this->collisionObject = dynamic_cast<CollisionObject*>(owner);
	this->dialogueCooldown = 0.0f;
	this->isEngagedInDialogue = false;
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
}

void TownExitBlocked::onActivate(bool isActiveThroughSkippable)
{
	ObjectEvents::watchForObject<Chiron>(this, [=](Chiron* chiron)
	{
		this->chiron = chiron;
		EntityCollisionBehavior* collisionBehavior = this->chiron->getAttachedBehavior<EntityCollisionBehavior>();

		if (collisionBehavior != nullptr)
		{
			collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::PlayerMovement }, [=](CollisionObject::CollisionData collisionData)
			{
				if (!this->isEngagedInDialogue && this->dialogueCooldown <= 0.0f)
				{
					this->isEngagedInDialogue = true;

					DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_FindElriel_CantLeaveTown::create(),
						[=]()
						{
							this->isEngagedInDialogue = false;
							this->dialogueCooldown = 4.0f;
						}
					));
				}
				
				return CollisionObject::CollisionResult::CollideWithPhysics;
			});
		}
	});
}

void TownExitBlocked::onComplete()
{
	this->removeAllListeners();
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
