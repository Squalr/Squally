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
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Buffs/RestoreHealth/RestoreHealth.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Platformer/Quests/Intro/HackerModeCombat.h"

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

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->hasTutorialRun = false;
	this->scrappy = nullptr;
}

RestorePotionTutorialBehavior::~RestorePotionTutorialBehavior()
{
}

void RestorePotionTutorialBehavior::onLoad()
{
	RestorePotion* restorePotion = this->entity->getInventory()->getItemOfType<RestorePotion>();

	if (restorePotion != nullptr)
	{
		restorePotion->getAssociatedAttack()->registerAttackCompleteCallback([=]()
		{
			this->runTutorial();
		});
	}

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	});

	HackableEvents::TriggerDisallowHackerMode();
}

void RestorePotionTutorialBehavior::runTutorial()
{
	if (this->hasTutorialRun || this->scrappy == nullptr)
	{
		return;
	}

	this->hasTutorialRun = true;

	static const float TutorialDelay = 1.5f;

	this->runAction(Sequence::create(
		DelayTime::create(TutorialDelay),
		CallFunc::create([=]()
		{
			HackableEvents::TriggerAllowHackerMode();
			HackableEvents::TriggerForceHackerModeEnable();

			this->runAction(Sequence::create(
				CallFunc::create([=]()
				{
					this->scrappy->droidChatterSound->play();
				}),
				CallFunc::create([=]()
				{
					this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_Intro_HackerModeCombat::create());
				}),
				DelayTime::create(4.0f),
				CallFunc::create([=]()
				{
					this->scrappy->speechBubble->hideDialogue();
				}),
				nullptr
			));
		}),
		nullptr
	));
}
