#pragma once

#include "Engine/Terrain/TextureObject.h"

class LeafTexture : public TextureObject
{
public:
	static LeafTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	LeafTexture(cocos2d::ValueMap& properties);
	~LeafTexture();
};
