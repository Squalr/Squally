#include "DartTripodLauncherSqualr.h"

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
#include "Events/SqualrEvents.h"
#include "Objects/Platformer/Projectiles/Dart/Dart.h"
#include "Objects/Platformer/Projectiles/ProjectilePool.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DartTripodLauncherSqualr::MapKey = "dart-tripod-launcher-squalr";

DartTripodLauncherSqualr* DartTripodLauncherSqualr::create(ValueMap& properties)
{
	DartTripodLauncherSqualr* instance = new DartTripodLauncherSqualr(properties);

	instance->autorelease();

	return instance;
}

DartTripodLauncherSqualr::DartTripodLauncherSqualr(ValueMap& properties) : super(properties, ObjectResources::Traps_DartTripodLauncher_Animations, 4)
{
	this->setAutoLaunch(false);
	this->toggleHackable(false);
}

DartTripodLauncherSqualr::~DartTripodLauncherSqualr()
{
}

void DartTripodLauncherSqualr::initializePositions()
{
	super::initializePositions();

	this->projectilePool->setPosition(Vec2(0.0f, 112.0f));
}

Projectile* DartTripodLauncherSqualr::createProjectile()
{
	Dart* dart = Dart::create(this->currentAngle, this->launchSpeed);
	
	dart->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionObject::CollisionData collisionData)
	{
		dart->disable(false);
		dart->runImpactFX();

		SqualrEvents::TriggerDartCollided();

		return CollisionObject::CollisionResult::DoNothing;
	});

	return dart;
}
