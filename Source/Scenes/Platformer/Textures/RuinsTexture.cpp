#include "RuinsTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsTexture::MapKey = "ruins";

RuinsTexture* RuinsTexture::create(ValueMap& properties)
{
	RuinsTexture* instance = new RuinsTexture(properties);

	instance->autorelease();

	return instance;
}

RuinsTexture::RuinsTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		RuinsTexture::MapKey,
		TextureResources::RuinsTexture,
		Color4B(11, 30, 39, 255)))
{
}

RuinsTexture::~RuinsTexture()
{
}
