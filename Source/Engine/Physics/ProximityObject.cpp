#include "ProximityObject.h"

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
}

bool ProximityObject::isInProximityTo(Node* other)
{
	return other == nullptr ? false : (this->getPosition3D().distance(other->getPosition3D()) < this->radius);
}
