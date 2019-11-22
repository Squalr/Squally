#include "WoodTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string WoodTexture::MapKeyTextureType = "wood";

WoodTexture* WoodTexture::create(ValueMap& properties)
{
	WoodTexture* instance = new WoodTexture(properties);

	instance->autorelease();

	return instance;
}

WoodTexture::WoodTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		WoodTexture::MapKeyTextureType,
		TextureResources::WoodTexture,
		Color4B(11, 30, 39, 255)))
{
}

WoodTexture::~WoodTexture()
{
}
