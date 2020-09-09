#include "CavernsTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/CavernsTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CavernsTerrain::MapKey = "caverns";
const Color4B CavernsTerrain::FillColor = Color4B(14, 5, 2, 255);
const Color4B CavernsTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

CavernsTerrain* CavernsTerrain::create(ValueMap& properties)
{
	CavernsTerrain* instance = new CavernsTerrain(properties);

	instance->autorelease();

	return instance;
}

CavernsTerrain::CavernsTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return CavernsTexture::create(transformedProps);
		},
		0.5f,
		CavernsTerrain::MapKey,
		TextureResources::CavernsTexture,
		TerrainResources::Caverns_Top,
		TerrainResources::Caverns_TopLeft,
		TerrainResources::Caverns_TopRight,
		TerrainResources::Caverns_TopConnector,
		TerrainResources::Caverns_TopConnectorConcave,
		TerrainResources::Caverns_TopConnectorConcaveDeep,
		TerrainResources::Caverns_TopConnectorConvex,
		TerrainResources::Caverns_TopConnectorConvexDeep,
		TerrainResources::Caverns_Bottom,
		TerrainResources::Caverns_BottomLeft,
		TerrainResources::Caverns_BottomRight,
		TerrainResources::Caverns_BottomConnector,
		TerrainResources::Caverns_Left,
		TerrainResources::Caverns_LeftConnector,
		TerrainResources::Caverns_Right,
		TerrainResources::Caverns_RightConnector,
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2::ZERO,
		// TopRight
		Vec2::ZERO,
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		// TopConnector
		Vec2::ZERO,
		// TopConnectorConcave
		Vec2(0.0f, 4.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, -2.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -14.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(CavernsTerrain::FillColor, false, true)))
{
}

CavernsTerrain::~CavernsTerrain()
{
}
