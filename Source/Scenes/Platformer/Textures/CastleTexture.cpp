#include "CastleTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CastleTexture::MapKeyTextureType = "blue-grass";

CastleTexture* CastleTexture::create(ValueMap& properties)
{
	CastleTexture* instance = new CastleTexture(properties);

	instance->autorelease();

	return instance;
}

CastleTexture::CastleTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		CastleTexture::MapKeyTextureType,
		TextureResources::CastleTexture,
		Color4B(11, 30, 39, 255)))
{
}

CastleTexture::~CastleTexture()
{
}
