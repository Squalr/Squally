#include "OutOfCombatAttackBehaviorBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

OutOfCombatAttackBehaviorBase::OutOfCombatAttackBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->isPerformingOutOfCombatAttack = false;
	
	this->outOfCombatAttackDebug = Sprite::create(UIResources::Menus_Icons_Swords);

	this->addChild(this->outOfCombatAttackDebug);
}

OutOfCombatAttackBehaviorBase::~OutOfCombatAttackBehaviorBase()
{
}

void OutOfCombatAttackBehaviorBase::initializePositions()
{
	super::initializePositions();

	this->outOfCombatAttackDebug->setPosition(Vec2(0.0f, this->entity->getEntitySize().height + this->entity->hoverHeight / 2.0f + 64.0f));
}


void OutOfCombatAttackBehaviorBase::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();
}

void OutOfCombatAttackBehaviorBase::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->outOfCombatAttackDebug->setVisible(false);
}

void OutOfCombatAttackBehaviorBase::onLoad()
{
}

void OutOfCombatAttackBehaviorBase::doOutOfCombatAttack(std::string attackAnimation, float onset, float sustain)
{
	if (this->isPerformingOutOfCombatAttack)
	{
		return;
	}

	this->isPerformingOutOfCombatAttack = true;
	this->entity->animationNode->playAnimation(attackAnimation);

	this->runAction(Sequence::create(
		DelayTime::create(onset),
		CallFunc::create([=]()
		{
			if (this->isDeveloperModeEnabled())
			{
				this->outOfCombatAttackDebug->setVisible(true);
			}

			this->entity->weaponCollision->setPhysicsEnabled(true);
		}),
		DelayTime::create(sustain),
		CallFunc::create([=]()
		{
			this->entity->weaponCollision->setPhysicsEnabled(false);
			this->isPerformingOutOfCombatAttack = false;
			this->outOfCombatAttackDebug->setVisible(false);
		}),
		nullptr
	));
}
