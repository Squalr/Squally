#include "TownExitBlocked.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/DialogueEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Strings/Platformer/Quests/Intro/HackerMode.h"

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
	this->chiron = dynamic_cast<Chiron*>(owner);
}

TownExitBlocked::~TownExitBlocked()
{
}

void TownExitBlocked::onLoad(QuestState questState)
{
}

void TownExitBlocked::onActivate(bool isActiveThroughSkippable)
{
	if (this->chiron == nullptr)
	{
		return;
	}

	EntityCollisionBehavior* collisionBehavior = this->chiron->getAttachedBehavior<EntityCollisionBehavior>();

	if (collisionBehavior != nullptr)
	{
		collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
		{
			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(Strings::Platformer_Quests_Intro_HackerMode::create()));
			
			return CollisionObject::CollisionResult::DoNothing;
		});
	}
}

void TownExitBlocked::onComplete()
{
}

void TownExitBlocked::onSkipped()
{
	this->removeAllListeners();
}

