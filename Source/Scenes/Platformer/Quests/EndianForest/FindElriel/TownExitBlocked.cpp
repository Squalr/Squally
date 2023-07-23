#include "TownExitBlocked.h"

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
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Npcs/EndianForest/Bard.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Npcs/EndianForest/Mara.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/BossExitUnlocked.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/ReturnToQueen.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/SneakPastLycan.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToGrogg.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToQueen.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToChiron.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownArrival.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownExitBlocked.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/WindSpellbook.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TownExitBlocked::MapKeyQuest = "town-exit-blocked";
const std::string TownExitBlocked::TagBlockedExit = "blocked-exit";

TownExitBlocked* TownExitBlocked::create(GameObject* owner, QuestLine* questLine)
{
	TownExitBlocked* instance = new TownExitBlocked(owner, questLine);

	instance->autorelease();

	return instance;
}

TownExitBlocked::TownExitBlocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TownExitBlocked::MapKeyQuest, false)
{
	this->chiron = dynamic_cast<Chiron*>(owner);
}

TownExitBlocked::~TownExitBlocked()
{
}

void TownExitBlocked::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void TownExitBlocked::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Bard>(this, [=](Bard* bard)
	{
		this->bard = bard;
		this->attachBardBehavior();
	}, Bard::MapKey);

	ObjectEvents::WatchForObject<Mara>(this, [=](Mara* mara)
	{
		this->mara = mara;
		this->attachMaraBehavior();
	}, Mara::MapKey);

	if (questState == QuestState::Complete)
	{
		this->defer([=]()
		{
			this->chiron->despawn();
		});
	}
	else
	{
		this->defer([=]()
		{
			this->attachChironBehavior();
		});

		ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
		{
			this->townExitPortal = portal;
			this->townExitPortal->disable();
		}, TownExitBlocked::TagBlockedExit);
	}
}

void TownExitBlocked::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void TownExitBlocked::attachChironBehavior()
{
	this->chiron->attachComponent(LookAtSquallyBehavior::create(this->chiron));

	this->chironCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->chiron->getEntitySize(), 8.0f),
		(CollisionType)PlatformerCollisionType::Cinematic,
		CollisionObject::Properties(false, false)
	);
	this->chironCollision->setPosition(Vec2(0.0f, this->chiron->getEntitySize().height / 2.0f));

	this->chiron->addChild(this->chironCollision);

	this->chironCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerMovement, (int)PlatformerCollisionType::Hover }, [=](CollisionData collisionData)
	{
		if (!this->isEngagedInDialogue && this->dialogueCooldown <= 0.0f)
		{
			this->isEngagedInDialogue = true;

			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Chiron_A_CantLeaveTown::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->chiron, true)
				),
				[=]()
				{
					this->isEngagedInDialogue = false;
					this->dialogueCooldown = 6.0f;
				},
				SoundResources::Platformer_Entities_Generic_ChatterAnnoyed1
			));
		}
		
		return CollisionResult::CollideWithPhysics;
	});
}

void TownExitBlocked::attachBardBehavior()
{
	if (this->bard == nullptr)
	{
		return;
	}

	this->bard->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_EndianForest_FindElriel_Bard_A_WhereAreDocks::create(),
			[=]()
			{
				// Load 'where is queen' text if not at that part of the quest
				if (!this->questLine->isCompleteUpToInclusive(TalkToQueen::MapKeyQuest))
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_EndianForest_FindElriel_Bard_B_RightButTalkToQueen::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->bard, true)
						),
						[=]()
						{
							Objectives::SetCurrentObjective(ObjectiveKeys::EFVisitQueen);
						},
						Voices::GetNextVoiceLong()
					));
				}
			}),
			1.0f
		);
	});
}

void TownExitBlocked::attachMaraBehavior()
{
	if (mara == nullptr)
	{
		return;
	}

	this->mara->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (this->questLine->isComplete())
		{
			// Default dialogue for Mara, to hint at visiting blacksmiths
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Mara_X_GossipBlacksmiths::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->mara, true)
				),
				[=]()
				{
					this->defer([=]()
					{
						this->attachMaraBehavior();
					});
				},
				Voices::GetNextVoiceLong()
			));
		}
		else if (this->questLine->isCompleteUpToInclusive(BossExitUnlocked::MapKeyQuest))
		{
			// 2nd prio text, hinting that you need to return to the queen after finding Elriel
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Mara_T_GossipFoundElriel::create()
					->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->mara, true)
				),
				[=]()
				{
					this->defer([=]()
					{
						this->attachMaraBehavior();
					});
				},
				Voices::GetNextVoiceLong()
			));
		}
		else if (this->questLine->isCompleteUpToInclusive(TalkToQueen::MapKeyQuest))
		{
			// 3rd prio text, hinting that Elriel should be found
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Mara_S_GossipFindElriel::create()
					->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->mara, true)
				),
				[=]()
				{
					this->defer([=]()
					{
						this->attachMaraBehavior();
					});
				},
				Voices::GetNextVoiceLong()
			));
		}
		else
		{
			// 4th prio text, hinting that you should talk to queen
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Platformer_Quests_EndianForest_FindElriel_Mara_A_WhereAreDocks::create(),
				[=]()
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_EndianForest_FindElriel_Mara_B_RightButTalkToQueen::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->mara, true)
						),
						[=]()
						{
							Objectives::SetCurrentObjective(ObjectiveKeys::EFVisitQueen);
						},
						Voices::GetNextVoiceLong()
					));
				}),
				1.0f
			);
		}
	});
}

void TownExitBlocked::onComplete()
{
}

void TownExitBlocked::onSkipped()
{
	this->removeAllListeners();
}

void TownExitBlocked::update(float dt)
{
	super::update(dt);

	if (!isEngagedInDialogue && this->dialogueCooldown > 0.0f)
	{
		this->dialogueCooldown -= dt;
	}
}
