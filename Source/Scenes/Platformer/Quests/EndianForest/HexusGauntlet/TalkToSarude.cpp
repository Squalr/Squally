#include "TalkToSarude.h"

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
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToSarude::MapKeyQuest = "talk-to-marcel"; // Keep as marcel until April 2020
const std::string TalkToSarude::QuestPortalTag = "quest-portal";

TalkToSarude* TalkToSarude::create(GameObject* owner, QuestLine* questLine)
{
	TalkToSarude* instance = new TalkToSarude(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToSarude::TalkToSarude(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToSarude::MapKeyQuest, false)
{
	this->sarude = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

TalkToSarude::~TalkToSarude()
{
}

void TalkToSarude::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKeySarude);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
	}, TalkToSarude::QuestPortalTag);
}

void TalkToSarude::onActivate(bool isActiveThroughSkippable)
{
	this->registerDialogue();
}

void TalkToSarude::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void TalkToSarude::onSkipped()
{
	this->removeAllListeners();
}

void TalkToSarude::registerDialogue()
{
	this->sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_A_WelcomeToMagesGuild::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort1,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_B_BroadcastedAndSent::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
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
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
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
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_D_FirstYouMustLearnHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterLong1,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_E_HexusIsAGameWhere::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_F_WhoeverMastersHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium3,
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_G_PortalToGauntlet::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
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
