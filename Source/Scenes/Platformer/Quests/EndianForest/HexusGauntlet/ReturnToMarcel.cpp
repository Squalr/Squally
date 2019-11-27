#include "ReturnToMarcel.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/EndianForest/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/MarcelTutorialBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/SoundResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/K_IChallengeYou.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/M_WellDone.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/N_WeBroughtYouHere.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/O_UnknownForce.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/P_OnlyYouCanDefeat.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/Q_LearnMoreOfTheseMonsters.h"

using namespace cocos2d;

const std::string ReturnToMarcel::MapKeyQuest = "return-to-marcel";
const std::string ReturnToMarcel::QuestPortalTag = "quest-portal";

ReturnToMarcel* ReturnToMarcel::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ReturnToMarcel* instance = new ReturnToMarcel(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ReturnToMarcel::ReturnToMarcel(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ReturnToMarcel::MapKeyQuest, questTag, false)
{
	this->marcel = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

ReturnToMarcel::~ReturnToMarcel()
{
}

void ReturnToMarcel::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;
	}, Marcel::MapKeyMarcel);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState != QuestState::Complete)
		{
			this->portal->closePortal(true);
		}
	}, ReturnToMarcel::QuestPortalTag);
}

void ReturnToMarcel::onActivate(bool isActiveThroughSkippable)
{
	this->registerDialogue();
}

void ReturnToMarcel::onComplete()
{
}

void ReturnToMarcel::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToMarcel::registerDialogue()
{
	if (this->marcel != nullptr)
	{
		this->marcel->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			// Pre-text chain
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_K_IChallengeYou::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->marcel, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
				},
				SoundResources::Platformer_Entities_Generic_ChatterShort1
			));
		});

		MarcelTutorialBehavior* behavior = MarcelTutorialBehavior::create(this->marcel);

		behavior->registerWinCallback([=]()
		{
			this->onHexusWin();
		});

		this->marcel->attachBehavior(behavior);
	}
}

void ReturnToMarcel::onHexusWin()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_M_WellDone::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->marcel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_N_WeBroughtYouHere::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_O_UnknownForce::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Top,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->marcel, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_P_OnlyYouCanDefeat::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Top,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->marcel, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_Q_LearnMoreOfTheseMonsters::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Top,
							DialogueBox::DialogueAlignment::Left,
							DialogueEvents::BuildPreviewNode(&this->marcel, false),
							DialogueEvents::BuildPreviewNode(&this->squally, true)
						),
						[=]()
						{
						},
						SoundResources::Platformer_Entities_Generic_ChatterLong1,
						true
						));
					},
					SoundResources::Platformer_Entities_Generic_ChatterMedium4,
					false
					));
				},
				SoundResources::Platformer_Entities_Generic_ChatterMedium3,
				false
				));
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
			));
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium1,
		false
	));
}
