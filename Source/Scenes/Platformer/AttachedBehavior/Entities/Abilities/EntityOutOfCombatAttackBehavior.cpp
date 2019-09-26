#include "EntityOutOfCombatAttackBehavior.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityOutOfCombatAttackBehavior::EntityOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->outOfCombatAttackDebug = Sprite::create(UIResources::Menus_Icons_Swords);
	this->isPerformingOutOfCombatAttack = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->addChild(this->outOfCombatAttackDebug);
}

EntityOutOfCombatAttackBehavior::~EntityOutOfCombatAttackBehavior()
{
}

void EntityOutOfCombatAttackBehavior::initializePositions()
{
	super::initializePositions();

	this->outOfCombatAttackDebug->setPosition(Vec2(0.0f, this->entity->getEntitySize().height + this->entity->getHoverHeight() / 2.0f + 64.0f));
}

void EntityOutOfCombatAttackBehavior::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();
}

void EntityOutOfCombatAttackBehavior::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->outOfCombatAttackDebug->setVisible(false);
}

void EntityOutOfCombatAttackBehavior::onLoad()
{
}

void EntityOutOfCombatAttackBehavior::doOutOfCombatAttack(std::string attackAnimation, float onset, float sustain)
{
	if (this->isPerformingOutOfCombatAttack || this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	this->isPerformingOutOfCombatAttack = true;
	this->entity->getAnimations()->playAnimation(attackAnimation, SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 1.0f);
	this->entity->watchForAttachedBehavior<EntityWeaponCollisionBehavior>([=](EntityWeaponCollisionBehavior* weaponBehavior)
	{
		this->runAction(Sequence::create(
			DelayTime::create(onset),
			CallFunc::create([=]()
			{
				if (this->isDeveloperModeEnabled())
				{
					this->outOfCombatAttackDebug->setVisible(true);
				}

				weaponBehavior->enable();
			}),
			DelayTime::create(sustain),
			CallFunc::create([=]()
			{
				weaponBehavior->disable();
				this->isPerformingOutOfCombatAttack = false;
				this->outOfCombatAttackDebug->setVisible(false);
			}),
			nullptr
		));
	});
}
