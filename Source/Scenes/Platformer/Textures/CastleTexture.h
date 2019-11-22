#pragma once

#include "Engine/Terrain/TextureObject.h"

class CastleTexture : public TextureObject
{
public:
	static CastleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	CastleTexture(cocos2d::ValueMap& properties);
	~CastleTexture();
};
