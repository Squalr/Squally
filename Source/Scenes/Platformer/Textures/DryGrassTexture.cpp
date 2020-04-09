#include "DryGrassTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DryGrassTexture::MapKey = "dry-grass";

DryGrassTexture* DryGrassTexture::create(ValueMap& properties)
{
	DryGrassTexture* instance = new DryGrassTexture(properties);

	instance->autorelease();

	return instance;
}

DryGrassTexture::DryGrassTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		DryGrassTexture::MapKey,
		TextureResources::DryGrassTexture,
		Color4B(11, 30, 39, 255)))
{
}

DryGrassTexture::~DryGrassTexture()
{
}
