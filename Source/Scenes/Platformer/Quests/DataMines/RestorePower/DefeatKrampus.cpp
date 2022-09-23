#include "DefeatKrampus.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Enemies/DataMines/Krampus.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DefeatKrampus::MapKeyQuest = "defeat-krampus";
const std::string DefeatKrampus::MapEventEngageKrampus = "awaken-krampus";

DefeatKrampus* DefeatKrampus::create(GameObject* owner, QuestLine* questLine)
{
	DefeatKrampus* instance = new DefeatKrampus(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatKrampus::DefeatKrampus(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatKrampus::MapKeyQuest, false)
{
	this->krampus = dynamic_cast<Krampus*>(owner);
}

DefeatKrampus::~DefeatKrampus()
{
}

void DefeatKrampus::onLoad(QuestState questState)
{
	if (this->krampus != nullptr)
	{
		if (!this->krampus->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}

		this->krampus->listenForStateWriteOnce(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->complete();
			}
		});
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void DefeatKrampus::onActivate(bool isActiveThroughSkippable)
{
	this->krampus->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});

	this->listenForMapEventOnce(DefeatKrampus::MapEventEngageKrampus, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatKrampus::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::DMSailToDrammol);
}

void DefeatKrampus::onSkipped()
{
	this->removeAllListeners();
}

void DefeatKrampus::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->krampus->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_DataMines_RestorePower_Krampus_A_Intruders::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->krampus, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->runCinematicSequencePt2();
				},
				Voices::GetNextVoiceShort(Voices::VoiceType::Rhino),
				false
			));
		}),
		nullptr
	));
}

void DefeatKrampus::runCinematicSequencePt2()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->krampus, false));
}
