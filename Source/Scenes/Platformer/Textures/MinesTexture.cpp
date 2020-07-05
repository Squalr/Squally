#include "MinesTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MinesTexture::MapKey = "mines";

MinesTexture* MinesTexture::create(ValueMap& properties)
{
	MinesTexture* instance = new MinesTexture(properties);

	instance->autorelease();

	return instance;
}

MinesTexture::MinesTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		MinesTexture::MapKey,
		TextureResources::MinesTexture,
		Color4B(11, 30, 39, 255)))
{
}

MinesTexture::~MinesTexture()
{
}
