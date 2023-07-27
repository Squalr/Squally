#include "WelcomeToMagesGuild.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Npcs/Mages/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WelcomeToMagesGuild::MapKeyQuest = "mages-guild";

WelcomeToMagesGuild* WelcomeToMagesGuild::create(GameObject* owner, QuestLine* questLine)
{
	WelcomeToMagesGuild* instance = new WelcomeToMagesGuild(owner, questLine);

	instance->autorelease();

	return instance;
}

WelcomeToMagesGuild::WelcomeToMagesGuild(GameObject* owner, QuestLine* questLine) : super(owner, questLine, WelcomeToMagesGuild::MapKeyQuest, false)
{
}

WelcomeToMagesGuild::~WelcomeToMagesGuild()
{
}

void WelcomeToMagesGuild::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;

		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			this->squally = squally;
			
			if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
			{
				this->runCinematicSequence();
			}
		}, Squally::MapKey);
	}, Marcel::MapKey);
}

void WelcomeToMagesGuild::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void WelcomeToMagesGuild::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFTalkToSarude);
}

void WelcomeToMagesGuild::onSkipped()
{
}

void WelcomeToMagesGuild::runCinematicSequence()
{
	if (this->marcel == nullptr)
	{
		return;
	}

	this->marcel->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_A_WelcomeToMagesGuild::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->marcel, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_B_BroadcastedAndSent::create()->setStringReplacementVariables(
				Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->marcel, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			true
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Marcel_C_SpeakToSarude::create()->setStringReplacementVariables(
				Strings::Platformer_Entities_Names_Npcs_DataMines_Sarude::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->marcel, true)
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
