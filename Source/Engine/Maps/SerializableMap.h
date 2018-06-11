#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Objects.h"
#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class SerializableMap : public Node
{
public:
	static SerializableMap* deserialize(std::string initLevelMapFileName, Size initMapSize);

	void insertLayer(SerializableLayer* layer);

	Size getMapSize();
	void hackerModeEnable();
	void hackerModeDisable();
	std::string getMapFileName();

protected:
	SerializableMap(std::string initLevelMapFileName, Size initMapSize);
	~SerializableMap();

private:

	std::string levelMapFileName;
	Size mapSize;

	std::vector<SerializableLayer*>* serializableLayers;
};
