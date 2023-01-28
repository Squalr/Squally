#include "CatacombsTexture.h"

#include "cocos/base/CCValue.h"

#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CatacombsTexture::MapKey = "catacombs";

CatacombsTexture* CatacombsTexture::create(ValueMap& properties)
{
	CatacombsTexture* instance = new CatacombsTexture(properties);

	instance->autorelease();

	return instance;
}

CatacombsTexture::CatacombsTexture(ValueMap& properties) : super(
	properties,
	TextureObject::TextureData(
		CatacombsTexture::MapKey,
		TextureResources::CatacombsTexture,
		Color4B(11, 30, 39, 255)))
{
}

CatacombsTexture::~CatacombsTexture()
{
}
