#include "VoidTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/VoidTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string VoidTerrain::MapKey = "void";
const Color4B VoidTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B VoidTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

VoidTerrain* VoidTerrain::create(ValueMap& properties)
{
	VoidTerrain* instance = new VoidTerrain(properties);

	instance->autorelease();

	return instance;
}

VoidTerrain::VoidTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return VoidTexture::create(transformedProps);
		},
		0.5f,
		VoidTerrain::MapKey,
		TextureResources::VoidTexture,
		TerrainResources::Void_Top,
		TerrainResources::Void_TopLeft,
		TerrainResources::Void_TopRight,
		TerrainResources::Void_TopConnector,
		TerrainResources::Void_TopConnectorConcave,
		TerrainResources::Void_TopConnectorConcaveDeep,
		TerrainResources::Void_TopConnectorConvex,
		TerrainResources::Void_TopConnectorConvexDeep,
		TerrainResources::Void_Bottom,
		TerrainResources::Void_BottomLeft,
		TerrainResources::Void_BottomRight,
		TerrainResources::Void_BottomConnector,
		TerrainResources::Void_Left,
		TerrainResources::Void_LeftConnector,
		TerrainResources::Void_Right,
		TerrainResources::Void_RightConnector,
		// Top
		Vec2(0.0f, -24.0f),
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
		InfillData(VoidTerrain::FillColor, false, true)))
{
}

VoidTerrain::~VoidTerrain()
{
}
