#include "PhysicsLayer.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string PhysicsLayer::MapKeyGravity = "gravity";
const float PhysicsLayer::DefaultGravity = 2048.0f;
const float PhysicsLayer::MinimumGravity = 1024.0f;
const float PhysicsLayer::MaximumGravity = 4096.0f;

PhysicsLayer* PhysicsLayer::create(ValueMap& properties, std::string name)
{
	PhysicsLayer* instance = new PhysicsLayer(properties, name);

	instance->autorelease();

	return instance;
}

PhysicsLayer::PhysicsLayer(ValueMap& properties, std::string name) : SerializableLayer(properties, name)
{
	// Parse gravity, fixing any bad input (force negative gravity values, bound between min and max)
	float parsedGravity = GameUtils::getKeyOrDefault(properties, PhysicsLayer::MapKeyGravity, Value(PhysicsLayer::DefaultGravity)).asFloat();
	this->gravity = -MathUtils::clamp(std::abs(parsedGravity), PhysicsLayer::MinimumGravity, PhysicsLayer::MaximumGravity);
}

PhysicsLayer::~PhysicsLayer()
{
}

void PhysicsLayer::onEnter()
{
	super::onEnter();

	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, this->gravity));
}
