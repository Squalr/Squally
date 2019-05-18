#include "CaveTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CaveTerrainDeserializer::MapKeyTerrainTypeCave = "cave";
CaveTerrainDeserializer* CaveTerrainDeserializer::instance = nullptr;

void CaveTerrainDeserializer::registerGlobalNode()
{
	if (CaveTerrainDeserializer::instance == nullptr)
	{
		CaveTerrainDeserializer::instance = new CaveTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CaveTerrainDeserializer::instance);
	}
}

CaveTerrainDeserializer::CaveTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		CaveTerrainDeserializer::MapKeyTerrainTypeCave,
		TerrainResources::Cave_CaveTexture,
		TerrainResources::Cave_Cave,
		TerrainResources::Cave_CaveTopLeft,
		TerrainResources::Cave_CaveTopRight,
		TerrainResources::Cave_CaveBottom,
		TerrainResources::Cave_CaveBottomLeft,
		TerrainResources::Cave_CaveBottomRight,
		TerrainResources::Cave_CaveLeft,
		TerrainResources::Cave_CaveRight,
		Color4B(11, 30, 39, 255)))
{
}

CaveTerrainDeserializer::~CaveTerrainDeserializer()
{
}
