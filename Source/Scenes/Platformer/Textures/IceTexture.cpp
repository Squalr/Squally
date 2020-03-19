#include "IceTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string IceTexture::MapKey = "ice";

IceTexture* IceTexture::create(ValueMap& properties)
{
	IceTexture* instance = new IceTexture(properties);

	instance->autorelease();

	return instance;
}

IceTexture::IceTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		IceTexture::MapKey,
		TextureResources::IceTexture,
		Color4B(11, 30, 39, 255)))
{
}

IceTexture::~IceTexture()
{
}
