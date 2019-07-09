#include "MarbleTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleTerrainDeserializer::MapKeyTerrainTypeMarble = "marble";

MarbleTerrainDeserializer* MarbleTerrainDeserializer::create()
{
	MarbleTerrainDeserializer* instance = new MarbleTerrainDeserializer();

	instance->autorelease();

	return instance;
}

MarbleTerrainDeserializer::MarbleTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		MarbleTerrainDeserializer::MapKeyTerrainTypeMarble,
		TerrainResources::Marble_MarbleTexture,
		TerrainResources::Marble_Marble,
		TerrainResources::Marble_MarbleTopLeft,
		TerrainResources::Marble_MarbleTopRight,
		TerrainResources::Marble_MarbleBottom,
		TerrainResources::Marble_MarbleBottomLeft,
		TerrainResources::Marble_MarbleBottomRight,
		TerrainResources::Marble_MarbleLeft,
		TerrainResources::Marble_MarbleRight,
		Color4B(11, 30, 39, 255)))
{
}

MarbleTerrainDeserializer::~MarbleTerrainDeserializer()
{
}
