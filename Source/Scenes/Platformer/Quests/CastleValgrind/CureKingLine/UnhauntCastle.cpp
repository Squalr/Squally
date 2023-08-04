#include "UnhauntCastle.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Haunted/EntityHauntedBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/FountainRoomKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string UnhauntCastle::MapKeyQuest = "unhaunt-castle";
const std::string UnhauntCastle::SaveKeySoulHarvestedCount = "SAVE_KEY_SOUL_HARVESTED_COUNT";
const std::string UnhauntCastle::SaveKeyPrefixUnhaunted = "SAVE_KEY_UNHAUNTED_";
const int UnhauntCastle::MaxUnhauntCount = 6;

UnhauntCastle* UnhauntCastle::create(GameObject* owner, QuestLine* questLine)
{
	UnhauntCastle* instance = new UnhauntCastle(owner, questLine);

	instance->autorelease();

	return instance;
}

UnhauntCastle::UnhauntCastle(GameObject* owner, QuestLine* questLine) : super(owner, questLine, UnhauntCastle::MapKeyQuest, false)
{
}

UnhauntCastle::~UnhauntCastle()
{
}

void UnhauntCastle::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Mabel>(this, [=](Mabel* mabel)
	{
		this->mabel = mabel;
		
		if (questState == QuestState::Active)
		{
			this->updateQuestVisuals();
		}
	}, Mabel::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		this->secretDoorPortal = portal;

		if (questState != QuestState::None)
		{
			this->secretDoorPortal->unlock();
		}
	}, "secret-door");

	ObjectEvents::WatchForObject<GameObject>(this, [=](GameObject* bookshelf)
	{
		this->bookshelf = bookshelf;

		if (questState == QuestState::Complete)
		{
			this->moveBookshelf(false);
		}
	}, "secret-bookshelf");
}

void UnhauntCastle::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	// Defer just in case Mabel is not initialized yet
	this->defer([=]()
	{
		if (isActiveThroughSkippable)
		{
			this->updateQuestVisuals();
		}
	}, 2);
}

void UnhauntCastle::onComplete()
{
	this->moveBookshelf(true);

	if (this->secretDoorPortal != nullptr)
	{
		this->secretDoorPortal->unlock();
	}

	this->mabel->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});

	Objectives::SetCurrentObjective(ObjectiveKeys::CVExploreSecretTunnel);
}

void UnhauntCastle::onSkipped()
{
	this->removeAllListeners();
}

void UnhauntCastle::updateQuestVisuals()
{
	if (this->mabel == nullptr)
	{
		return;
	}

	bool isOtherWorld = GameUtils::getKeyOrDefault(this->mabel->properties, EntityHauntedBehavior::PropertyOtherWorld, Value(false)).asBool();

	if (isOtherWorld)
	{
		return;
	}

	this->mabel->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		int currentCureCount = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeySoulHarvestedCount, Value(0)).asInt();

		if (currentCureCount >= UnhauntCastle::MaxUnhauntCount)
		{
			questBehavior->enableTurnIn();

			this->runCinematicSequence();
		}
		// Check for at least one unhaunted entity, such as to not give spoilers for the unhaunting quest
		else if (currentCureCount >= 1)
		{
			questBehavior->enableIncompleteQuest();

			this->setPreText();
		}
	});
}

void UnhauntCastle::runCinematicSequence()
{
	if (this->mabel == nullptr)
	{
		return;
	}
	
	this->mabel->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_V_ThankYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
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
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true),
				true
			),
			[=]()
			{
			},
			"",
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_W_ThroneRoomBlocked::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceQuestion(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_X_SecretTunnels::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_Y_Perhaps::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceQuestion(),
			true
		));
	});
}

void UnhauntCastle::setPreText()
{
	if (this->mabel == nullptr)
	{
		return;
	}

	this->defer([=]()
	{
		this->mabel->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			int remaining = UnhauntCastle::MaxUnhauntCount - SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeySoulHarvestedCount, Value(0)).asInt();

			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_Q_Remaining::create()
					->setStringReplacementVariables(ConstantString::create(std::to_string(remaining))),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->mabel, true)
				),
				[=]()
				{
					this->setPreText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});
	});
}

void UnhauntCastle::moveBookshelf(bool animate)
{
	if (this->bookshelf == nullptr)
	{
		return;
	}

	Vec2 startPos = this->bookshelf->getPosition();

	if (animate)
	{
		this->bookshelf->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.0f, startPos + Vec2(512.0f, 0.0f))),
			nullptr
		));
	}
	else
	{
		this->bookshelf->setPositionX(startPos.x + 512.0f);
	}
}
