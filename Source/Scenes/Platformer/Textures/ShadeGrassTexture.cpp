#include "ShadeGrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShadeGrassTexture::MapKey = "shade-grass";

ShadeGrassTexture* ShadeGrassTexture::create(ValueMap& properties)
{
	ShadeGrassTexture* instance = new ShadeGrassTexture(properties);

	instance->autorelease();

	return instance;
}

ShadeGrassTexture::ShadeGrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ShadeGrassTexture::MapKey,
		TextureResources::ShadeGrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

ShadeGrassTexture::~ShadeGrassTexture()
{
}
