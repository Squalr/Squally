#include "HasteTutorial.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyHackableCueBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/Haste.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HasteTutorial::MapKey = "haste-tutorial";

HasteTutorial* HasteTutorial::create(GameObject* owner)
{
	HasteTutorial* instance = new HasteTutorial(owner);

	instance->autorelease();

	return instance;
}

HasteTutorial::HasteTutorial(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;
	this->squally = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

HasteTutorial::~HasteTutorial()
{
}

void HasteTutorial::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<Haste*>(args->buff) != nullptr)
		{
			dynamic_cast<Haste*>(args->buff)->enableClippy();
			this->runTutorial();
		}
	}));

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;

		this->scrappy->watchForAttachedBehavior<ScrappyHackableCueBehavior>([=](ScrappyHackableCueBehavior* scrappyHackableCueBehavior)
		{
			scrappyHackableCueBehavior->disable();
		});
	}, Scrappy::MapKey);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	HackableEvents::TriggerDisallowHackerMode();
}

void HasteTutorial::onDisable()
{
	super::onDisable();
}

void HasteTutorial::runTutorial()
{
	if (this->hasRunTutorial || this->scrappy == nullptr)
	{
		return;
	}

	static const float TutorialDelay = 0.25f;

	this->hasRunTutorial = true;

	this->runAction(Sequence::create(
		DelayTime::create(TutorialDelay),
		CallFunc::create([=]()
		{
			if (this->tutorialInterrupt)
			{
				return;
			}

			CombatEvents::TriggerPauseTimelineCinematic();
			HackableEvents::TriggerDisallowHackerMode();

			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Menus_Hacking_HackWarning::create(),
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
