#include "FrostTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/FrostTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string FrostTerrain::MapKey = "frost";

FrostTerrain* FrostTerrain::create(ValueMap& properties)
{
	FrostTerrain* instance = new FrostTerrain(properties);

	instance->autorelease();

	return instance;
}

FrostTerrain::FrostTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap& properties) { return FrostTexture::create(this->transformPropertiesForTexture(properties)); },
		0.5f,
		FrostTerrain::MapKey,
		TextureResources::FrostTexture,
		TerrainResources::Frost_Top,
		TerrainResources::Frost_TopLeft,
		TerrainResources::Frost_TopRight,
		TerrainResources::Frost_TopConnector,
		TerrainResources::Frost_TopConnectorConcave,
		TerrainResources::Frost_TopConnectorConcaveDeep,
		TerrainResources::Frost_TopConnectorConvex,
		TerrainResources::Frost_TopConnectorConvexDeep,
		TerrainResources::Frost_Bottom,
		TerrainResources::Frost_BottomLeft,
		TerrainResources::Frost_BottomRight,
		TerrainResources::Frost_BottomConnector,
		TerrainResources::Frost_Left,
		TerrainResources::Frost_LeftConnector,
		TerrainResources::Frost_Right,
		TerrainResources::Frost_RightConnector,
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
		Color4B(11, 30, 39, 255)))
{
}

FrostTerrain::~FrostTerrain()
{
}
