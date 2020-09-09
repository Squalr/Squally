#include "TempleGreenTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/TempleGreenTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleGreenTerrain::MapKey = "temple-green";
const Color4B TempleGreenTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B TempleGreenTerrain::MiniMapColor = Color4B(11, 30, 39, 255);


TempleGreenTerrain* TempleGreenTerrain::create(ValueMap& properties)
{
	TempleGreenTerrain* instance = new TempleGreenTerrain(properties);

	instance->autorelease();

	return instance;
}

TempleGreenTerrain::TempleGreenTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return TempleGreenTexture::create(transformedProps);
		},
		0.5f,
		TempleGreenTerrain::MapKey,
		TextureResources::TempleGreenTexture,
		TerrainResources::TempleGreen_Top,
		TerrainResources::TempleGreen_TopLeft,
		TerrainResources::TempleGreen_TopRight,
		TerrainResources::TempleGreen_TopConnector,
		TerrainResources::TempleGreen_TopConnectorConcave,
		TerrainResources::TempleGreen_TopConnectorConcaveDeep,
		TerrainResources::TempleGreen_TopConnectorConvex,
		TerrainResources::TempleGreen_TopConnectorConvexDeep,
		TerrainResources::TempleGreen_Bottom,
		TerrainResources::TempleGreen_BottomLeft,
		TerrainResources::TempleGreen_BottomRight,
		TerrainResources::TempleGreen_BottomConnector,
		TerrainResources::TempleGreen_Left,
		TerrainResources::TempleGreen_LeftConnector,
		TerrainResources::TempleGreen_Right,
		TerrainResources::TempleGreen_RightConnector,
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
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -8.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(TempleGreenTerrain::FillColor, false, true)))
{
}

TempleGreenTerrain::~TempleGreenTerrain()
{
}
