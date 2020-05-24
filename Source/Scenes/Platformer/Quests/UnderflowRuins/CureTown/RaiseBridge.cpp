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
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

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

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->runCinematicSequence();
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
	Objectives::SetCurrentObjective(ObjectiveKeys::URFindTheCavernsEntrance);
}

void RaiseBridge::onSkipped()
{
	this->removeAllListeners();
}

void RaiseBridge::runCinematicSequence()
{
	this->ajax->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
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
			},
			Voices::GetNextVoiceShort(),
			false
		));
	});
}
