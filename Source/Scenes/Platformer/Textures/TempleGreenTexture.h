#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleGreenTexture : public TextureObject
{
public:
	static TempleGreenTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	TempleGreenTexture(cocos2d::ValueMap& properties);
	~TempleGreenTexture();
};
