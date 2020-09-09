#pragma once
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Hackables/HackableObject.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Utils/AlgoUtils.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class TextureObject;

class MiniMapTerrainObject : public HackableObject
{
public:
	static const std::string MapKey;
	static const std::string PropertyTopOnly;
	static const std::string PropertyMiniMapHidden;
	static const std::string TagMiniMapTerrain;

protected:
	MiniMapTerrainObject(cocos2d::ValueMap& properties, TerrainObject::TerrainData terrainData);
	virtual ~MiniMapTerrainObject();

	void onEnter() override;

private:
	typedef HackableObject super;

	void setPoints(std::vector<cocos2d::Vec2> points);
	void buildInfill(TerrainObject::InfillData infillData);

	TerrainObject::TerrainData terrainData;
	std::vector<cocos2d::Vec2> points;
	std::vector<AlgoUtils::Triangle> infillTriangles;

	cocos2d::Node* rootNode;
	cocos2d::Node* infillNode;

	bool isInactive;
	bool isMiniMapHidden;
};
