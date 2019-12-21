#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleTexture : public TextureObject
{
public:
	static TempleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	TempleTexture(cocos2d::ValueMap& properties);
	~TempleTexture();
};
