#include "ArabicTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ArabicTexture::MapKey = "arabic";

ArabicTexture* ArabicTexture::create(ValueMap& properties)
{
	ArabicTexture* instance = new ArabicTexture(properties);

	instance->autorelease();

	return instance;
}

ArabicTexture::ArabicTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ArabicTexture::MapKey,
		TextureResources::ArabicWebTexture,
		Color4B(11, 30, 39, 255)))
{
}

ArabicTexture::~ArabicTexture()
{
}
