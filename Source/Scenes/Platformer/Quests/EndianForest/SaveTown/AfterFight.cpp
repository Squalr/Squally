#include "AfterFight.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Merlin.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Igneus.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Alder.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AfterFight::MapKeyQuest = "after-fight";
const std::string AfterFight::TagQuestPortal = "quest-portal";

AfterFight* AfterFight::create(GameObject* owner, QuestLine* questLine)
{
	AfterFight* instance = new AfterFight(owner, questLine);

	instance->autorelease();

	return instance;
}

AfterFight::AfterFight(GameObject* owner, QuestLine* questLine) : super(owner, questLine, AfterFight::MapKeyQuest, false)
{
	this->squally = nullptr;
	this->scrappy = nullptr;
	this->sarude = nullptr;
}

AfterFight::~AfterFight()
{
}

void AfterFight::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
	
	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKeySarude);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* magePortal)
	{
		this->magePortal = magePortal;

		if (questState == QuestState::Complete)
		{
			this->magePortal->openPortal(true);
		}
		else
		{
			this->magePortal->closePortal(true);
		}
	}, AfterFight::TagQuestPortal);

	if (questState == QuestState::Complete)
	{
		this->despawnMages();
	}
}

void AfterFight::onActivate(bool isActiveThroughSkippable)
{
	this->defer([=]()
	{
		this->runCinematicSequencePart1();
	});
}

void AfterFight::onComplete()
{
}

void AfterFight::onSkipped()
{
}

void AfterFight::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SaveTown_Sarude_H_ThanksBruh::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->sarude, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePart2();
			this->complete();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium3,
		true
	));
}

void AfterFight::runCinematicSequencePart2()
{
	if (this->magePortal != nullptr)
	{
		this->magePortal->openPortal(true);

		Vec2 destCoords = GameUtils::getWorldCoords(this->magePortal);
		
		ObjectEvents::watchForObject<Igneus>(this, [=](Igneus* igneus)
		{
			igneus->setState(StateKeys::CinematicDestinationX, Value(destCoords.x));
			
			igneus->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				igneus->runAction(FadeTo::create(0.25f, 0));
			});
		}, Igneus::MapKeyIgneus);

		ObjectEvents::watchForObject<Alder>(this, [=](Alder* alder)
		{
			alder->setState(StateKeys::CinematicDestinationX, Value(destCoords.x));
			
			alder->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				alder->runAction(FadeTo::create(0.25f, 0));
			});
		}, Alder::MapKeyAlder);

		ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
		{
			sarude->setState(StateKeys::CinematicDestinationX, Value(destCoords.x));
			
			sarude->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				sarude->runAction(FadeTo::create(0.25f, 0));
			});
		
			sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				interactionBehavior->clearPretext();
			});
		}, Sarude::MapKeySarude);

		ObjectEvents::watchForObject<Aster>(this, [=](Aster* aster)
		{
			aster->setState(StateKeys::CinematicDestinationX, Value(destCoords.x));
			
			aster->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				aster->runAction(FadeTo::create(0.25f, 0));
			});
		}, Aster::MapKeyAster);

		ObjectEvents::watchForObject<Merlin>(this, [=](Merlin* merlin)
		{
			merlin->setState(StateKeys::CinematicDestinationX, Value(destCoords.x));
			
			merlin->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				merlin->runAction(FadeTo::create(0.25f, 0));
			});
		}, Merlin::MapKeyMerlin);
	}
}

void AfterFight::despawnMages()
{
	ObjectEvents::watchForObject<Igneus>(this, [=](Igneus* igneus)
	{
		igneus->setOpacity(0);
	}, Igneus::MapKeyIgneus);

	ObjectEvents::watchForObject<Alder>(this, [=](Alder* alder)
	{
		alder->setOpacity(0);
	}, Alder::MapKeyAlder);

	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		sarude->setOpacity(0);

		this->sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->clearPretext();
		});
	}, Sarude::MapKeySarude);

	ObjectEvents::watchForObject<Aster>(this, [=](Aster* aster)
	{
		aster->setOpacity(0);
	}, Aster::MapKeyAster);

	ObjectEvents::watchForObject<Merlin>(this, [=](Merlin* merlin)
	{
		merlin->setOpacity(0);
	}, Merlin::MapKeyMerlin);
}
