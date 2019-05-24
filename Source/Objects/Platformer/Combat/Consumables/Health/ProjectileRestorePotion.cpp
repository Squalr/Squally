#include "ProjectileRestorePotion.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileRestorePotionGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float ProjectileRestorePotion::HealPercentage = 0.4f;

ProjectileRestorePotion* ProjectileRestorePotion::create()
{
	ProjectileRestorePotion* instance = new ProjectileRestorePotion();

	instance->autorelease();

	return instance;
}

ProjectileRestorePotion::ProjectileRestorePotion() : Projectile(256.0f, 1.0f)
{
	this->restorePotionSprite = Sprite::create(ObjectResources::Items_Consumables_HEALTH_2);

	this->contentNode->addChild(this->restorePotionSprite);
}

ProjectileRestorePotion::~ProjectileRestorePotion()
{
}

void ProjectileRestorePotion::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ProjectileRestorePotion::initializePositions()
{
	super::initializePositions();
}

void ProjectileRestorePotion::update(float dt)
{
	super::update(dt);
}

void ProjectileRestorePotion::onCollideWithTarget(PlatformerEntity* target)
{
	const float DelayBetweenTicks = 0.5f;

	int healing = float(target->getMaxHealth()) * ProjectileRestorePotion::HealPercentage;
	
	for (int healIndex = 0; healIndex < healing; healIndex++)
	{
		this->runAction(Sequence::create(
			DelayTime::create(DelayBetweenTicks * float(healIndex)),
			CallFunc::create([=]()
			{
				this->doHealTick(target);
			}),
			nullptr
		));
	}
}

cocos2d::Vec2 ProjectileRestorePotion::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ProjectileRestorePotion::createDefaultPreview()
{
	return ProjectileRestorePotionGenericPreview::create();
}

HackablePreview* ProjectileRestorePotion::createVelocityPreview()
{
	return ProjectileRestorePotionGenericPreview::create();
}

HackablePreview* ProjectileRestorePotion::createAccelerationPreview()
{
	return ProjectileRestorePotionGenericPreview::create();
}

void ProjectileRestorePotion::doHealTick(PlatformerEntity* target)
{
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(1, target));
}
