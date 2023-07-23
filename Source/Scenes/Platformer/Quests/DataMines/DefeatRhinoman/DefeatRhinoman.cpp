#include "DefeatRhinoman.h"

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
#include "Entities/Platformer/Enemies/DataMines/Rhinoman.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/ScreamingDoor.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DefeatRhinoman::MapKeyQuest = "defeat-rhinoman";
const std::string DefeatRhinoman::MapEventAwakenRhinoman = "awaken-rhinoman";

DefeatRhinoman* DefeatRhinoman::create(GameObject* owner, QuestLine* questLine)
{
	DefeatRhinoman* instance = new DefeatRhinoman(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatRhinoman::DefeatRhinoman(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatRhinoman::MapKeyQuest, false)
{
	this->rhinoman = dynamic_cast<Rhinoman*>(owner);
}

DefeatRhinoman::~DefeatRhinoman()
{
}

void DefeatRhinoman::onLoad(QuestState questState)
{
	if (this->rhinoman != nullptr)
	{
		if (!this->rhinoman->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}
		else
		{
			this->rhinoman->setOpacity(0);
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<ScreamingDoor>(this, [=](ScreamingDoor* screamingDoor)
	{
		this->screamingDoor = screamingDoor;
		
		if (questState == QuestState::Complete)
		{
			this->screamingDoor->unlock(false);
		}
	}, ScreamingDoor::MapKey);
}

void DefeatRhinoman::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->rhinoman->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});

	this->listenForMapEventOnce(DefeatRhinoman::MapEventAwakenRhinoman, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatRhinoman::onComplete()
{
	ObjectEvents::WatchForObject<ScreamingDoor>(this, [=](ScreamingDoor* screamingDoor)
	{
		this->screamingDoor = screamingDoor;
		
		this->screamingDoor->unlock(false);
	}, ScreamingDoor::MapKey);
}

void DefeatRhinoman::onSkipped()
{
	this->removeAllListeners();
}

void DefeatRhinoman::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->screamingDoor->unlock(true);

	this->rhinoman->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_DataMines_DefeatRhinoman_A_YouShallNotPass::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->rhinoman, false),
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

void DefeatRhinoman::runCinematicSequencePt2()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->rhinoman, false));
}
