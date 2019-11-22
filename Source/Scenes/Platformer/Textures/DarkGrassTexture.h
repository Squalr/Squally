#pragma once

#include "Engine/Terrain/TextureObject.h"

class DarkGrassTexture : public TextureObject
{
public:
	static DarkGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	DarkGrassTexture(cocos2d::ValueMap& properties);
	~DarkGrassTexture();
};
