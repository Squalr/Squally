#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Objects.h"
#include "Objects/SerializableLayer.h"

using namespace cocos2d;

class LevelMap : public Node
{
public:
	static LevelMap* create(std::string initLevelMapFileName, Size initMapSize);

	void insertStaticLayer(SerializableLayer* node, bool hackerModeHidden);
	void insertDynamicLayer(SerializableLayer* node, bool hackerModeHidden);

	void setPosition(const Vec2& position) override;
	Size getMapSize();
	void hackerModeEnable();
	void hackerModeDisable();
	std::string getMapFileName();

protected:
	LevelMap(std::string initLevelMapFileName, Size initMapSize);
	~LevelMap();

private:

	std::string levelMapFileName;
	Size mapSize;

	std::vector<SerializableLayer*>* staticMembers;
	std::vector<SerializableLayer*>* dynamicMembers;
	std::vector<SerializableLayer*>* hackerModeHiddenMembers;
};
