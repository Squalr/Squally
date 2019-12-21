#include "ShipTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipTexture::MapKeyTextureType = "ship";

ShipTexture* ShipTexture::create(ValueMap& properties)
{
	ShipTexture* instance = new ShipTexture(properties);

	instance->autorelease();

	return instance;
}

ShipTexture::ShipTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ShipTexture::MapKeyTextureType,
		TextureResources::ShipTexture,
		Color4B(11, 30, 39, 255)))
{
}

ShipTexture::~ShipTexture()
{
}
