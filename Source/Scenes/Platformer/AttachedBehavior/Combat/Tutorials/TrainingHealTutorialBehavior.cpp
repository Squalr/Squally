#include "TrainingHealTutorialBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Events/DialogueEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyHackableCueBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/TrainingDummy/TrainingHeal/TrainingHeal.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TrainingHealTutorialBehavior::MapKey = "training-heal-tutorial";
const int TrainingHealTutorialBehavior::HealsBeforeTutorial = 2;

TrainingHealTutorialBehavior* TrainingHealTutorialBehavior::create(GameObject* owner)
{
	TrainingHealTutorialBehavior* instance = new TrainingHealTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

TrainingHealTutorialBehavior::TrainingHealTutorialBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->healCount = 0;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

TrainingHealTutorialBehavior::~TrainingHealTutorialBehavior()
{
}

void TrainingHealTutorialBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<TrainingHeal*>(args->buff) != nullptr)
		{
			dynamic_cast<TrainingHeal*>(args->buff)->enableClippy();
			this->runTutorial();
		}
	}));

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;

		this->scrappy->watchForAttachedBehavior<ScrappyHackableCueBehavior>([=](ScrappyHackableCueBehavior* scrappyHackableCueBehavior)
		{
			scrappyHackableCueBehavior->disable();
		});
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	HackableEvents::TriggerDisallowHackerMode();
}

void TrainingHealTutorialBehavior::onDisable()
{
	super::onDisable();
}

void TrainingHealTutorialBehavior::runTutorial()
{
	if (healCount > TrainingHealTutorialBehavior::HealsBeforeTutorial|| this->scrappy == nullptr)
	{
		return;
	}

	if (++this->healCount == TrainingHealTutorialBehavior::HealsBeforeTutorial)
	{
		static const float TutorialDelay = 0.1f;

		this->runAction(Sequence::create(
			DelayTime::create(TutorialDelay),
			CallFunc::create([=]()
			{
				CombatEvents::TriggerPauseTimelineCinematic();

				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_Intro_G_HackerModeCombat::create()
						->setStringReplacementVariables(Strings::Common_Brackets::create())
						->setStringReplacementVariables(Strings::Input_Tab::create()),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Top,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						CombatEvents::TriggerResumeTimelineCinematic();
						HackableEvents::TriggerAllowHackerMode();
					},
					SoundResources::Platformer_Entities_Droid_DroidChatter
				));
			}),
			nullptr
		));
	}
}
