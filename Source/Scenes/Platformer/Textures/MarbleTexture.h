#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleTexture : public TextureObject
{
public:
	static MarbleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	MarbleTexture(cocos2d::ValueMap& properties);
	~MarbleTexture();
};
