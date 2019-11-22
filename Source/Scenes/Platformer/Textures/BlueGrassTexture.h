#pragma once

#include "Engine/Terrain/TextureObject.h"

class BlueGrassTexture : public TextureObject
{
public:
	static BlueGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	BlueGrassTexture(cocos2d::ValueMap& properties);
	~BlueGrassTexture();
};
