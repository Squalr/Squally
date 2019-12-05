#include "ProjectileSpeedRune.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedRune/ProjectileSpeedRuneGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float ProjectileSpeedRune::SpeedMultiplier = 2.4f;

ProjectileSpeedRune* ProjectileSpeedRune::create(PlatformerEntity* caster)
{
	ProjectileSpeedRune* instance = new ProjectileSpeedRune(caster);

	instance->autorelease();

	return instance;
}

ProjectileSpeedRune::ProjectileSpeedRune(PlatformerEntity* caster)
	: Projectile(caster, CollisionObject::createCapsulePolygon(Size(64.0f, 64.0f)), CombatCollisionType::Projectile, 1.0f, false)
{
	this->speedRuneSprite = Sprite::create(ObjectResources::Items_Consumables_Runes_YELLOW_RUNE);

	this->contentNode->addChild(this->speedRuneSprite);
}

ProjectileSpeedRune::~ProjectileSpeedRune()
{
}

void ProjectileSpeedRune::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ProjectileSpeedRune::initializePositions()
{
	super::initializePositions();
}

void ProjectileSpeedRune::update(float dt)
{
	super::update(dt);
}

void ProjectileSpeedRune::onCollideWithTarget(PlatformerEntity* target)
{
	// CombatEvents::TriggerSpeedGain(CombatEvents::SpeedGainArgs(this->caster, target, ProjectileSpeedRune::SpeedMultiplier));
}

cocos2d::Vec2 ProjectileSpeedRune::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ProjectileSpeedRune::createDefaultPreview()
{
	return ProjectileSpeedRuneGenericPreview::create();
}

HackablePreview* ProjectileSpeedRune::createVelocityPreview()
{
	return ProjectileSpeedRuneGenericPreview::create();
}

HackablePreview* ProjectileSpeedRune::createAccelerationPreview()
{
	return ProjectileSpeedRuneGenericPreview::create();
}
