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
	this->hackerModeHiddenMembers = new std::vector<Node*>();
	this->staticMembers = new std::vector<Node*>();
	this->dynamicMembers = new std::vector<Node*>();
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

void LevelMap::insertStaticMember(Node* node, bool hackerModeHidden)
{
	if (hackerModeHidden)
	{
		this->hackerModeHiddenMembers->push_back(node);
	}

	this->staticMembers->push_back(node);
	this->addChild(node);
}

void LevelMap::insertDynamicMember(Node* node, bool hackerModeHidden)
{
	if (hackerModeHidden)
	{
		this->hackerModeHiddenMembers->push_back(node);
	}

	this->dynamicMembers->push_back(node);
	this->addChild(node);
}