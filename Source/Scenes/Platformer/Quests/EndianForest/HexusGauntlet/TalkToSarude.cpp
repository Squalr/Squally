#include "TalkToSarude.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/DataMines/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToSarude::MapKeyQuest = "talk-to-sarude";
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
	ObjectEvents::WatchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->sarude->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableNewQuest();
			});
		}
	}, Sarude::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->portal->closePortal(true);
		}

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

	if (this->sarude != nullptr)
	{
		this->sarude->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}

	Objectives::SetCurrentObjective(ObjectiveKeys::EFBeatGauntlet);
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
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_A_CallForHelp::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Ellipses::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
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
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_B_DoYouRemember::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Ellipses::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
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
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_C_IThoughtNot::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_D_YouNeedTraining::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_E_ToBeginYouMustLearnHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_F_HexusIsAGameWhere::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_G_WhoeverMastersHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_H_PortalToGauntlet::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
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
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}
