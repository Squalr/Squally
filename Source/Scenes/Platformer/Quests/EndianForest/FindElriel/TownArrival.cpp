#include "TownArrival.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Platformer/Quests/EndianForest/FindElriel/Scrappy/A_LetsFindABoat.h"
#include "Strings/Platformer/MapNames/Zones/UnderflowRuins.h"

using namespace cocos2d;

const std::string TownArrival::MapKeyQuest = "town-arrival";

TownArrival* TownArrival::create(GameObject* owner, QuestLine* questLine, std::string questTag)
{
	TownArrival* instance = new TownArrival(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TownArrival::TownArrival(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TownArrival::MapKeyQuest, questTag, true)
{
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TownArrival::~TownArrival()
{
}

void TownArrival::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);
}

void TownArrival::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(TownArrival::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void TownArrival::onComplete()
{
}

void TownArrival::onSkipped()
{
	this->removeAllListeners();
}

void TownArrival::runCinematicSequence()
{
	if (this->scrappy == nullptr)
	{
		return;
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Scrappy_A_LetsFindABoat::create()
			->setStringReplacementVariables({ Strings::Platformer_MapNames_Zones_UnderflowRuins::create() }),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
		},
		SoundResources::Platformer_Entities_Droid_DroidChatter,
		true
	));
}
