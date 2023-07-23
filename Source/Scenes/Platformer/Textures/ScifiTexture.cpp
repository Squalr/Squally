#include "ScifiTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ScifiTexture::MapKey = "scifi";

ScifiTexture* ScifiTexture::create(ValueMap& properties)
{
	ScifiTexture* instance = new ScifiTexture(properties);

	instance->autorelease();

	return instance;
}

ScifiTexture::ScifiTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ScifiTexture::MapKey,
		TextureResources::ScifiTexture,
		Color4B(11, 30, 39, 255)))
{
}

ScifiTexture::~ScifiTexture()
{
}
