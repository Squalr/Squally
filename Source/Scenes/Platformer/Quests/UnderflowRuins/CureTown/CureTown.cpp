#include "CureTown.h"

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
#include "Entities/Platformer/Npcs/UnderflowRuins/Hera.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/FountainRoomKey.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CureTown::MapKeyQuest = "cure-town";
const std::string CureTown::SaveKeyCuredCount = "cure-town";
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

	ObjectEvents::WatchForObject<Hera>(this, [=](Hera* hera)
	{
		this->hera = hera;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->hera->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				int currentCureCount = this->getQuestSaveStateOrDefault(CureTown::SaveKeyCuredCount, Value(0)).asInt();

				if (currentCureCount > CureTown::MaxCuredCount)
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
	this->hera->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});

	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
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
	
	this->hera->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::PointerTrace_Assembly_Jmp::create(),
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
			SoundResources::Platformer_Entities_Generic_ChatterShort1,
			false
		));
	});
}

void CureTown::setPreText()
{
	this->defer([=]()
	{
		this->hera->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_Q_PleaseCure::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->hera, true)
				),
				[=]()
				{
					this->setPreText();
				},
				SoundResources::Platformer_Entities_Generic_ChatterMedium2,
				true
			));
		});
	});
}
