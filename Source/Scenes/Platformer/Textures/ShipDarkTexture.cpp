#include "ShipDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipDarkTexture::MapKey = "ship-dark";

ShipDarkTexture* ShipDarkTexture::create(ValueMap& properties)
{
	ShipDarkTexture* instance = new ShipDarkTexture(properties);

	instance->autorelease();

	return instance;
}

ShipDarkTexture::ShipDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ShipDarkTexture::MapKey,
		TextureResources::ShipDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

ShipDarkTexture::~ShipDarkTexture()
{
}
