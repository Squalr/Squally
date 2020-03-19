#include "FrostTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string FrostTexture::MapKey = "frost";

FrostTexture* FrostTexture::create(ValueMap& properties)
{
	FrostTexture* instance = new FrostTexture(properties);

	instance->autorelease();

	return instance;
}

FrostTexture::FrostTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		FrostTexture::MapKey,
		TextureResources::FrostTexture,
		Color4B(11, 30, 39, 255)))
{
}

FrostTexture::~FrostTexture()
{
}
