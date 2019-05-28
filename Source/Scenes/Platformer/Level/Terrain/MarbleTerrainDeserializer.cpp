#include "MarbleTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleTerrainDeserializer::MapKeyTerrainTypeMarble = "marble";
MarbleTerrainDeserializer* MarbleTerrainDeserializer::instance = nullptr;

void MarbleTerrainDeserializer::registerGlobalNode()
{
	if (MarbleTerrainDeserializer::instance == nullptr)
	{
		MarbleTerrainDeserializer::instance = new MarbleTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MarbleTerrainDeserializer::instance);
	}
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
