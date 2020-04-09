#include "CaveTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CaveTexture::MapKey = "cave";

CaveTexture* CaveTexture::create(ValueMap& properties)
{
	CaveTexture* instance = new CaveTexture(properties);

	instance->autorelease();

	return instance;
}

CaveTexture::CaveTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		CaveTexture::MapKey,
		TextureResources::CaveTexture,
		Color4B(11, 30, 39, 255)))
{
}

CaveTexture::~CaveTexture()
{
}
