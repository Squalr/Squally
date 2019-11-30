#include "ScrappyHackableCueBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/SpeechBubble.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ScrappyHackableCueBehavior::MapKeyAttachedBehavior = "scrappy-movement";

ScrappyHackableCueBehavior* ScrappyHackableCueBehavior::create(GameObject* owner)
{
	ScrappyHackableCueBehavior* instance = new ScrappyHackableCueBehavior(owner);

	instance->autorelease();

	return instance;
}

ScrappyHackableCueBehavior::ScrappyHackableCueBehavior(GameObject* owner) : super(owner)
{
	this->scrappy = dynamic_cast<Scrappy*>(owner);
	this->cueCooldown = 0.0f;

	if (this->scrappy == nullptr)
	{
		this->invalidate();
	}
}

ScrappyHackableCueBehavior::~ScrappyHackableCueBehavior()
{
}

void ScrappyHackableCueBehavior::update(float dt)
{
	super::update(dt);

	if (this->cueCooldown > 0.0f)
	{
		this->cueCooldown -= dt;
	}
}

void ScrappyHackableCueBehavior::onLoad()
{
	this->scheduleUpdate();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventHackableCombatCue, [=](EventCustom* eventCustom)
	{
		if (this->cueCooldown <= 0.0f)
		{
			this->scrappy->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Dialogue_Combat_Help_UseYourAbilities::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
			});
		}
	}));
}
