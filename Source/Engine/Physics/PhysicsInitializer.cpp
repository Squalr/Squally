#include "PhysicsInitializer.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string PhysicsInitializer::MapKeyPhysicsInitializer = "meta";
const std::string PhysicsInitializer::MapKeyGravity = "gravity";
const float PhysicsInitializer::DefaultGravity = 768.0f;
const float PhysicsInitializer::MinimumGravity = 1024.0f;
const float PhysicsInitializer::MaximumGravity = 4096.0f;

PhysicsInitializer* PhysicsInitializer::create(ValueMap& properties)
{
	PhysicsInitializer* instance = new PhysicsInitializer(properties);

	instance->autorelease();

	return instance;
}

PhysicsInitializer::PhysicsInitializer(ValueMap& properties) : super(properties)
{
	// Parse gravity, fixing any bad input (force negative gravity values, bound between min and max)
	float parsedGravity = GameUtils::getKeyOrDefault(properties, PhysicsInitializer::MapKeyGravity, Value(PhysicsInitializer::DefaultGravity)).asFloat();
	this->gravity = -MathUtils::clamp(std::abs(parsedGravity), PhysicsInitializer::MinimumGravity, PhysicsInitializer::MaximumGravity);
}

PhysicsInitializer::~PhysicsInitializer()
{
}

void PhysicsInitializer::onEnter()
{
	super::onEnter();
	
	/*
	PhysicsWorld* physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();

	if (physicsWorld != nullptr)
	{
		physicsWorld->setGravity(Vec2(0.0f, this->gravity));
	}*/
}
