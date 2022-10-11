#include "DefeatAgnes.h"

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
#include "Entities/Platformer/Enemies/CastleValgrind/Agnes.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/ScreamingDoor.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DefeatAgnes::MapKeyQuest = "defeat-agnes";
const std::string DefeatAgnes::MapEventEngageAgnes = "engage-agnes";

DefeatAgnes* DefeatAgnes::create(GameObject* owner, QuestLine* questLine)
{
	DefeatAgnes* instance = new DefeatAgnes(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatAgnes::DefeatAgnes(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatAgnes::MapKeyQuest, false)
{
	this->agnes = dynamic_cast<Agnes*>(owner);
}

DefeatAgnes::~DefeatAgnes()
{
}

void DefeatAgnes::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void DefeatAgnes::onActivate(bool isActiveThroughSkippable)
{
	this->agnes->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});

	this->listenForMapEventOnce(DefeatAgnes::MapEventEngageAgnes, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatAgnes::onComplete()
{
	// TODO
	// Objectives::SetCurrentObjective(ObjectiveKeys::UREnterTheMines);
}

void DefeatAgnes::onSkipped()
{
	this->removeAllListeners();
}

void DefeatAgnes::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->agnes->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Menus_StoryMode::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->agnes, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->runCinematicSequencePt2();
				},
				Voices::GetNextVoiceMedium(Voices::VoiceType::Human),
				false
			));
		}),
		nullptr
	));
}

void DefeatAgnes::runCinematicSequencePt2()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->agnes, false));
}
