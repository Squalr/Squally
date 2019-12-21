#include "BrickInteriorTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string BrickInteriorTexture::MapKeyTextureType = "brick-interior";

BrickInteriorTexture* BrickInteriorTexture::create(ValueMap& properties)
{
	BrickInteriorTexture* instance = new BrickInteriorTexture(properties);

	instance->autorelease();

	return instance;
}

BrickInteriorTexture::BrickInteriorTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		BrickInteriorTexture::MapKeyTextureType,
		TextureResources::BrickInteriorTexture,
		Color4B(11, 30, 39, 255)))
{
}

BrickInteriorTexture::~BrickInteriorTexture()
{
}
