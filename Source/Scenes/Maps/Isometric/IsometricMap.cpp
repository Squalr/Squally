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

	GameCamera::getInstance()->setScrollOffset(Vec2(64.0f, 32.0f));
	GameCamera::getInstance()->setFollowSpeed(Vec2(0.075f, 0.075f));
	GameCamera::getInstance()->setTarget(IsometricSqually::getInstance());

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
