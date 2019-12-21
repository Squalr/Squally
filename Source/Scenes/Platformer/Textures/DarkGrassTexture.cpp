#include "DarkGrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DarkGrassTexture::MapKeyTextureType = "dark-grass";

DarkGrassTexture* DarkGrassTexture::create(ValueMap& properties)
{
	DarkGrassTexture* instance = new DarkGrassTexture(properties);

	instance->autorelease();

	return instance;
}

DarkGrassTexture::DarkGrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		DarkGrassTexture::MapKeyTextureType,
		TextureResources::DarkGrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

DarkGrassTexture::~DarkGrassTexture()
{
}
