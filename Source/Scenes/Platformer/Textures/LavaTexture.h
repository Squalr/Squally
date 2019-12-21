#pragma once

#include "Engine/Terrain/TextureObject.h"

class LavaTexture : public TextureObject
{
public:
	static LavaTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	LavaTexture(cocos2d::ValueMap& properties);
	~LavaTexture();
};
