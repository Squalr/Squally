#pragma once

#include "Engine/Terrain/TextureObject.h"

class TrailTexture : public TextureObject
{
public:
	static TrailTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	TrailTexture(cocos2d::ValueMap& properties);
	~TrailTexture();
};
