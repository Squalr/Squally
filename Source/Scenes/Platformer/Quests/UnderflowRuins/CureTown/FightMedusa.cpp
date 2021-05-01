#include "FightMedusa.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Medusa.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FightMedusa::MapKeyQuest = "fight-medusa";

FightMedusa* FightMedusa::create(GameObject* owner, QuestLine* questLine)
{
	FightMedusa* instance = new FightMedusa(owner, questLine);

	instance->autorelease();

	return instance;
}

FightMedusa::FightMedusa(GameObject* owner, QuestLine* questLine) : super(owner, questLine, FightMedusa::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->medusa = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

FightMedusa::~FightMedusa()
{
}

void FightMedusa::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Medusa>(this, [=](Medusa* medusa)
	{
		this->medusa = medusa;

		if (this->medusa->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->listenForMapEventOnce(FightMedusa::MapKeyQuest, [=](ValueMap args)
			{
				this->runCinematicSequencePart1();
			});
		}
		else
		{
			this->defer([=]()
			{
				this->complete();
			});
		}

		// Listen for non-combat death. Just a debugging tool.
		this->medusa->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->complete();
			}
		});
	}, Medusa::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void FightMedusa::onActivate(bool isActiveThroughSkippable)
{
}

void FightMedusa::onComplete()
{
	this->runCinematicSequencePart2();
}

void FightMedusa::onSkipped()
{
	this->removeAllListeners();
}

void FightMedusa::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Mesuda_A_Hiss::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->medusa, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->medusa, true));
		},
		SoundResources::Platformer_Entities_Serpent_Hiss1,
		false
	));
}

void FightMedusa::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Scrappy_T_StillCursed::create()
			->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}
