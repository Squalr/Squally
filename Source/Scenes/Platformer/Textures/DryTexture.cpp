#include "DryTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DryTexture::MapKey = "dry";

DryTexture* DryTexture::create(ValueMap& properties)
{
	DryTexture* instance = new DryTexture(properties);

	instance->autorelease();

	return instance;
}

DryTexture::DryTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		DryTexture::MapKey,
		TextureResources::DryTexture,
		Color4B(11, 30, 39, 255)))
{
}

DryTexture::~DryTexture()
{
}
