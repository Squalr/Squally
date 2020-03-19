#include "BlueGrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string BlueGrassTexture::MapKey = "blue-grass";

BlueGrassTexture* BlueGrassTexture::create(ValueMap& properties)
{
	BlueGrassTexture* instance = new BlueGrassTexture(properties);

	instance->autorelease();

	return instance;
}

BlueGrassTexture::BlueGrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		BlueGrassTexture::MapKey,
		TextureResources::BlueGrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

BlueGrassTexture::~BlueGrassTexture()
{
}
