#include "TempleTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleTexture::MapKey = "temple";

TempleTexture* TempleTexture::create(ValueMap& properties)
{
	TempleTexture* instance = new TempleTexture(properties);

	instance->autorelease();

	return instance;
}

TempleTexture::TempleTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		TempleTexture::MapKey,
		TextureResources::TempleTexture,
		Color4B(11, 30, 39, 255)))
{
}

TempleTexture::~TempleTexture()
{
}
