#include "TalkToSarude.h"

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
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"

using namespace cocos2d;

const std::string TalkToSarude::MapKeyQuest = "talk-to-sarude";

TalkToSarude* TalkToSarude::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToSarude* instance = new TalkToSarude(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToSarude::TalkToSarude(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToSarude::MapKeyQuest, questTag, false)
{
	this->sarude = nullptr;
	this->squally = nullptr;
}

TalkToSarude::~TalkToSarude()
{
}

void TalkToSarude::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});
}

void TalkToSarude::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToSarude::onComplete()
{
}

void TalkToSarude::onSkipped()
{
	this->removeAllListeners();
}

void TalkToSarude::registerDialogue()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		DelayTime::create(3.0f),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				nullptr,
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				[=]()
				{
				},
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true),
				false
			));
		}),
		nullptr
	));
}
