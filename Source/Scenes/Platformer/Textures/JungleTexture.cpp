#include "JungleTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string JungleTexture::MapKeyTextureType = "jungle";

JungleTexture* JungleTexture::create(ValueMap& properties)
{
	JungleTexture* instance = new JungleTexture(properties);

	instance->autorelease();

	return instance;
}

JungleTexture::JungleTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		JungleTexture::MapKeyTextureType,
		TextureResources::JungleTexture,
		Color4B(11, 30, 39, 255)))
{
}

JungleTexture::~JungleTexture()
{
}
