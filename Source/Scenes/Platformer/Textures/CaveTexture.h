#pragma once

#include "Engine/Terrain/TextureObject.h"

class CaveTexture : public TextureObject
{
public:
	static CaveTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	CaveTexture(cocos2d::ValueMap& properties);
	~CaveTexture();
};
