#include "EnemyOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

EnemyOutOfCombatAttackBehavior::EnemyOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->enemy = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->enemy == nullptr)
	{
		this->invalidate();
	}
}

EnemyOutOfCombatAttackBehavior::~EnemyOutOfCombatAttackBehavior()
{
}

void EnemyOutOfCombatAttackBehavior::onEnter()
{
	super::onEnter();
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void EnemyOutOfCombatAttackBehavior::decorateProjectile(Projectile* projectile)
{
	super::decorateProjectile(projectile);

	if (projectile == nullptr)
	{
		return;
	}
	
	projectile->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Helper }, [=](CollisionData collisionData)
	{
		if (!this->enemy->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionResult::DoNothing;
		}

		PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other);

		if (this->squally != nullptr && this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true)
			&& entity != nullptr && entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			// Encountered enemy w/o first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->enemy, false));

			projectile->runImpactFX();
		}

		return CollisionResult::DoNothing;
	});
}
