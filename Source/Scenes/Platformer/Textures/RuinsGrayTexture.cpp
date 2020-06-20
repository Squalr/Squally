#include "RuinsGrayTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsGrayTexture::MapKey = "ruins-gray";

RuinsGrayTexture* RuinsGrayTexture::create(ValueMap& properties)
{
	RuinsGrayTexture* instance = new RuinsGrayTexture(properties);

	instance->autorelease();

	return instance;
}

RuinsGrayTexture::RuinsGrayTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		RuinsGrayTexture::MapKey,
		TextureResources::RuinsGrayTexture,
		Color4B(11, 30, 39, 255)))
{
}

RuinsGrayTexture::~RuinsGrayTexture()
{
}
