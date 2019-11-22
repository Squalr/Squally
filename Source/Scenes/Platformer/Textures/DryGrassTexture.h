#pragma once

#include "Engine/Terrain/TextureObject.h"

class DryGrassTexture : public TextureObject
{
public:
	static DryGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	DryGrassTexture(cocos2d::ValueMap& properties);
	~DryGrassTexture();
};
