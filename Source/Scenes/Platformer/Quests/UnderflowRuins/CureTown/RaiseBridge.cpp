#include "RaiseBridge.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ajax.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/CureTown.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/CureTownLine.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RaiseBridge::MapKeyQuest = "raise-bridge";

RaiseBridge* RaiseBridge::create(GameObject* owner, QuestLine* questLine)
{
	RaiseBridge* instance = new RaiseBridge(owner, questLine);

	instance->autorelease();

	return instance;
}

RaiseBridge::RaiseBridge(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RaiseBridge::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->ajax = nullptr;
}

RaiseBridge::~RaiseBridge()
{
}

void RaiseBridge::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Ajax>(this, [=](Ajax* ajax)
	{
		this->ajax = ajax;

		bool ajaxCured = QuestTask::GetQuestSaveStateOrDefault(CureTownLine::MapKeyQuestLine, CureTown::MapKeyQuest, CureTown::SaveKeyAjaxCured, Value(false)).asBool();
		int curedCount = QuestTask::GetQuestSaveStateOrDefault(CureTownLine::MapKeyQuestLine, CureTown::MapKeyQuest, CureTown::SaveKeyCuredCount, Value(0)).asInt();

		if (questState == QuestState::Complete || questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->runCinematicSequence();
		}
		else if (ajaxCured && curedCount < CureTown::MaxCuredCount)
		{
			this->runCinematicSequenceCureIncomplete();
		}
		else if (ajaxCured && curedCount >= CureTown::MaxCuredCount)
		{
			this->runCinematicSequencePreviousQuestIncomplete();
		}
		else
		{
			this->ajax->despawn();
		}
	}, Ajax::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void RaiseBridge::onActivate(bool isActiveThroughSkippable)
{
}

void RaiseBridge::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::URFindMineEntrance);
}

void RaiseBridge::onSkipped()
{
	this->removeAllListeners();
}

void RaiseBridge::runCinematicSequence()
{
	this->ajax->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_M_RaiseBridge::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->ajax, true)
			),
			[=]()
			{
				this->broadcastMapEvent("raise-bridge", ValueMap());
				this->complete();
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}

void RaiseBridge::runCinematicSequenceCureIncomplete()
{
	this->ajax->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_Y_RemainingTownspeople::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->ajax, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}

void RaiseBridge::runCinematicSequencePreviousQuestIncomplete()
{
	this->ajax->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_Z_SpeakToHera::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->ajax, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}
