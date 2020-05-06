#include "ArabicDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ArabicDarkTexture::MapKey = "arabic-dark";

ArabicDarkTexture* ArabicDarkTexture::create(ValueMap& properties)
{
	ArabicDarkTexture* instance = new ArabicDarkTexture(properties);

	instance->autorelease();

	return instance;
}

ArabicDarkTexture::ArabicDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ArabicDarkTexture::MapKey,
		TextureResources::ArabicWebDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

ArabicDarkTexture::~ArabicDarkTexture()
{
}
