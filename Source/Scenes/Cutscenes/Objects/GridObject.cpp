#include "GridObject.h"

using namespace cocos2d;

GridObject* GridObject::create(cocos2d::Node* inner, Vec2 spawnCoords, bool isObjectStatic)
{
	GridObject* instance = new GridObject(inner, spawnCoords, isObjectStatic);

	instance->autorelease();

	return instance;
}

GridObject::GridObject(cocos2d::Node* inner, Vec2 spawnCoords, bool isObjectStatic)
{
	this->initCoords = spawnCoords;
	this->isStatic = isObjectStatic;
	this->gridCoords = this->initCoords;

	inner->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setCascadeOpacityEnabled(true);
	
	this->addChild(inner);
}

GridObject::~GridObject()
{
}

void GridObject::onEnter()
{
	SmartNode::onEnter();
}

void GridObject::setCoords(Vec2 coords)
{
	if (this->isStatic)
	{
		return;
	}

	this->gridCoords = coords;
}

Vec2 GridObject::getCoords()
{
	return this->gridCoords;
}

Vec2 GridObject::getSpawnCoords()
{
	return this->initCoords;
}
