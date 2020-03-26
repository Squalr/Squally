#include "ReflectTutorial.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Reflect/Reflect.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReflectTutorial::MapKey = "reflect-tutorial";

ReflectTutorial* ReflectTutorial::create(GameObject* owner)
{
	ReflectTutorial* instance = new ReflectTutorial(owner);

	instance->autorelease();

	return instance;
}

ReflectTutorial::ReflectTutorial(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->hasRunTutorial = false;
	this->tutorialInterrupt = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

ReflectTutorial::~ReflectTutorial()
{
}

void ReflectTutorial::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<Reflect*>(args->buff) != nullptr)
		{
			dynamic_cast<Reflect*>(args->buff)->enableClippy();
			this->runTutorial();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		if (this->hasRunTutorial)
		{
			this->tutorialInterrupt = true;
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
}

void ReflectTutorial::onDisable()
{
	super::onDisable();
}

void ReflectTutorial::runTutorial()
{
	if (this->hasRunTutorial || this->scrappy == nullptr)
	{
		return;
	}

	static const float TutorialDelay = 0.75f;

	this->hasRunTutorial = true;

	// Take-over text disabled
	return;

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
