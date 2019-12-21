#pragma once

#include "Engine/Terrain/TextureObject.h"

class JungleTexture : public TextureObject
{
public:
	static JungleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	JungleTexture(cocos2d::ValueMap& properties);
	~JungleTexture();
};
