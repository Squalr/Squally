#include "TempleGreenDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleGreenDarkTexture::MapKeyTextureType = "temple-green-dark";

TempleGreenDarkTexture* TempleGreenDarkTexture::create(ValueMap& properties)
{
	TempleGreenDarkTexture* instance = new TempleGreenDarkTexture(properties);

	instance->autorelease();

	return instance;
}

TempleGreenDarkTexture::TempleGreenDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		TempleGreenDarkTexture::MapKeyTextureType,
		TextureResources::TempleGreenDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

TempleGreenDarkTexture::~TempleGreenDarkTexture()
{
}
