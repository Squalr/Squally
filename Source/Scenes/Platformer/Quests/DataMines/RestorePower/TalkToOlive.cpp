#include "TalkToOlive.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/Olive.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToOlive::MapKeyQuest = "talk-to-olive";

TalkToOlive* TalkToOlive::create(GameObject* owner, QuestLine* questLine)
{
	TalkToOlive* instance = new TalkToOlive(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToOlive::TalkToOlive(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToOlive::MapKeyQuest, false)
{
}

TalkToOlive::~TalkToOlive()
{
}

void TalkToOlive::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Olive>(this, [=](Olive* olive)
	{
		this->olive = olive;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->olive->watchForComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableNewQuest();
			});
		}
	});

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->runCinematicSequencePt1();
	}
}

void TalkToOlive::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToOlive::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::URLightTorches);

	if (this->olive != nullptr)
	{
		this->olive->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void TalkToOlive::onSkipped()
{
	this->removeAllListeners();
}

void TalkToOlive::runCinematicSequencePt1()
{
	this->olive->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_StoryMode::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->olive, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_StoryMode::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->olive, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	});
}