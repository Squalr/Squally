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

void DefeatAgnes::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	if (this->agnes != nullptr)
	{
		this->agnes->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->complete();
			}
		});

		if (!this->agnes->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}
	}

	this->listenForMapEventOnce(DefeatAgnes::MapEventEngageAgnes, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatAgnes::onComplete()
{
}

void DefeatAgnes::onSkipped()
{
	this->removeAllListeners();
}

void DefeatAgnes::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Agnes_A_Guests::create(),
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
		Voices::GetNextVoiceShort(Voices::VoiceType::Human),
		false
	));
}

void DefeatAgnes::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Agnes_B_StayingLong::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->agnes, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->agnes, false));
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Human),
		false
	));
	
}
