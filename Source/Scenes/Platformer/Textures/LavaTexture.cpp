#include "LavaTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LavaTexture::MapKey = "lava";

LavaTexture* LavaTexture::create(ValueMap& properties)
{
	LavaTexture* instance = new LavaTexture(properties);

	instance->autorelease();

	return instance;
}

LavaTexture::LavaTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		LavaTexture::MapKey,
		TextureResources::LavaTexture,
		Color4B(11, 30, 39, 255)))
{
}

LavaTexture::~LavaTexture()
{
}
