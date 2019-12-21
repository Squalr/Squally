#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleGrassTexture : public TextureObject
{
public:
	static MarbleGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	MarbleGrassTexture(cocos2d::ValueMap& properties);
	~MarbleGrassTexture();
};
