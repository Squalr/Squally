#include "TalkToAmelia.h"

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
#include "Entities/Platformer/Npcs/LambdaCrypts/Amelia.h"
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

const std::string TalkToAmelia::MapKeyQuest = "talk-to-amelia";

TalkToAmelia* TalkToAmelia::create(GameObject* owner, QuestLine* questLine)
{
	TalkToAmelia* instance = new TalkToAmelia(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToAmelia::TalkToAmelia(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToAmelia::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->amelia = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToAmelia::~TalkToAmelia()
{
}

void TalkToAmelia::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Amelia>(this, [=](Amelia* amelia)
	{
		this->amelia = amelia;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->amelia->clearState(StateKeys::PatrolSourceX);
			this->amelia->clearState(StateKeys::PatrolDestinationX);
			this->amelia->setState(StateKeys::PatrolHijacked, Value(true));
			this->amelia->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}

		// Await Helpers to be ready
		this->defer([=]()
		{
			this->runCinematicSequence();
		}, 2);

	}, Amelia::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToAmelia::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void TalkToAmelia::onComplete()
{
	if (this->amelia != nullptr)
	{
		this->amelia->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}

	Objectives::SetCurrentObjective(ObjectiveKeys::LCTalkToNebea);
}

void TalkToAmelia::onSkipped()
{
	this->removeAllListeners();
}

void TalkToAmelia::runCinematicSequence()
{
	if (this->amelia == nullptr)
	{
		return;
	}
	
	this->amelia->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_Amelia_A_Bitten::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Elric::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->amelia, true)
			),
			[=]()
			{
				this->amelia->setState(StateKeys::PatrolHijacked, Value(false));

				if (GameUtils::getWorldCoords(this->amelia).x > GameUtils::getWorldCoords(this->squally).x)
				{
					this->amelia->getAnimations()->setFlippedX(true);
				}
				else
				{
					this->amelia->getAnimations()->setFlippedX(false);
				}
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_Amelia_B_NothingCanBeDone::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->amelia, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_Amelia_C_NoCure::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->amelia, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_Amelia_D_SeeNebea::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Elric::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->amelia, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceLong(),
			true
		));
	});
}
