#pragma once

#include "Engine/Terrain/TextureObject.h"

class WoodTexture : public TextureObject
{
public:
	static WoodTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	WoodTexture(cocos2d::ValueMap& properties);
	~WoodTexture();
};
