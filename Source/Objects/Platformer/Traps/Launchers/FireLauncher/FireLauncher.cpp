#include "FireLauncher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Combat/Projectiles/Fireball/Fireball.h"
#include "Objects/Platformer/Projectiles/ProjectilePool.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireLauncher::MapKey = "fire-launcher";

FireLauncher* FireLauncher::create(ValueMap& properties)
{
	FireLauncher* instance = new FireLauncher(properties);

	instance->autorelease();

	return instance;
}

FireLauncher::FireLauncher(ValueMap& properties) : super(properties, ObjectResources::Traps_FireLauncher_Animations, 2)
{
}

FireLauncher::~FireLauncher()
{
}

void FireLauncher::initializePositions()
{
	super::initializePositions();

	this->projectilePool->setPosition(Vec2(0.0f, 112.0f));
}

Vec2 FireLauncher::getProjectileSpawnPosition()
{
	return Vec2(0.0f, 0.0f);
}

Projectile* FireLauncher::createProjectile()
{
	Fireball* fireball = Fireball::create(nullptr, nullptr);
	
	fireball->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionData collisionData)
	{
		fireball->disable(true);
		fireball->runImpactFX();

		return CollisionResult::DoNothing;
	});

	return fireball;
}
	