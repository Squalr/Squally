#include "ProximityObject.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

ProximityObject* ProximityObject::create(float radius)
{
	ProximityObject* instance = new ProximityObject(radius);

	instance->autorelease();

	return instance;
}

ProximityObject::ProximityObject(float radius)
{
	this->radius = radius;
	this->velocity = Vec3::ZERO;
	this->acceleration = Vec3::ZERO;
}

ProximityObject::~ProximityObject()
{
}

void ProximityObject::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ProximityObject::initializePositions()
{
	super::initializePositions();
}

void ProximityObject::update(float dt)
{
	super::update(dt);

	this->velocity += this->acceleration * dt;
	this->setPosition3D(this->getPosition3D() + this->velocity * dt);
}

void ProximityObject::launchTowardsTarget(Node* target, Vec2 offset, float spinSpeed, float secondsPer256pxLinearDistance, Vec3 gravity)
{
	Vec3 thisPosition = GameUtils::getWorldCoords3D(this);
	Vec3 targetPosition = GameUtils::getWorldCoords3D(target) + Vec3(offset.x, offset.y, 0.0f);
	float duration = targetPosition.distance(thisPosition) / 480.0f * secondsPer256pxLinearDistance;
	bool isLeft = targetPosition.x < thisPosition.x;

	if (spinSpeed != 0.0f)
	{
		this->runAction(RotateBy::create(duration, (isLeft ? -1.0f : 1.0f) * duration * 360.0f * spinSpeed));
	}

	this->setAcceleration(gravity);
	this->setVelocity(AlgoUtils::computeArcVelocity(thisPosition, targetPosition, gravity, duration));
}

void ProximityObject::setVelocity(cocos2d::Vec3 velocity)
{
	this->velocity = velocity;
}

void ProximityObject::setAcceleration(cocos2d::Vec3 acceleration)
{
	this->acceleration = acceleration;
}

bool ProximityObject::isInProximityTo(Node* other)
{
	return other == nullptr ? false : (this->getPosition3D().distance(other->getPosition3D()) < this->radius);
}
