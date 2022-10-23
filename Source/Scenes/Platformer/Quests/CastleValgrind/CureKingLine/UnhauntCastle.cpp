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
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hera.h"
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
const std::string UnhauntCastle::SaveKeyElricCured = "SAVE_KEY_ELRIC_UNHAUNTED";
const std::string UnhauntCastle::SaveKeyLeopoldCured = "SAVE_KEY_LEOPOLD_UNHAUNTED";
const int UnhauntCastle::MaxCuredCount = 4;

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

	ObjectEvents::WatchForObject<Hera>(this, [=](Hera* hera)
	{
		this->hera = hera;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->hera->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				int currentCureCount = this->getQuestSaveStateOrDefault(UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt();

				if (currentCureCount >= UnhauntCastle::MaxCuredCount)
				{
					questBehavior->enableTurnIn();

					this->runCinematicSequence();
				}
				else
				{
					questBehavior->enableIncompleteQuest();

					this->setPreText();
				}
			});
		}
	}, Hera::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void UnhauntCastle::onActivate(bool isActiveThroughSkippable)
{
}

void UnhauntCastle::onComplete()
{
	this->hera->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});

	Objectives::SetCurrentObjective(ObjectiveKeys::URCrossBridge);
}

void UnhauntCastle::onSkipped()
{
	this->removeAllListeners();
}

void UnhauntCastle::runCinematicSequence()
{
	if (this->hera == nullptr)
	{
		return;
	}
	
	this->hera->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ FountainRoomKey::create() }));
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceQuestion(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create()
				->setStringReplacementVariables(Strings::Platformer_MapNames_UnderflowRuins_PyramidPass::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_TODO::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void UnhauntCastle::setPreText()
{
	this->defer([=]()
	{
		this->hera->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			int remaining = UnhauntCastle::MaxCuredCount - this->getQuestSaveStateOrDefault(UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt();

			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Menus_TODO::create()
					->setStringReplacementVariables(ConstantString::create(std::to_string(remaining))),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->hera, true)
				),
				[=]()
				{
					PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ FountainRoomKey::create() }));
					this->setPreText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});
	});
}
