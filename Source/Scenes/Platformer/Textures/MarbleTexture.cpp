#include "MarbleTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleTexture::MapKey = "marble";

MarbleTexture* MarbleTexture::create(ValueMap& properties)
{
	MarbleTexture* instance = new MarbleTexture(properties);

	instance->autorelease();

	return instance;
}

MarbleTexture::MarbleTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		MarbleTexture::MapKey,
		TextureResources::MarbleTexture,
		Color4B(11, 30, 39, 255)))
{
}

MarbleTexture::~MarbleTexture()
{
}
