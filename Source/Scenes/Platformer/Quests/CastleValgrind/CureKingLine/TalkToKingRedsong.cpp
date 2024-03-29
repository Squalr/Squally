#include "TalkToKingRedsong.h"

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
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsong.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsongSlime.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leroy.h"
#include "Entities/Platformer/Npcs/CastleValgrind/PrincessOpal.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/CastleValgrind/CryptKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToKingRedsong::MapKeyQuest = "talk-to-king-redsong";

TalkToKingRedsong* TalkToKingRedsong::create(GameObject* owner, QuestLine* questLine)
{
	TalkToKingRedsong* instance = new TalkToKingRedsong(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToKingRedsong::TalkToKingRedsong(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToKingRedsong::MapKeyQuest, false)
{
}

TalkToKingRedsong::~TalkToKingRedsong()
{
}

void TalkToKingRedsong::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<KingRedsong>(this, [=](KingRedsong* kingRedsong)
	{
		this->kingRedsong = kingRedsong;

		if (questState == QuestState::None)
		{
			this->cinematicDespawn(this->kingRedsong);
		}
	}, KingRedsong::MapKey);

	ObjectEvents::WatchForObject<KingRedsongSlime>(this, [=](KingRedsongSlime* kingRedsongSlime)
	{
		this->kingRedsongSlime = kingRedsongSlime;
		
		if (questState != QuestState::None)
		{
			this->cinematicDespawn(this->kingRedsongSlime);
		}
	}, KingRedsongSlime::MapKey);

	ObjectEvents::WatchForObject<Leroy>(this, [=](Leroy* leroy)
	{
		this->leroy = leroy;
		
		if (questState != QuestState::None)
		{
			this->cinematicDespawn(this->leroy);
		}
	}, Leroy::MapKey);

	ObjectEvents::WatchForObject<PrincessOpal>(this, [=](PrincessOpal* princessOpal)
	{
		this->princessOpal = princessOpal;

		if (questState == QuestState::None)
		{
			this->cinematicDespawn(this->princessOpal);
		}
	}, PrincessOpal::MapKey);
}

void TalkToKingRedsong::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	// Defer 1 frame to ensure that dialogue cinematic hijack works
	this->defer([=]()
	{
		this->runCinematicSequencePt1();
	});

	if (this->leroy != nullptr)
	{
		this->cinematicDespawn(this->leroy);
	}

	if (this->kingRedsongSlime != nullptr)
	{
		this->cinematicDespawn(this->kingRedsongSlime);
	}

	if (this->princessOpal != nullptr)
	{
		this->cinematicRespawn(this->princessOpal);
	}

	if (this->kingRedsong != nullptr)
	{
		this->cinematicRespawn(this->kingRedsong);
	}
}

void TalkToKingRedsong::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::CVEnterLambdaCrypts);
}

void TalkToKingRedsong::onSkipped()
{
	this->removeAllListeners();
}

void TalkToKingRedsong::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_A_ThankYou::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToKingRedsong::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_B_TheWitch::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToKingRedsong::runCinematicSequencePt3()
{
	if (this->guano != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_C_GuanoFireGuards::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
			),
			[=]()
			{
				this->runCinematicSequencePt4();
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Human),
			true
		));
	}
	else if (this->gecky != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_C_Generic::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->gecky, false),
				DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
			),
			[=]()
			{
				this->runCinematicSequencePt4();
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Human),
			true
		));
	}
	else
	{
		this->runCinematicSequencePt4();
	}
}

void TalkToKingRedsong::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_D_CanWeEnterCrypts::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
		),
		[=]()
		{
				this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		true
	));
}

void TalkToKingRedsong::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_KingRedsong_E_OfCourse::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->kingRedsong, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ CryptKey::create() }));
			this->complete();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void TalkToKingRedsong::cinematicDespawn(PlatformerEntity* entity)
{
	if (entity == nullptr)
	{
		return;
	}

	entity->setOpacity(0);
	entity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->kill();
	});
}

void TalkToKingRedsong::cinematicRespawn(PlatformerEntity* entity)
{
	if (entity == nullptr)
	{
		return;
	}

	entity->setOpacity(255);
	entity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->revive();
	});
}
