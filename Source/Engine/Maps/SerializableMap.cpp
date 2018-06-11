#include "SerializableMap.h"

SerializableMap* SerializableMap::deserialize(std::string initLevelMapFileName, Size initMapSize)
{
	SerializableMap* instance = new SerializableMap(initLevelMapFileName, initMapSize);

	instance->autorelease();

	return instance;
}

SerializableMap::SerializableMap(std::string initLevelMapFileName, Size initMapSize)
{
	this->levelMapFileName = initLevelMapFileName;
	this->mapSize = initMapSize;
	this->serializableLayers = new std::vector<SerializableLayer*>();
}

SerializableMap::~SerializableMap()
{
	delete(this->serializableLayers);
}

std::string SerializableMap::getMapFileName()
{
	return this->levelMapFileName;
}

void SerializableMap::hackerModeEnable()
{
	this->setVisible(true);

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		(*it)->setVisible(false);
	}
}

void SerializableMap::hackerModeDisable()
{
	this->setVisible(true);

	for (auto it = this->serializableLayers->begin(); it != this->serializableLayers->end(); it++)
	{
		(*it)->setVisible(true);
	}
}

Size SerializableMap::getMapSize()
{
	return this->mapSize;
}

void SerializableMap::insertLayer(SerializableLayer* layer)
{
	this->serializableLayers->push_back(layer);
	this->addChild(layer);
}
