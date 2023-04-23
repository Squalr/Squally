#include "DefeatAsmodeus.h"

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

const std::string DefeatAsmodeus::MapKeyQuest = "defeat-asmodeus";
const std::string DefeatAsmodeus::MapEventEngageKrampus = "engage-asmodeus";

DefeatAsmodeus* DefeatAsmodeus::create(GameObject* owner, QuestLine* questLine)
{
	DefeatAsmodeus* instance = new DefeatAsmodeus(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatAsmodeus::DefeatAsmodeus(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatAsmodeus::MapKeyQuest, false)
{
	this->krampus = dynamic_cast<Krampus*>(owner);
}

DefeatAsmodeus::~DefeatAsmodeus()
{
}

void DefeatAsmodeus::onLoad(QuestState questState)
{
	if (this->krampus != nullptr)
	{
		if (!this->krampus->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}

		this->krampus->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
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

void DefeatAsmodeus::onActivate(bool isActiveThroughSkippable)
{
	if (this->krampus != nullptr)
	{
		this->krampus->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->complete();
			}
		});
	}

	this->listenForMapEventOnce(DefeatAsmodeus::MapEventEngageKrampus, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatAsmodeus::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::DMSailToDrammol);
}

void DefeatAsmodeus::onSkipped()
{
	this->removeAllListeners();
}

void DefeatAsmodeus::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->krampus->getAnimations()->setFlippedX(true);

	this->krampus->runAction(Sequence::create(
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
				Voices::GetNextVoiceShort(Voices::VoiceType::Demon),
				false
			));
		}),
		nullptr
	));
}

void DefeatAsmodeus::runCinematicSequencePt2()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->krampus, false));
}
