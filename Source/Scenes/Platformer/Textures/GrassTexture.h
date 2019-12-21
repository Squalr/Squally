#pragma once

#include "Engine/Terrain/TextureObject.h"

class GrassTexture : public TextureObject
{
public:
	static GrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	GrassTexture(cocos2d::ValueMap& properties);
	~GrassTexture();
};
