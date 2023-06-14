#include "ScifiDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ScifiDarkTexture::MapKey = "scifi-dark";

ScifiDarkTexture* ScifiDarkTexture::create(ValueMap& properties)
{
	ScifiDarkTexture* instance = new ScifiDarkTexture(properties);

	instance->autorelease();

	return instance;
}

ScifiDarkTexture::ScifiDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ScifiDarkTexture::MapKey,
		TextureResources::ScifiDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

ScifiDarkTexture::~ScifiDarkTexture()
{
}
