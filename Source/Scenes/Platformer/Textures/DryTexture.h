#pragma once

#include "Engine/Terrain/TextureObject.h"

class DryTexture : public TextureObject
{
public:
	static DryTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	DryTexture(cocos2d::ValueMap& properties);
	~DryTexture();
};
