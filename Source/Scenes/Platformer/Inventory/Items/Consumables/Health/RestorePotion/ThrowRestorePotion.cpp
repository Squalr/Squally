#include "ThrowRestorePotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/ProjectileRestorePotion.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

ThrowRestorePotion* ThrowRestorePotion::create()
{
	ThrowRestorePotion* instance = new ThrowRestorePotion();

	instance->autorelease();

	return instance;
}

ThrowRestorePotion::ThrowRestorePotion() : super(AttackType::ProjectileHealing, ObjectResources::Items_Consumables_Potions_HEALTH_2, 0.5f, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Attacks_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowRestorePotion::~ThrowRestorePotion()
{
}

PlatformerAttack* ThrowRestorePotion::cloneInternal()
{
	return ThrowRestorePotion::create();
}

LocalizedString* ThrowRestorePotion::getString()
{
	return Strings::Common_Empty::create();
}

std::string ThrowRestorePotion::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowRestorePotion::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowRestorePotion::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	ProjectileRestorePotion* potion = ProjectileRestorePotion::create(owner);

	this->replaceOffhandWithProjectile(owner, potion);

	potion->launchTowardsTarget(owner, Vec2(0.0f, owner->getEntitySize().height / 2.0f) + Vec2(0.0f, 256.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f));
}

void ThrowRestorePotion::onCleanup()
{
}
