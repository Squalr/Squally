#include "ProjectileHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileHealthPotionGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ProjectileHealthPotion* ProjectileHealthPotion::create(std::function<void(PlatformerEntity* target)> onTargetHit)
{
	ProjectileHealthPotion* instance = new ProjectileHealthPotion(onTargetHit);

	instance->autorelease();

	return instance;
}

ProjectileHealthPotion::ProjectileHealthPotion(std::function<void(PlatformerEntity* target)> onTargetHit) : Projectile(onTargetHit, 256.0f, 1.0f)
{
	this->healthPotionSprite = Sprite::create(ObjectResources::Items_Consumables_HEALTH_2);

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
