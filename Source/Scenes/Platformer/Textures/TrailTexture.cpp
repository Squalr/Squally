#include "TrailTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TrailTexture::MapKey = "trail";

TrailTexture* TrailTexture::create(ValueMap& properties)
{
	TrailTexture* instance = new TrailTexture(properties);

	instance->autorelease();

	return instance;
}

TrailTexture::TrailTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		TrailTexture::MapKey,
		TextureResources::TrailTexture,
		Color4B(11, 30, 39, 255)))
{
}

TrailTexture::~TrailTexture()
{
}
