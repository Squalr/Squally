#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleDarkTexture : public TextureObject
{
public:
	static MarbleDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	MarbleDarkTexture(cocos2d::ValueMap& properties);
	~MarbleDarkTexture();
};
