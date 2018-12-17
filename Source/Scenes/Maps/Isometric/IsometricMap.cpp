#include "IsometricMap.h"

IsometricMap* IsometricMap::create()
{
	IsometricMap* instance = new IsometricMap();

	instance->autorelease();

	return instance;
}

IsometricMap::IsometricMap()
{
	if (!MapBase::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));
}

IsometricMap::~IsometricMap()
{
}

void IsometricMap::onEnter()
{
	MapBase::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(IsometricSqually::getInstance(), Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData);

	this->scheduleUpdate();
}

void IsometricMap::initializePositions()
{
	MapBase::initializePositions();
}

void IsometricMap::initializeListeners()
{
	MapBase::initializeListeners();
}
