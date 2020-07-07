#include "StoneTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string StoneTexture::MapKey = "stone";

StoneTexture* StoneTexture::create(ValueMap& properties)
{
	StoneTexture* instance = new StoneTexture(properties);

	instance->autorelease();

	return instance;
}

StoneTexture::StoneTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		StoneTexture::MapKey,
		TextureResources::StoneTexture,
		Color4B(11, 30, 39, 255)))
{
}

StoneTexture::~StoneTexture()
{
}
