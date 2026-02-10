#include "KillTheTroll.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

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
}

KillTheTroll::~KillTheTroll()
{
}

void KillTheTroll::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void KillTheTroll::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
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
