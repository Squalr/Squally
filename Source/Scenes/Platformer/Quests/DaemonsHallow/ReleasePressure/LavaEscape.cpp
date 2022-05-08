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

void LavaEscape::onActivate(bool isActiveThroughSkippable)
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
		Strings::Platformer_Quests_EndianForest_FindElriel_Elriel_A_GratefulYouAreHere::create(), // TODO: Do you hear that?
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
		Voices::GetNextVoiceMedium(),
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
		Strings::Platformer_Ellipses::create(), // TODO: Seismic activity
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true),
			true
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
		lava->runAction(Sequence::create(
			EaseSineIn::create(MoveBy::create(50.0f, Vec2(0.0f, 10000.0f))),
			nullptr
		));
	}, LavaEscape::MapTagRisingLava);
}
