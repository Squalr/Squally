#include "RuinsGrayDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsGrayDarkTexture::MapKey = "ruins-gray-dark";

RuinsGrayDarkTexture* RuinsGrayDarkTexture::create(ValueMap& properties)
{
	RuinsGrayDarkTexture* instance = new RuinsGrayDarkTexture(properties);

	instance->autorelease();

	return instance;
}

RuinsGrayDarkTexture::RuinsGrayDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		RuinsGrayDarkTexture::MapKey,
		TextureResources::RuinsGrayDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

RuinsGrayDarkTexture::~RuinsGrayDarkTexture()
{
}
