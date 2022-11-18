#include "UnhauntCastle.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/FountainRoomKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string UnhauntCastle::MapKeyQuest = "unhaunt-castle";
const std::string UnhauntCastle::SaveKeyUnhauntedCount = "SAVE_KEY_UNHAUNTED_COUNT";
const std::string UnhauntCastle::SaveKeyPrefixUnhaunted = "SAVE_KEY_UNHAUNTED_";
const int UnhauntCastle::MaxUnhauntCount = 5;

UnhauntCastle* UnhauntCastle::create(GameObject* owner, QuestLine* questLine)
{
	UnhauntCastle* instance = new UnhauntCastle(owner, questLine);

	instance->autorelease();

	return instance;
}

UnhauntCastle::UnhauntCastle(GameObject* owner, QuestLine* questLine) : super(owner, questLine, UnhauntCastle::MapKeyQuest, false)
{
}

UnhauntCastle::~UnhauntCastle()
{
}

void UnhauntCastle::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Mabel>(this, [=](Mabel* mabel)
	{
		this->mabel = mabel;
		
		if (questState == QuestState::Active)
		{
			this->updateQuestVisuals();
		}
	}, Mabel::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void UnhauntCastle::onActivate(bool isActiveThroughSkippable)
{
	// Defer just in case Mabel is not initialized yet
	this->defer([=]()
	{
		if (isActiveThroughSkippable)
		{
			this->updateQuestVisuals();
		}
	}, 2);
}

void UnhauntCastle::onComplete()
{
	this->mabel->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});
}

void UnhauntCastle::onSkipped()
{
	this->removeAllListeners();
}

void UnhauntCastle::updateQuestVisuals()
{
	if (this->mabel == nullptr)
	{
		return;
	}

	this->mabel->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		int currentCureCount = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt();

		if (currentCureCount >= UnhauntCastle::MaxUnhauntCount)
		{
			questBehavior->enableTurnIn();

			this->runCinematicSequence();
		}
		// Check for at least one unhaunted entity, such as to not give spoilers for the unhaunting quest
		else if (currentCureCount >= 1)
		{
			questBehavior->enableIncompleteQuest();

			this->setPreText();
		}
	});
}

void UnhauntCastle::runCinematicSequence()
{
	if (this->mabel == nullptr)
	{
		return;
	}
	
	this->mabel->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_V_ThankYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_W_TakeArcaneBook::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}

void UnhauntCastle::setPreText()
{
	if (this->mabel == nullptr)
	{
		return;
	}

	this->defer([=]()
	{
		this->mabel->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			int remaining = UnhauntCastle::MaxUnhauntCount - SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt();

			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_Q_Remaining::create()
					->setStringReplacementVariables(ConstantString::create(std::to_string(remaining))),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->mabel, true)
				),
				[=]()
				{
					this->setPreText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});
	});
}
