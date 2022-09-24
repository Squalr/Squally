#include "BlackTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string BlackTexture::MapKey = "black";

BlackTexture* BlackTexture::create(ValueMap& properties)
{
	BlackTexture* instance = new BlackTexture(properties);

	instance->autorelease();

	return instance;
}

BlackTexture::BlackTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		BlackTexture::MapKey,
		TextureResources::BlackTexture,
		Color4B(11, 30, 39, 255)))
{
}

BlackTexture::~BlackTexture()
{
}
