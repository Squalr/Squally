#include "RestorePotionTutorialBehavior.h"

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
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestoreHealth.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RestorePotionTutorialBehavior::MapKeyAttachedBehavior = "restore-potion-tutorial";

RestorePotionTutorialBehavior* RestorePotionTutorialBehavior::create(GameObject* owner)
{
	RestorePotionTutorialBehavior* instance = new RestorePotionTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

RestorePotionTutorialBehavior::RestorePotionTutorialBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->hasTutorialRun = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

RestorePotionTutorialBehavior::~RestorePotionTutorialBehavior()
{
}

void RestorePotionTutorialBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (dynamic_cast<RestoreHealth*>(args->buff) != nullptr)
		{
			dynamic_cast<RestoreHealth*>(args->buff)->enableClippy();
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
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void RestorePotionTutorialBehavior::runTutorial()
{
	if (this->hasTutorialRun || this->scrappy == nullptr)
	{
		return;
	}

	this->hasTutorialRun = true;

	static const float TutorialDelay = RestoreHealth::StartDelay + RestoreHealth::TimeBetweenTicks * 2.0f + 0.1f;
	
	CombatEvents::TriggerPauseTimeline();

	this->runAction(Sequence::create(
		DelayTime::create(TutorialDelay),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Intro_F_HackerModeCombat::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Top,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->scrappy, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					CombatEvents::TriggerResumeTimeline();
				},
				SoundResources::Platformer_Entities_Droid_DroidChatter
			));

			// HackableEvents::TriggerForceHackerModeEnable();
		}),
		nullptr
	));
}
