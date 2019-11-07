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
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Ellipses.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/FirstChallenge.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/HexusIsAGameWhere.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/HowWouldYouLikeToPlay.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/LegendHasItHexus.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/ReadyToStart.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/WelcomeToMagesGuild.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/WishToLearn.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/YouveNeverHeardOfHexus.h"

using namespace cocos2d;

const std::string TalkToSarude::MapKeyQuest = "talk-to-sarude";
const std::string TalkToSarude::QuestPortalTag = "quest-portal";

TalkToSarude* TalkToSarude::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToSarude* instance = new TalkToSarude(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToSarude::TalkToSarude(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToSarude::MapKeyQuest, questTag, false)
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
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

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
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_WelcomeToMagesGuild::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_HowWouldYouLikeToPlay::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Ellipses::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::HardRight,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true),
				true
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_YouveNeverHeardOfHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_HexusIsAGameWhere::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_LegendHasItHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_WishToLearn::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(this->sarude, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
			),
			[=]()
			{
			}
		));

		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_ReadyToStart::create(),
			[=]()
			{
				DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_FirstChallenge::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(this->sarude, false),
						DialogueEvents::BuildPreviewNode(this->squally, true)
					),
					[=]()
					{
						this->complete();
					}
				));
			}),
			1.0f
		);
	});
}
