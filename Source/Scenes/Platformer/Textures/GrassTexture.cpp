#include "GrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string GrassTexture::MapKey = "grass";

GrassTexture* GrassTexture::create(ValueMap& properties)
{
	GrassTexture* instance = new GrassTexture(properties);

	instance->autorelease();

	return instance;
}

GrassTexture::GrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		GrassTexture::MapKey,
		TextureResources::GrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

GrassTexture::~GrassTexture()
{
}
