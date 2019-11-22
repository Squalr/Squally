#include "CavernsTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CavernsTexture::MapKeyTextureType = "caverns";

CavernsTexture* CavernsTexture::create(ValueMap& properties)
{
	CavernsTexture* instance = new CavernsTexture(properties);

	instance->autorelease();

	return instance;
}

CavernsTexture::CavernsTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		CavernsTexture::MapKeyTextureType,
		TextureResources::CavernsTexture,
		Color4B(11, 30, 39, 255)))
{
}

CavernsTexture::~CavernsTexture()
{
}
