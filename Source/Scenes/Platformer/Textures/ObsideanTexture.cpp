#include "ObsideanTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ObsideanTexture::MapKey = "obsidean";

ObsideanTexture* ObsideanTexture::create(ValueMap& properties)
{
	ObsideanTexture* instance = new ObsideanTexture(properties);

	instance->autorelease();

	return instance;
}

ObsideanTexture::ObsideanTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		ObsideanTexture::MapKey,
		TextureResources::ObsideanTexture,
		Color4B(224, 127, 39, 255)))
{
}

ObsideanTexture::~ObsideanTexture()
{
}
