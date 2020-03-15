#include "LifeStone.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string LifeStone::MapKeyLifeStone = "life-stone";

LifeStone* LifeStone::create(ValueMap& properties)
{
	LifeStone* instance = new LifeStone(properties);

	instance->autorelease();

	return instance;
}

LifeStone::LifeStone(ValueMap& properties) : super(properties, InteractObject::InteractType::Collision, Size(192.0f, 440.0f), Vec2::ZERO)
{
	this->lifeStone = Sprite::create(ObjectResources::Interactive_LifeStone);
	this->healAnimation = SmartAnimationSequenceNode::create();
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal4);
	this->isAnimating = false;

	static bool runOnce = true;

	if (runOnce)
	{
		runOnce = false;

		SmartAnimationSequenceNode::primeCache(FXResources::Heal_Heal_0000);
	}
	
	this->addChild(this->lifeStone);
	this->addChild(this->healAnimation);
	this->addChild(this->healSound);
}

LifeStone::~LifeStone()
{
}

void LifeStone::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void LifeStone::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->healAnimation));
}

void LifeStone::initializePositions()
{
	super::initializePositions();

	this->lifeStone->setPosition(Vec2(0.0f, 0.0f));
	this->healAnimation->setPosition(Vec2(0.0f, -96.0f));
}

void LifeStone::initializeListeners()
{
	super::initializeListeners();
}

void LifeStone::onInteract()
{
	super::onInteract();

	this->runHealAnimation();

	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
	{
		squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->setHealth(healthBehavior->getMaxHealth());
		});
	}), Squally::MapKeySqually);
}

void LifeStone::onEndCollision()
{
	this->isAnimating = false;
}

void LifeStone::runHealAnimation(bool reRun)
{
	if (this->isAnimating && !reRun)
	{
		return;
	}

	if (!reRun)
	{
		this->healSound->play();
	}

	this->isAnimating = true;
	
	this->healAnimation->playAnimation(FXResources::Heal_Heal_0000, 0.05f, false, [=]()
	{
		if (this->isAnimating)
		{
			this->runHealAnimation(true);
		}
	});
}
