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
#include "Scenes/Platformer/Level/Combat/Buffs/RestoreHealth/RestoreHealth.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float ProjectileRestorePotion::HealPercentage = 0.6f;

ProjectileRestorePotion* ProjectileRestorePotion::create(PlatformerEntity* caster)
{
	ProjectileRestorePotion* instance = new ProjectileRestorePotion(caster);

	instance->autorelease();

	return instance;
}

ProjectileRestorePotion::ProjectileRestorePotion(PlatformerEntity* caster) : Projectile(caster, 256.0f, 1.0f, false)
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
	int healing = std::round(float(target->getMaxHealth()) * ProjectileRestorePotion::HealPercentage);
	
	target->addChild(RestoreHealth::create(this->caster, target, healing));
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
