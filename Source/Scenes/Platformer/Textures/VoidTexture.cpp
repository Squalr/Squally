#include "VoidTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string VoidTexture::MapKey = "void";

VoidTexture* VoidTexture::create(ValueMap& properties)
{
	VoidTexture* instance = new VoidTexture(properties);

	instance->autorelease();

	return instance;
}

VoidTexture::VoidTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		VoidTexture::MapKey,
		TextureResources::VoidTexture,
		Color4B(11, 30, 39, 255)))
{
}

VoidTexture::~VoidTexture()
{
}
