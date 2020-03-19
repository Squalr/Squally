#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShadeGrassTexture : public TextureObject
{
public:
	static ShadeGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ShadeGrassTexture(cocos2d::ValueMap& properties);
	virtual ~ShadeGrassTexture();

private:
	typedef TextureObject super;
};
