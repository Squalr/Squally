#include "SneakPastLycan.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/FXResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SneakPastLycan::MapKeyQuest = "sneak-past-lycan";

SneakPastLycan* SneakPastLycan::create(GameObject* owner, QuestLine* questLine)
{
	SneakPastLycan* instance = new SneakPastLycan(owner, questLine);

	instance->autorelease();

	return instance;
}

SneakPastLycan::SneakPastLycan(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SneakPastLycan::MapKeyQuest, false)
{
	this->sleepFx = SmartAnimationSequenceNode::create(FXResources::Sleep_Sleep_0000);

	this->sleepFx->setVisible(false);

	this->addChild(this->sleepFx);
}

SneakPastLycan::~SneakPastLycan()
{
}

void SneakPastLycan::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Lycan>(this, [=](Lycan* lycan)
	{
		this->lycan = lycan;

		// Hacky, but this is the only real way to add the sleeping state to this quest without reworking the quest line and breaking backwards compatibility
		bool hasHelper = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString() != "";

		if (questState == QuestState::Complete)
		{
			this->lycan->despawn();
		}
		else if (!hasHelper)
		{
			this->runCinematicSequence();
		}
		else
		{
			this->runSleepingCinematicSequence();
		}
	}, Lycan::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void SneakPastLycan::onActivate(bool isActiveThroughSkippable)
{
}

void SneakPastLycan::onComplete()
{
}

void SneakPastLycan::onSkipped()
{
	this->removeAllListeners();
}

void SneakPastLycan::runCinematicSequence()
{
	if (this->lycan == nullptr)
	{
		return;
	}

	this->lycan->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Entities_EndianForest_Lycan_LetMeIntoTown::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Entities_EndianForest_Lycan_NobodyAllowedIntoTown::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->lycan, true)
					),
					[=]()
					{
						Objectives::SetCurrentObjective(ObjectiveKeys::EFExploreMagesGuild);
					},
					Voices::GetNextVoiceShort(),
					true
				));
			}),
			0.5f
		);
	});
}

void SneakPastLycan::runSleepingCinematicSequence()
{
	static const std::vector<std::string>& sleepAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(FXResources::Sleep_Sleep_0000);

	// TODO: Swap for sleep anim
	this->lycan->getAnimations()->playAnimation("Sit", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f));

	GameUtils::setWorldCoords(this->sleepFx, GameUtils::getWorldCoords(this->lycan) + Vec2(0.0f, 256.0f));
	this->sleepFx->setVisible(true);

	this->sleepFx->playAnimationRepeat(sleepAnimationFiles, 0.075f);
}
