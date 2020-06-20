#include "MeetScrappy.h"

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
#include "Engine/Events/SceneEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HelperEvents.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MeetScrappy::MapKeyQuest = "meet-scrappy";
const std::string MeetScrappy::TagScrappyStop = "scrappy-stop";

MeetScrappy* MeetScrappy::create(GameObject* owner, QuestLine* questLine)
{
	MeetScrappy* instance = new MeetScrappy(owner, questLine);

	instance->autorelease();

	return instance;
}

MeetScrappy::MeetScrappy(GameObject* owner, QuestLine* questLine) : super(owner, questLine, MeetScrappy::MapKeyQuest, true)
{
	this->scrappy = dynamic_cast<Scrappy*>(owner);
	this->squally = nullptr;
	this->droidAlarmedSound = WorldSound::create(SoundResources::Platformer_Entities_Droid_Alarmed);

	this->addChild(this->droidAlarmedSound);
}

MeetScrappy::~MeetScrappy()
{
}

void MeetScrappy::onLoad(QuestState questState)
{
	if (this->scrappy != nullptr)
	{
		this->scrappy->getAnimations()->setFlippedX(true);

		if (questState == QuestState::Complete)
		{
			this->scrappy->setVisible(false);
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void MeetScrappy::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(MeetScrappy::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequencePt1();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->complete();
	}));
}

void MeetScrappy::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFHeadToTown);
}

void MeetScrappy::onSkipped()
{
	this->removeAllListeners();
}

void MeetScrappy::runCinematicSequencePt1()
{
	Vec2 positionA = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		positionA = GameUtils::getWorldCoords(cinematicMarker);
	}), MeetScrappy::TagScrappyStop);

	if (this->scrappy != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->scrappy->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->droidAlarmedSound->play();
			}),
			EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
			CallFunc::create([=]()
			{
				this->scrappy->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
				{
					interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_A_YoureAlive::create(), Voices::GetNextVoiceShort(Voices::VoiceType::Droid), 2.0f, [=]()
					{
						this->runCinematicSequencePt2();
					});
				});
			}),
			nullptr
		));
	}
}

void MeetScrappy::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Intro_B_DistressBeacon::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void MeetScrappy::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Intro_C_GetYouPatched::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void MeetScrappy::runCinematicSequencePt4()
{
	if (this->scrappy != nullptr)
	{
		this->scrappy->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				Vec2 positionB = Vec2::ZERO;

				ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* squally)
				{
					positionB = GameUtils::getWorldCoords(squally);
				}), Squally::MapKey);

				this->scrappy->runAction(EaseSineInOut::create(MoveTo::create(1.0f, positionB)));
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				this->scrappy->setVisible(false);

				NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
					nullptr,
					Strings::Platformer_Notifications_Party_HelperJoinedParty::create()->setStringReplacementVariables(this->scrappy->getEntityName()),
					this->scrappy->getEmblemResource(),
					SoundResources::Notifications_NotificationGood2
				));
				HelperEvents::TriggerFindScrappy();
				PlatformerEvents::TriggerCinematicRestore();

				this->complete();
			}),
			nullptr
		));
	}
}
