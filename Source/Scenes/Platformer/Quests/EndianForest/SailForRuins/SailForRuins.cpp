#include "SailForRuins.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Strings/Platformer/Quests/EndianForest/SailForRuins/BlackBeard/CanWeBoard.h"
#include "Strings/Platformer/MapNames/Zones/UnderflowRuins.h"

using namespace cocos2d;

const std::string SailForRuins::MapKeyQuest = "sail-for-ruins";

SailForRuins* SailForRuins::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	SailForRuins* instance = new SailForRuins(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

SailForRuins::SailForRuins(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, SailForRuins::MapKeyQuest, questTag, false)
{
	this->blackbeard = nullptr;
}

SailForRuins::~SailForRuins()
{
}

void SailForRuins::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Blackbeard>(this, [=](Blackbeard* blackbeard)
	{
		this->blackbeard = blackbeard;

		if (questState == QuestState::None)
		{
			this->blackbeard->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					Strings::Platformer_Quests_EndianForest_SailForRuins_BlackBeard_CanWeBoard::create()->setStringReplacementVariables(Strings::Platformer_MapNames_Zones_UnderflowRuins::create()),
					[=]()
					{
					}),
					0.5f
				);
			});
		}
	}, Blackbeard::MapKeyBlackbeard);
}

void SailForRuins::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void SailForRuins::onComplete()
{
}

void SailForRuins::onSkipped()
{
}

void SailForRuins::runCinematicSequence()
{
	if (this->blackbeard == nullptr)
	{
		return;
	}

	this->complete();
}
