#include "ObsideanTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ObsideanTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ObsideanTerrain::MapKey = "obsidean";
const Color4B ObsideanTerrain::FillColor = Color4B(87, 15, 22, 255);
const Color4B ObsideanTerrain::MiniMapColor = Color4B(87, 15, 22, 255);

ObsideanTerrain* ObsideanTerrain::create(ValueMap& properties)
{
	ObsideanTerrain* instance = new ObsideanTerrain(properties);

	instance->autorelease();

	return instance;
}

ObsideanTerrain::ObsideanTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ObsideanTexture::create(transformedProps);
		},
		0.5f,
		ObsideanTerrain::MapKey,
		TextureResources::ObsideanTexture,
		TerrainResources::Obsidean_Top,
		TerrainResources::Obsidean_TopLeft,
		TerrainResources::Obsidean_TopRight,
		TerrainResources::Obsidean_TopConnector,
		TerrainResources::Obsidean_TopConnectorConcave,
		TerrainResources::Obsidean_TopConnectorConcaveDeep,
		TerrainResources::Obsidean_TopConnectorConvex,
		TerrainResources::Obsidean_TopConnectorConvexDeep,
		TerrainResources::Obsidean_Bottom,
		TerrainResources::Obsidean_BottomLeft,
		TerrainResources::Obsidean_BottomRight,
		TerrainResources::Obsidean_BottomConnector,
		TerrainResources::Obsidean_Left,
		TerrainResources::Obsidean_LeftConnector,
		TerrainResources::Obsidean_Right,
		TerrainResources::Obsidean_RightConnector,
		// Top
		Vec2(0.0f, -16.0f),
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(-20.0f, 0.0f),
		// TopRight
		Vec2(20.0f, 2.0f),
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		// TopConnector
		Vec2(0.0f, 16.0f),
		// TopConnectorConcave
		Vec2(0.0f, 16.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, 8.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -12.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(ObsideanTerrain::FillColor, false, true)))
{
}

ObsideanTerrain::~ObsideanTerrain()
{
}
