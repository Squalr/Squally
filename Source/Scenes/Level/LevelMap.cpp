#include "LevelMap.h"

LevelMap* LevelMap::create(std::string initLevelMapFileName, Size initMapSize)
{
	LevelMap* levelMap = new LevelMap(initLevelMapFileName, initMapSize);

	levelMap->autorelease();

	return levelMap;
}

LevelMap::LevelMap(std::string initLevelMapFileName, Size initMapSize)
{
	this->levelMapFileName = initLevelMapFileName;
	this->mapSize = initMapSize;
	this->hackerModeHiddenMembers = new std::vector<SerializableLayer*>();
	this->staticMembers = new std::vector<SerializableLayer*>();
	this->dynamicMembers = new std::vector<SerializableLayer*>();
}

LevelMap::~LevelMap()
{
	delete(this->hackerModeHiddenMembers);
	delete(this->staticMembers);
	delete(this->dynamicMembers);
}

std::string LevelMap::getMapFileName()
{
	return this->levelMapFileName;
}

void LevelMap::hackerModeEnable()
{
	this->setVisible(true);

	for (auto it = this->hackerModeHiddenMembers->begin(); it != this->hackerModeHiddenMembers->end(); it++)
	{
		(*it)->setVisible(false);
	}
}

void LevelMap::hackerModeDisable()
{
	this->setVisible(true);

	for (auto it = this->hackerModeHiddenMembers->begin(); it != this->hackerModeHiddenMembers->end(); it++)
	{
		(*it)->setVisible(true);
	}
}

void LevelMap::setPosition(const Vec2& position)
{
	// Override set position to only set the position of dynamic layers
	for (auto it = this->dynamicMembers->begin(); it != this->dynamicMembers->end(); it++)
	{
		(*it)->setPosition(position);
	}
}

Size LevelMap::getMapSize()
{
	return this->mapSize;
}

void LevelMap::insertStaticLayer(SerializableLayer* node, bool hackerModeHidden)
{
	if (hackerModeHidden)
	{
		this->hackerModeHiddenMembers->push_back(node);
	}

	this->staticMembers->push_back(node);
	this->addChild(node);
}

void LevelMap::insertDynamicLayer(SerializableLayer* node, bool hackerModeHidden)
{
	if (hackerModeHidden)
	{
		this->hackerModeHiddenMembers->push_back(node);
	}

	this->dynamicMembers->push_back(node);
	this->addChild(node);
}