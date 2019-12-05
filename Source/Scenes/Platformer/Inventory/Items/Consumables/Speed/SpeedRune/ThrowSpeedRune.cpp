#include "ThrowSpeedRune.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedRune/SpeedGain.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

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

	ThrownObject* rune = ThrownObject::create(owner, ObjectResources::Items_Consumables_Runes_YELLOW_RUNE);
	
	rune->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			entity->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
			{
				// entityBuffBehavior->applyBuff(SpeedGain::create(owner, entity, healing));
			});
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->replaceOffhandWithProjectile(owner, rune);

	rune->launchTowardsTarget(owner, Vec2(0.0f, owner->getEntitySize().height / 2.0f) + Vec2(0.0f, 256.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f));
}

void ThrowSpeedRune::onCleanup()
{
}
