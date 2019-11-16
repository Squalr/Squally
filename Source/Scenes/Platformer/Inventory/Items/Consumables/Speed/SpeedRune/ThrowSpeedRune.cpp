#include "ThrowSpeedRune.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedRune/ProjectileSpeedRune.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

ThrowSpeedRune* ThrowSpeedRune::create()
{
	ThrowSpeedRune* instance = new ThrowSpeedRune();

	instance->autorelease();

	return instance;
}

ThrowSpeedRune::ThrowSpeedRune() : super(AttackType::ProjectileBuffSpeed, ObjectResources::Items_Consumables_Runes_YELLOW_RUNE, 0.5f, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = Sound::create(SoundResources::Platformer_Combat_Attacks_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowSpeedRune::~ThrowSpeedRune()
{
}

PlatformerAttack* ThrowSpeedRune::cloneInternal()
{
	return ThrowSpeedRune::create();
}

LocalizedString* ThrowSpeedRune::getString()
{
	return Strings::Common_Empty::create();
}

std::string ThrowSpeedRune::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowSpeedRune::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowSpeedRune::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);
	
	ProjectileSpeedRune* rune = ProjectileSpeedRune::create(owner);

	this->replaceOffhandWithProjectile(owner, rune);

	rune->launchTowardsTarget(owner, Vec2(0.0f, owner->getEntitySize().height / 2.0f) + Vec2(0.0f, 256.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f));
}

void ThrowSpeedRune::onCleanup()
{
}
