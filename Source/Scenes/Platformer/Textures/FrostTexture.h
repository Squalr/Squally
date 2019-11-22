#pragma once

#include "Engine/Terrain/TextureObject.h"

class FrostTexture : public TextureObject
{
public:
	static FrostTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	FrostTexture(cocos2d::ValueMap& properties);
	~FrostTexture();
};
