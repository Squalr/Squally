#include "TalkToGrogg.h"

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
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Overworld/EndianForest/KingGrogg/GroggOutOfCombatAttackBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToGrogg::MapKeyQuest = "talk-to-grogg";

TalkToGrogg* TalkToGrogg::create(GameObject* owner, QuestLine* questLine)
{
	TalkToGrogg* instance = new TalkToGrogg(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToGrogg::TalkToGrogg(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToGrogg::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->kingGrogg = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToGrogg::~TalkToGrogg()
{
}

void TalkToGrogg::onLoad(QuestState questState)
{
	// Ret-con to allow players to hack water stuff TODO: Delete after 4/x/2020
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<KingGrogg>(this, [=](KingGrogg* kingGrogg)
	{
		this->kingGrogg = kingGrogg;
		
		this->kingGrogg->watchForAttachedBehavior<AgroBehavior>([&](AgroBehavior* agroBehavior)
		{
			agroBehavior->disable();
		});
	}, KingGrogg::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToGrogg::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(TalkToGrogg::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequencePart1();
	});
}

void TalkToGrogg::onComplete()
{
}

void TalkToGrogg::onSkipped()
{
	this->removeAllListeners();
}

void TalkToGrogg::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Grogg_A_WhoDares::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingGrogg, true)
		),
		[=]()
		{
			this->runCinematicSequencePart2();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Orc),
		false
	));
}

void TalkToGrogg::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Grogg_B_RescueElf::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingGrogg, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		Voices::GetNextVoiceQuestion(Voices::VoiceType::Orc),
		false
	));
}

void TalkToGrogg::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Grogg_C_SpreadForcesThin::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingGrogg, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Orc),
		false
	));
}

void TalkToGrogg::runCinematicSequencePart4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Grogg_D_MarchesTowards::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingGrogg, true)
		),
		[=]()
		{
			this->complete();
			
			this->kingGrogg->watchForAttachedBehavior<GroggOutOfCombatAttackBehavior>([&](GroggOutOfCombatAttackBehavior* combatBehavior)
			{
				combatBehavior->attack();
			});
			
			this->kingGrogg->watchForAttachedBehavior<AgroBehavior>([&](AgroBehavior* agroBehavior)
			{
				agroBehavior->enable();
				agroBehavior->toggleWarnOnAgro(false);
				agroBehavior->setAgroRangeX(65535.0f);
				agroBehavior->setAgroRangeY(65535.0f);
			});
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Orc),
		true
	));
}
