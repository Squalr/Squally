#include "KillTheTroll.h"

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
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string KillTheTroll::MapKeyQuest = "kill-the-troll";

KillTheTroll* KillTheTroll::create(GameObject* owner, QuestLine* questLine)
{
	KillTheTroll* instance = new KillTheTroll(owner, questLine);

	instance->autorelease();

	return instance;
}

KillTheTroll::KillTheTroll(GameObject* owner, QuestLine* questLine) : super(owner, questLine, KillTheTroll::MapKeyQuest, false)
{
	this->troll = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
}

KillTheTroll::~KillTheTroll()
{
}

void KillTheTroll::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void KillTheTroll::onActivate(bool isActiveThroughSkippable)
{
	this->troll->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});
}

void KillTheTroll::onComplete()
{
}

void KillTheTroll::onSkipped()
{
	this->removeAllListeners();
}
