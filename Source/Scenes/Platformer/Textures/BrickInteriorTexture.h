#pragma once

#include "Engine/Terrain/TextureObject.h"

class BrickInteriorTexture : public TextureObject
{
public:
	static BrickInteriorTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	BrickInteriorTexture(cocos2d::ValueMap& properties);
	~BrickInteriorTexture();
};
