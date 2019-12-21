#include "MarbleGrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleGrassTexture::MapKeyTextureType = "marble-grass";

MarbleGrassTexture* MarbleGrassTexture::create(ValueMap& properties)
{
	MarbleGrassTexture* instance = new MarbleGrassTexture(properties);

	instance->autorelease();

	return instance;
}

MarbleGrassTexture::MarbleGrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		MarbleGrassTexture::MapKeyTextureType,
		TextureResources::MarbleGrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

MarbleGrassTexture::~MarbleGrassTexture()
{
}
