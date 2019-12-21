#include "ShipAltTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipAltTexture::MapKeyTextureType = "ship-alt";

ShipAltTexture* ShipAltTexture::create(ValueMap& properties)
{
	ShipAltTexture* instance = new ShipAltTexture(properties);

	instance->autorelease();

	return instance;
}

ShipAltTexture::ShipAltTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ShipAltTexture::MapKeyTextureType,
		TextureResources::ShipAltTexture,
		Color4B(11, 30, 39, 255)))
{
}

ShipAltTexture::~ShipAltTexture()
{
}
