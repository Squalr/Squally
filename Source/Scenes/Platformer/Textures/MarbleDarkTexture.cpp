#include "MarbleDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleDarkTexture::MapKey = "marble-dark";

MarbleDarkTexture* MarbleDarkTexture::create(ValueMap& properties)
{
	MarbleDarkTexture* instance = new MarbleDarkTexture(properties);

	instance->autorelease();

	return instance;
}

MarbleDarkTexture::MarbleDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		MarbleDarkTexture::MapKey,
		TextureResources::MarbleDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

MarbleDarkTexture::~MarbleDarkTexture()
{
}
