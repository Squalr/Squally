#include "TempleGreenTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleGreenTexture::MapKey = "temple-green";

TempleGreenTexture* TempleGreenTexture::create(ValueMap& properties)
{
	TempleGreenTexture* instance = new TempleGreenTexture(properties);

	instance->autorelease();

	return instance;
}

TempleGreenTexture::TempleGreenTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		TempleGreenTexture::MapKey,
		TextureResources::TempleGreenTexture,
		Color4B(11, 30, 39, 255)))
{
}

TempleGreenTexture::~TempleGreenTexture()
{
}
