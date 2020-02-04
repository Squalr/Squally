#include "FireLauncherSqualr.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/SqualrEvents.h"
#include "Objects/Platformer/Projectiles/Fireball/Fireball.h"
#include "Objects/Platformer/Projectiles/ProjectilePool.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireLauncherSqualr::MapKeyFireLauncherSqualr = "fire-launcher-squalr";

FireLauncherSqualr* FireLauncherSqualr::create(ValueMap& properties)
{
	FireLauncherSqualr* instance = new FireLauncherSqualr(properties);

	instance->autorelease();

	return instance;
}

FireLauncherSqualr::FireLauncherSqualr(ValueMap& properties) : super(properties, ObjectResources::Traps_FireLauncher_Animations)
{
	this->setAutoLaunch(false);
}

FireLauncherSqualr::~FireLauncherSqualr()
{
}

void FireLauncherSqualr::initializePositions()
{
	super::initializePositions();

	this->projectilePool->setPosition(Vec2(0.0f, 112.0f));
}

Projectile* FireLauncherSqualr::createProjectile()
{
	Fireball* fireball = Fireball::create(nullptr);
	
	fireball->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionObject::CollisionData collisionData)
	{
		fireball->disable(false);
		fireball->runImpactFX();

		SqualrEvents::TriggerFireballCollided();

		return CollisionObject::CollisionResult::DoNothing;
	});

	return fireball;
}
