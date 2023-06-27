#include "TalkToNebea.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/PrincessNebea.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/LambdaCrypts/RustyKey.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToNebea::MapKeyQuest = "talk-to-nebea";

TalkToNebea* TalkToNebea::create(GameObject* owner, QuestLine* questLine)
{
	TalkToNebea* instance = new TalkToNebea(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToNebea::TalkToNebea(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToNebea::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->princessNebea = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToNebea::~TalkToNebea()
{
}

void TalkToNebea::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Grim>(this, [=](Grim* grim)
	{
		this->grim = grim;
	}, Grim::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<PrincessNebea>(this, [=](PrincessNebea* princessNebea)
	{
		this->princessNebea = princessNebea;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->princessNebea->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}

		if (questState != QuestState::None && questState != QuestState::Complete)
		{
			// Await Helpers to be ready
			this->defer([=]()
			{
				this->runCinematicSequence();
			}, 2);
		}
	}, PrincessNebea::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToNebea::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void TalkToNebea::onComplete()
{
	if (this->princessNebea != nullptr)
	{
		this->princessNebea->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}

	Objectives::SetCurrentObjective(ObjectiveKeys::LCReturnToElric);
}

void TalkToNebea::onSkipped()
{
	this->removeAllListeners();
}

void TalkToNebea::runCinematicSequence()
{
	if (this->princessNebea == nullptr)
	{
		return;
	}
	
	this->princessNebea->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_A_ElricIsDying::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Elric::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_B_ElricsMission::create()
				->setStringReplacementVariables(Strings::Items_Misc_Keys_DemonHeart::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_C_TakeKeyFromCorpse::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		if (this->gecky != nullptr)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_D_Gecky_Oh::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->gecky, false),
					DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
				),
				[=]()
				{
				},
				Voices::GetNextVoiceShort(),
				false
			));
		}
		else if (this->grim != nullptr)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_D_Grim_Souls::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->grim, false),
					DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
				),
				[=]()
				{
				},
				Voices::GetNextVoiceShort(),
				false
			));
		}
		else
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_D_Guano_Brutal::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->guano, false),
					DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
				),
				[=]()
				{
				},
				Voices::GetNextVoiceShort(),
				false
			));
		}

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_E_HellCrystalPurpose::create()
				->setStringReplacementVariables(Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessNebea, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_PrincessNebea_F_LeadsToPeaks::create()
				->setStringReplacementVariables(
				{
					Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create(),
					Strings::Platformer_MapNames_BallmerPeaks_BallmerPeaks::create(),
					Strings::Items_Misc_Keys_DemonHeart::create()
				}),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceLong(Voices::VoiceType::Droid),
			true
		));
	});
}
