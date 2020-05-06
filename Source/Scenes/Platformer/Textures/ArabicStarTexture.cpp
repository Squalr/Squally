#include "ArabicStarTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ArabicStarTexture::MapKey = "arabic-star";

ArabicStarTexture* ArabicStarTexture::create(ValueMap& properties)
{
	ArabicStarTexture* instance = new ArabicStarTexture(properties);

	instance->autorelease();

	return instance;
}

ArabicStarTexture::ArabicStarTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ArabicStarTexture::MapKey,
		TextureResources::ArabicStarTexture,
		Color4B(11, 30, 39, 255)))
{
}

ArabicStarTexture::~ArabicStarTexture()
{
}
