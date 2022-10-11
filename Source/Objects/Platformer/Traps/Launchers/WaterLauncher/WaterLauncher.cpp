#include "WaterLauncher.h"

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
#include "Objects/Platformer/Combat/Projectiles/Waterball/Waterball.h"
#include "Objects/Platformer/Projectiles/ProjectilePool.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WaterLauncher::MapKey = "water-launcher";

WaterLauncher* WaterLauncher::create(ValueMap& properties)
{
	WaterLauncher* instance = new WaterLauncher(properties);

	instance->autorelease();

	return instance;
}

WaterLauncher::WaterLauncher(ValueMap& properties) : super(properties, ObjectResources::Traps_WaterLauncher_Animations, true, 2)
{
}

WaterLauncher::~WaterLauncher()
{
}

void WaterLauncher::initializePositions()
{
	super::initializePositions();

	this->projectilePool->setPosition(Vec2(0.0f, 112.0f));
}

Vec2 WaterLauncher::getProjectileSpawnPosition()
{
	return Vec2(0.0f, 0.0f);
}

Projectile* WaterLauncher::createProjectile()
{
	Waterball* waterball = Waterball::create(nullptr, nullptr);
	
	waterball->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionData collisionData)
	{
		waterball->disable(true);
		waterball->runImpactFX();

		return CollisionResult::DoNothing;
	});

	return waterball;
}
	