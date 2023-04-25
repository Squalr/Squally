#include "LavaEscape.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Liquids/Lava.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaEscape::MapKeyQuest = "lava-escape";
const std::string LavaEscape::MapEventBeginLavaEvent = "begin-lava-event";
const std::string LavaEscape::MapEventPressureReleased = "pressure-released";
const std::string LavaEscape::MapTagRisingLava = "rising-lava";

LavaEscape* LavaEscape::create(GameObject* owner, QuestLine* questLine)
{
	LavaEscape* instance = new LavaEscape(owner, questLine);

	instance->autorelease();

	return instance;
}

LavaEscape::LavaEscape(GameObject* owner, QuestLine* questLine) : super(owner, questLine, LavaEscape::MapKeyQuest, false)
{
}

LavaEscape::~LavaEscape()
{
}

void LavaEscape::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void LavaEscape::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->listenForMapEventOnce(LavaEscape::MapEventBeginLavaEvent, [=](ValueMap)
	{
		this->runCinematicSequencePart1();
	});
	this->listenForMapEventOnce(LavaEscape::MapEventPressureReleased, [=](ValueMap)
	{
		this->complete();
	});
}

void LavaEscape::onComplete()
{
}

void LavaEscape::onSkipped()
{
	this->removeAllListeners();
}

void LavaEscape::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_ReleasePressure_A_DoYouHearThat::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePart2();
		},
		Voices::GetNextVoiceQuestion(),
		false
	));
}

void LavaEscape::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true),
			true
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		"",
		false
	));
}

void LavaEscape::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_ReleasePressure_B_SeismicActivity::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void LavaEscape::runCinematicSequencePart4()
{
	ObjectEvents::QueryObject<Lava>([=](Lava* lava)
	{
		const float phase1Time = 5.0f;
		const float phase2Time = 5.0f;
		const float phase3Time = 10.0f;
		const float phase4Time = 20.0f;

		const float phase1Speed = 100.0f;
		const float phase2Speed = 125.0f;
		const float phase3Speed = 150.0f;
		const float phase4Speed = 200.0f;

		lava->runAction(Sequence::create(
			EaseSineIn::create(MoveBy::create(phase1Time, Vec2(0.0f, phase1Time * phase1Speed))),
			MoveBy::create(phase2Time, Vec2(0.0f, phase2Time * phase2Speed)),
			MoveBy::create(phase3Time, Vec2(0.0f, phase3Time * phase3Speed)),
			MoveBy::create(phase4Time, Vec2(0.0f, phase4Time * phase4Speed)),
			nullptr
		));
	}, LavaEscape::MapTagRisingLava);
}
