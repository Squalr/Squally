#include "Shiftman.h"

const std::string Shiftman::KeyShiftmanProperty = "shiftman";

Shiftman* Shiftman::deserialize(ValueMap* initProperties)
{
	Shiftman* instance = new Shiftman(initProperties);

	instance->autorelease();

	return instance;
}

Shiftman::Shiftman(ValueMap* initProperties) : IsometricEntity::IsometricEntity(initProperties,
	Resources::Entities_Isometric_Shiftman_Animations,
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->registerHackables();

	this->animationNodeEntity->setCurrentAnimation("Idle_SE");
}

Shiftman::~Shiftman()
{
}

void Shiftman::onEnter()
{
	IsometricEntity::onEnter();
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
	IsometricEntity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;
}
