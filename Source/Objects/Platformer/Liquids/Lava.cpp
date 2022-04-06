#include "Lava.h"

#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/Liquid/LiquidNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Lava::MapKey = "lava";
const Color4B Lava::SurfaceColor = Color4B(224, 224, 0, 255);
const Color4B Lava::BodyColor = Color4B(212, 12, 12, 224);
const float Lava::LavaGravity = 0.0f;

Lava* Lava::create(ValueMap& properties)
{
	Lava* instance = new Lava(properties);

	instance->autorelease();

	return instance;
}

Lava::Lava(ValueMap& properties) : super(properties, 8.0f, (CollisionType)PlatformerCollisionType::KillPlane, Lava::SurfaceColor, Lava::BodyColor, 0.025f, 0.015f, 0.15f)
{
}

Lava::~Lava()
{
}

void Lava::initializeListeners()
{
	super::initializeListeners();

	this->liquidCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->runObjectSplash(collisionData.other, false);

		return CollisionResult::DoNothing;
	});

	this->liquidCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->runObjectSplash(collisionData.other, true);

		return CollisionResult::DoNothing;
	});

	this->liquidCollision->whileCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->applyLavaForce(collisionData.other, collisionData.dt);

		return CollisionResult::DoNothing;
	});
}

void Lava::applyLavaForce(CollisionObject* target, float dt)
{
	target->setVelocity(target->getVelocity() + Vec2(0.0f, Lava::LavaGravity * dt));
}
