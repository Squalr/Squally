#include "ThrownWeapon.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/ThrownWeapon/ThrownWeaponGenericPreview.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"

using namespace cocos2d;

ThrownWeapon* ThrownWeapon::create(PlatformerEntity* caster, std::string weaponResource, int damage)
{
	ThrownWeapon* instance = new ThrownWeapon(caster, weaponResource, damage);

	instance->autorelease();

	return instance;
}

ThrownWeapon::ThrownWeapon(PlatformerEntity* caster, std::string weaponResource, int damage) : Projectile(caster, 256.0f, 1.0f, true)
{
	this->damage = -std::abs(damage);
	this->weaponResource = weaponResource;
	this->weaponSprite = Sprite::create(weaponResource);
	this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);

	this->contentNode->addChild(this->weaponSprite);
	this->contentNode->addChild(this->fire);
}

ThrownWeapon::~ThrownWeapon()
{
}

void ThrownWeapon::onEnter()
{
	super::onEnter();

	this->fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.005f);
}

void ThrownWeapon::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 56.0f));
}

void ThrownWeapon::onCollideWithTarget(PlatformerEntity* target)
{
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(this->caster, target, this->damage));
}

cocos2d::Vec2 ThrownWeapon::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ThrownWeapon::createDefaultPreview()
{
	return ThrownWeaponGenericPreview::create(this->weaponResource);
}

HackablePreview* ThrownWeapon::createVelocityPreview()
{
	return ThrownWeaponGenericPreview::create(this->weaponResource);
}

HackablePreview* ThrownWeapon::createAccelerationPreview()
{
	return ThrownWeaponGenericPreview::create(this->weaponResource);
}
