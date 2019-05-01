#include "GridItem.h"

using namespace cocos2d;

GridItem* GridItem::create(cocos2d::Node* inner, Vec2 spawnCoords, bool isObjectStatic)
{
	GridItem* instance = new GridItem(inner, spawnCoords, isObjectStatic);

	instance->autorelease();

	return instance;
}

GridItem::GridItem(cocos2d::Node* inner, Vec2 spawnCoords, bool isObjectStatic)
{
	this->initCoords = spawnCoords;
	this->isStatic = isObjectStatic;
	this->gridCoords = this->initCoords;

	inner->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setCascadeOpacityEnabled(true);
	
	this->addChild(inner);
}

GridItem::~GridItem()
{
}

void GridItem::onEnter()
{
	SmartNode::onEnter();
}

void GridItem::setCoords(Vec2 coords)
{
	if (this->isStatic)
	{
		return;
	}

	this->gridCoords = coords;
}

Vec2 GridItem::getCoords()
{
	return this->gridCoords;
}

Vec2 GridItem::getSpawnCoords()
{
	return this->initCoords;
}
