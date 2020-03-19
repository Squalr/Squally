#include "LavaTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/LavaTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LavaTerrain::MapKey = "lava";

LavaTerrain* LavaTerrain::create(ValueMap& properties)
{
	LavaTerrain* instance = new LavaTerrain(properties);

	instance->autorelease();

	return instance;
}

LavaTerrain::LavaTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap& properties) { return LavaTexture::create(this->transformPropertiesForTexture(properties)); },
		0.5f,
		LavaTerrain::MapKey,
		TextureResources::LavaTexture,
		TerrainResources::Lava_Top,
		TerrainResources::Lava_TopLeft,
		TerrainResources::Lava_TopRight,
		TerrainResources::Lava_TopConnector,
		TerrainResources::Lava_TopConnectorConcave,
		TerrainResources::Lava_TopConnectorConcaveDeep,
		TerrainResources::Lava_TopConnectorConvex,
		TerrainResources::Lava_TopConnectorConvexDeep,
		TerrainResources::Lava_Bottom,
		TerrainResources::Lava_BottomLeft,
		TerrainResources::Lava_BottomRight,
		TerrainResources::Lava_BottomConnector,
		TerrainResources::Lava_Left,
		TerrainResources::Lava_LeftConnector,
		TerrainResources::Lava_Right,
		TerrainResources::Lava_RightConnector,
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

LavaTerrain::~LavaTerrain()
{
}
