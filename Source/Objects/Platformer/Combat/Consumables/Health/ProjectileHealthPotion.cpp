#include "ProjectileHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileHealthPotionGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float ProjectileHealthPotion::HealPercentage = 0.4f;

ProjectileHealthPotion* ProjectileHealthPotion::create(PlatformerEntity* caster)
{
	ProjectileHealthPotion* instance = new ProjectileHealthPotion(caster);

	instance->autorelease();

	return instance;
}

ProjectileHealthPotion::ProjectileHealthPotion(PlatformerEntity* caster) : Projectile(caster, 256.0f, 1.0f, false)
{
	this->healthPotionSprite = Sprite::create(ObjectResources::Items_Consumables_Potions_HEALTH_2);

	this->contentNode->addChild(this->healthPotionSprite);
}

ProjectileHealthPotion::~ProjectileHealthPotion()
{
}

void ProjectileHealthPotion::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ProjectileHealthPotion::initializePositions()
{
	super::initializePositions();
}

void ProjectileHealthPotion::update(float dt)
{
	super::update(dt);
}

void ProjectileHealthPotion::onCollideWithTarget(PlatformerEntity* target)
{
	if (target == nullptr)
	{
		return;
	}

	int healing = std::round(float(target->getStateOrDefaultInt(StateKeys::Health, 0))) * ProjectileHealthPotion::HealPercentage;

	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(this->caster, target, healing));
}

cocos2d::Vec2 ProjectileHealthPotion::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ProjectileHealthPotion::createDefaultPreview()
{
	return ProjectileHealthPotionGenericPreview::create();
}

HackablePreview* ProjectileHealthPotion::createVelocityPreview()
{
	return ProjectileHealthPotionGenericPreview::create();
}

HackablePreview* ProjectileHealthPotion::createAccelerationPreview()
{
	return ProjectileHealthPotionGenericPreview::create();
}
