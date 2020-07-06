#include "StoneDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string StoneDarkTexture::MapKey = "stone-dark";

StoneDarkTexture* StoneDarkTexture::create(ValueMap& properties)
{
	StoneDarkTexture* instance = new StoneDarkTexture(properties);

	instance->autorelease();

	return instance;
}

StoneDarkTexture::StoneDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		StoneDarkTexture::MapKey,
		TextureResources::StoneDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

StoneDarkTexture::~StoneDarkTexture()
{
}
