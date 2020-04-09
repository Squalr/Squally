#include "LeafTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LeafTexture::MapKey = "leaf";

LeafTexture* LeafTexture::create(ValueMap& properties)
{
	LeafTexture* instance = new LeafTexture(properties);

	instance->autorelease();

	return instance;
}

LeafTexture::LeafTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		LeafTexture::MapKey,
		TextureResources::LeafTexture,
		Color4B(11, 30, 39, 255)))
{
}

LeafTexture::~LeafTexture()
{
}
