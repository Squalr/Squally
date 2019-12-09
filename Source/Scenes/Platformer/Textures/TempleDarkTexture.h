#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleDarkTexture : public TextureObject
{
public:
	static TempleDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	TempleDarkTexture(cocos2d::ValueMap& properties);
	~TempleDarkTexture();
};
