#include "DistractGuard.h"

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
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/WeakMindedBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string DistractGuard::MapKeyQuest = "distract-guard";

DistractGuard* DistractGuard::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	DistractGuard* instance = new DistractGuard(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

DistractGuard::DistractGuard(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, DistractGuard::MapKeyQuest, questTag, false)
{
	this->lycan = dynamic_cast<Lycan*>(owner);
}

DistractGuard::~DistractGuard()
{
}

void DistractGuard::onEnter()
{
	super::onEnter();
}

void DistractGuard::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Lycan>(this, [=](Lycan* lycan)
	{
		this->lycan = lycan;

		this->lycan->attachBehavior(WeakMindedBehavior::create(this->lycan));
	});
}

void DistractGuard::onActivate(bool isActiveThroughSkippable)
{
}

void DistractGuard::onComplete()
{
	this->removeAllListeners();
}

void DistractGuard::onSkipped()
{
	this->removeAllListeners();
}
