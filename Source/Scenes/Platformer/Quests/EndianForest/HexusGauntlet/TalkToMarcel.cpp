#include "TalkToMarcel.h"

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
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Ellipses.h"
#include "Strings/Platformer/Entities/Names/Helpers/EndianForest/Scrappy.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/A_WelcomeToMagesGuild.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/B_BroadcastedAndSent.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/C_WeNeededSomeone.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/D_FirstYouMustLearnHexus.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/E_HexusIsAGameWhere.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/F_WhoeverMastersHexus.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/G_PortalToGauntlet.h"

using namespace cocos2d;

const std::string TalkToMarcel::MapKeyQuest = "talk-to-marcel";
const std::string TalkToMarcel::QuestPortalTag = "quest-portal";

TalkToMarcel* TalkToMarcel::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToMarcel* instance = new TalkToMarcel(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToMarcel::TalkToMarcel(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToMarcel::MapKeyQuest, questTag, false)
{
	this->marcel = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

TalkToMarcel::~TalkToMarcel()
{
}

void TalkToMarcel::onLoad(QuestState questState)
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
	}, TalkToMarcel::QuestPortalTag);
}

void TalkToMarcel::onActivate(bool isActiveThroughSkippable)
{
	this->registerDialogue();
}

void TalkToMarcel::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void TalkToMarcel::onSkipped()
{
	this->removeAllListeners();
}

void TalkToMarcel::registerDialogue()
{
	this->marcel->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_A_WelcomeToMagesGuild::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort1,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_B_BroadcastedAndSent::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort2,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Ellipses::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::HardRight,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true),
				true
			),
			[=]()
			{
			},
			"",
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_D_FirstYouMustLearnHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterLong1,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_E_HexusIsAGameWhere::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_F_WhoeverMastersHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium3,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_G_PortalToGauntlet::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			true
		));
	});
}
