#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleGreenDarkTexture : public TextureObject
{
public:
	static TempleGreenDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	TempleGreenDarkTexture(cocos2d::ValueMap& properties);
	~TempleGreenDarkTexture();
};
