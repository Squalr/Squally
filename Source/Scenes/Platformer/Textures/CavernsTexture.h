#pragma once

#include "Engine/Terrain/TextureObject.h"

class CavernsTexture : public TextureObject
{
public:
	static CavernsTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	CavernsTexture(cocos2d::ValueMap& properties);
	~CavernsTexture();
};
