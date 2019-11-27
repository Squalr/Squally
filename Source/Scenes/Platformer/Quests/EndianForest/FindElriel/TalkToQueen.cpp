#include "TalkToQueen.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/EndianForest/QueenLiana.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Elriel.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/A_HowDoWeGetToTheRuins.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/B_HowDareYou.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/C_NobodyLeavesUntil.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/D_WhatIfWeHelp.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/E_YouWouldHelp.h"
#include "Strings/Platformer/Quests/EndianForest/FindElriel/Queen/F_OrderMyGuards.h"

using namespace cocos2d;

const std::string TalkToQueen::MapKeyQuest = "talk-to-queen";

TalkToQueen* TalkToQueen::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToQueen* instance = new TalkToQueen(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToQueen::TalkToQueen(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToQueen::MapKeyQuest, questTag, false)
{
	this->guano = nullptr;
	this->queenLiana = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToQueen::~TalkToQueen()
{
}

void TalkToQueen::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKeyGuano);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<QueenLiana>(this, [=](QueenLiana* queenLiana)
	{
		this->queenLiana = queenLiana;
	}, QueenLiana::MapKeyQueenLiana);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void TalkToQueen::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void TalkToQueen::onComplete()
{
}

void TalkToQueen::onSkipped()
{
	this->removeAllListeners();
}

void TalkToQueen::runCinematicSequence()
{
	if (this->queenLiana == nullptr)
	{
		return;
	}
	
	this->queenLiana->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_A_HowDoWeGetToTheRuins::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->guano, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_B_HowDareYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->guano, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort2,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_C_NobodyLeavesUntil::create()
				->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create() }),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->guano, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterLong1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_D_WhatIfWeHelp::create()
				->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create() }),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Droid_DroidChatter,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_E_YouWouldHelp::create()
				->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create() }),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium3,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_F_OrderMyGuards::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->queenLiana, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			true
		));
	});
}

void TalkToQueen::setPostText()
{

}
