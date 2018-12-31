#include "Shiftman.h"

#include "Engine/Animations/SmartAnimationNode.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string Shiftman::KeyShiftmanProperty = "shiftman";

Shiftman* Shiftman::deserialize(ValueMap* initProperties)
{
	Shiftman* instance = new Shiftman(initProperties);

	instance->autorelease();

	return instance;
}

Shiftman::Shiftman(ValueMap* initProperties) : super::IsometricEntity(initProperties,
	"", //// EntityResources::Isometric_Shiftman_Animations,
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->registerHackables();

	this->animationNode->playAnimation("Idle_SE");
}

Shiftman::~Shiftman()
{
}

void Shiftman::onEnter()
{
	super::onEnter();
}

void Shiftman::registerHackables()
{
}

Vec2 Shiftman::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void Shiftman::update(float dt)
{
	super::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;
}
