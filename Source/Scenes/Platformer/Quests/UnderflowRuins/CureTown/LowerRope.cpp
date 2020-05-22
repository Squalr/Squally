#include "LowerRope.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/PlatformerDecorObject.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LowerRope::MapKeyQuest = "lower-rope";
const std::string LowerRope::TagRopePortal = "rope-portal";
const std::string LowerRope::TagRope = "rope";

LowerRope* LowerRope::create(GameObject* owner, QuestLine* questLine)
{
	LowerRope* instance = new LowerRope(owner, questLine);

	instance->autorelease();

	return instance;
}

LowerRope::LowerRope(GameObject* owner, QuestLine* questLine) : super(owner, questLine, LowerRope::MapKeyQuest, false)
{
}

LowerRope::~LowerRope()
{
}

void LowerRope::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		if (questState != QuestState::Complete)
		{
			portal->disable();
		}
	}, LowerRope::TagRopePortal);

	ObjectEvents::WatchForObject<PlatformerDecorObject>(this, [=](PlatformerDecorObject* rope)
	{
		if (questState != QuestState::Complete)
		{
			rope->setVisible(false);
		}
	}, LowerRope::TagRope);
}

void LowerRope::onActivate(bool isActiveThroughSkippable)
{
}

void LowerRope::onComplete()
{
}

void LowerRope::onSkipped()
{
}
