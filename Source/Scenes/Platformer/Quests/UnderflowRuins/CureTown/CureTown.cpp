#include "CureTown.h"

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

const std::string CureTown::MapKeyQuest = "cure-town";
const std::string CureTown::SaveKeyCuredCount = "SAVE_KEY_CURED_COUNT";
const std::string CureTown::SaveKeyAjaxCured = "SAVE_KEY_AJAX_CURED";
const std::string CureTown::SaveKeyGriffinCured = "SAVE_KEY_GRIFFIN_CURED";
const int CureTown::MaxCuredCount = 6;

CureTown* CureTown::create(GameObject* owner, QuestLine* questLine)
{
	CureTown* instance = new CureTown(owner, questLine);

	instance->autorelease();

	return instance;
}

CureTown::CureTown(GameObject* owner, QuestLine* questLine) : super(owner, questLine, CureTown::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->hera = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

CureTown::~CureTown()
{
}

void CureTown::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	if (questState == QuestState::Complete)
	{
		ObjectEvents::WatchForObject<CollisionObject>(this, [=](CollisionObject* collisionObject)
		{
			collisionObject->setPhysicsEnabled(false);
		}, "quest-solid-wall");

		ObjectEvents::WatchForObject<CameraStop>(this, [=](CameraStop* cameraStop)
		{
			cameraStop->disable();
		}, "quest-camera-stop");
	}

	ObjectEvents::WatchForObject<Hera>(this, [=](Hera* hera)
	{
		this->hera = hera;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->hera->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				int currentCureCount = this->getQuestSaveStateOrDefault(CureTown::SaveKeyCuredCount, Value(0)).asInt();

				if (currentCureCount >= CureTown::MaxCuredCount)
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

void CureTown::onActivate(bool isActiveThroughSkippable)
{
}

void CureTown::onComplete()
{
	this->hera->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});

	ObjectEvents::WatchForObject<CollisionObject>(this, [=](CollisionObject* collisionObject)
	{
		collisionObject->setPhysicsEnabled(false);
	}, "quest-solid-wall");

	ObjectEvents::WatchForObject<CameraStop>(this, [=](CameraStop* cameraStop)
	{
		cameraStop->disable();
	}, "quest-camera-stop");

	Objectives::SetCurrentObjective(ObjectiveKeys::URCrossBridge);
}

void CureTown::onSkipped()
{
	this->removeAllListeners();
}

void CureTown::runCinematicSequence()
{
	if (this->hera == nullptr)
	{
		return;
	}
	
	this->hera->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_R_ThankYou::create(),
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_S_WhereAreYouHeaded::create(),
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_T_SkyCrack::create(),
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_U_OnlyWay::create()
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_V_Bridge::create(),
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_W_BeforeYouGo::create(),
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

void CureTown::setPreText()
{
	this->defer([=]()
	{
		this->hera->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			int remaining = CureTown::MaxCuredCount - this->getQuestSaveStateOrDefault(CureTown::SaveKeyCuredCount, Value(0)).asInt();

			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_Q_PleaseCure::create()
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
