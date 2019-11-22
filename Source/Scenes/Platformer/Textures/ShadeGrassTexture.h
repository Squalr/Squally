#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShadeGrassTexture : public TextureObject
{
public:
	static ShadeGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	ShadeGrassTexture(cocos2d::ValueMap& properties);
	~ShadeGrassTexture();
};
