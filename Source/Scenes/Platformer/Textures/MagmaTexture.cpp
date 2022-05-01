#include "MagmaTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MagmaTexture::MapKey = "magma";

MagmaTexture* MagmaTexture::create(ValueMap& properties)
{
	MagmaTexture* instance = new MagmaTexture(properties);

	instance->autorelease();

	return instance;
}

MagmaTexture::MagmaTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		MagmaTexture::MapKey,
		TextureResources::MagmaTexture,
		Color4B(224, 127, 39, 255)))
{
}

MagmaTexture::~MagmaTexture()
{
}
