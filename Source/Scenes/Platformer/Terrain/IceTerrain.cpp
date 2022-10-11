#include "IceTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/IceTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string IceTerrain::MapKey = "ice";
const Color4B IceTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B IceTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

IceTerrain* IceTerrain::create(ValueMap& properties)
{
	IceTerrain* instance = new IceTerrain(properties);

	instance->autorelease();

	return instance;
}

IceTerrain::IceTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return IceTexture::create(transformedProps);
		},
		0.5f,
		IceTerrain::MapKey,
		TextureResources::IceTexture,
		TerrainResources::Ice_Top,
		TerrainResources::Ice_TopLeft,
		TerrainResources::Ice_TopRight,
		TerrainResources::Ice_TopConnector,
		TerrainResources::Ice_TopConnectorConcave,
		TerrainResources::Ice_TopConnectorConcaveDeep,
		TerrainResources::Ice_TopConnectorConvex,
		TerrainResources::Ice_TopConnectorConvexDeep,
		TerrainResources::Ice_Bottom,
		TerrainResources::Ice_BottomLeft,
		TerrainResources::Ice_BottomRight,
		TerrainResources::Ice_BottomConnector,
		TerrainResources::Ice_Left,
		TerrainResources::Ice_LeftConnector,
		TerrainResources::Ice_Right,
		TerrainResources::Ice_RightConnector,
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
		InfillData(IceTerrain::FillColor, false, true)))
{
}

IceTerrain::~IceTerrain()
{
}
