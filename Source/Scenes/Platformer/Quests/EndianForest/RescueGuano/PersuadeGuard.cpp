#include "PersuadeGuard.h"

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
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/WeakMindedBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/BoredWithoutVisitors.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/DoorTech.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/FollowMe.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/GoingToTheInn.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/NoVisitors.h"

using namespace cocos2d;

const std::string PersuadeGuard::MapKeyQuest = "persuade-guard";
const std::string PersuadeGuard::QuestTagPrison = "prison";
const std::string PersuadeGuard::QuestTagSolidWall = "solid-wall";
const std::string PersuadeGuard::QuestTagInn = "inn";

PersuadeGuard* PersuadeGuard::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	PersuadeGuard* instance = new PersuadeGuard(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

PersuadeGuard::PersuadeGuard(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, PersuadeGuard::MapKeyQuest, questTag, false)
{
	this->lycan = dynamic_cast<Lycan*>(owner);
	this->solidWall = dynamic_cast<CollisionObject*>(owner);
	this->squally = nullptr;
}

PersuadeGuard::~PersuadeGuard()
{
}

void PersuadeGuard::onEnter()
{
	super::onEnter();
}

void PersuadeGuard::onLoad(QuestState questState)
{
	if (this->questTag == PersuadeGuard::QuestTagPrison)
	{
		ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
		{
			this->squally = squally;
		});

		if (this->lycan != nullptr)
		{
			this->lycan->attachBehavior(LookAtSquallyBehavior::create(this->lycan));
		}
	}
	else if (this->questTag == PersuadeGuard::QuestTagSolidWall)
	{
		if (this->solidWall != nullptr && questState == QuestState::Complete)
		{
			this->solidWall->setPhysicsEnabled(false);
		}
	}
}

void PersuadeGuard::onActivate(bool isActiveThroughSkippable)
{
	if (this->questTag == PersuadeGuard::QuestTagPrison)
	{
		if (this->lycan != nullptr)
		{
			this->lycan->attachBehavior(WeakMindedBehavior::create(this->lycan));

			this->lycan->listenForStateWrite(StateKeys::WeakMinded, [=](Value value)
			{
				this->runPersuasionSequence();
			});

			this->runNoVisitorsSequence();
		}
	}
}

void PersuadeGuard::onComplete()
{
	this->removeAllListeners();

	if (this->questTag == PersuadeGuard::QuestTagSolidWall)
	{
		if (this->solidWall != nullptr)
		{
			this->solidWall->setPhysicsEnabled(false);
		}
	}
}

void PersuadeGuard::onSkipped()
{
	this->removeAllListeners();
}

void PersuadeGuard::runNoVisitorsSequence()
{
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicHijack();

			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				// Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_NoVisitors::create(),
				Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_BoredWithoutVisitors::create(),
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				[=]()
				{
					this->runAction(Sequence::create(
						DelayTime::create(1.0f),
						CallFunc::create([=]()
						{
							PlatformerEvents::TriggerCinematicHijack();

							DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
								// Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_NoVisitors::create(),
								Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_BoredWithoutVisitors::create(),
								DialogueBox::DialogueDock::Top,
								DialogueBox::DialogueAlignment::Center,
								[=]()
								{
									this->runAction(Sequence::create(
										DelayTime::create(1.0f),
										CallFunc::create([=]()
										{
											PlatformerEvents::TriggerCinematicHijack();

											DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
												// Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_NoVisitors::create(),
												Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_BoredWithoutVisitors::create(),
												DialogueBox::DialogueDock::Top,
												DialogueBox::DialogueAlignment::Right,
												[=]()
												{
													PlatformerEvents::TriggerCinematicRestore();
												},
												DialogueEvents::BuildPreviewNode(this->squally, false),
												DialogueEvents::BuildPreviewNode(this->lycan, true)
											));
										}),
										nullptr
									));
								},
								DialogueEvents::BuildPreviewNode(this->squally, false),
								DialogueEvents::BuildPreviewNode(this->lycan, true)
							));
						}),
						nullptr
					));
				},
				DialogueEvents::BuildPreviewNode(this->squally, false),
				DialogueEvents::BuildPreviewNode(this->lycan, true)
			));
		}),
		nullptr
	));
}

void PersuadeGuard::runPersuasionSequence()
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicHijack();

			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_BoredWithoutVisitors::create(),
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Right,
				[=]()
				{
					PlatformerEvents::TriggerCinematicRestore();
				},
				DialogueEvents::BuildPreviewNode(this->squally, false),
				DialogueEvents::BuildPreviewNode(this->lycan, true)
			));
		}),
		nullptr
	));
}
