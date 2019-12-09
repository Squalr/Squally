#include "TempleDarkTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleDarkTexture::MapKeyTextureType = "temple-dark";

TempleDarkTexture* TempleDarkTexture::create(ValueMap& properties)
{
	TempleDarkTexture* instance = new TempleDarkTexture(properties);

	instance->autorelease();

	return instance;
}

TempleDarkTexture::TempleDarkTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		TempleDarkTexture::MapKeyTextureType,
		TextureResources::TempleDarkTexture,
		Color4B(11, 30, 39, 255)))
{
}

TempleDarkTexture::~TempleDarkTexture()
{
}
