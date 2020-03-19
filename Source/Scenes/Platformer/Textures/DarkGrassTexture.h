#pragma once

#include "Engine/Terrain/TextureObject.h"

class DarkGrassTexture : public TextureObject
{
public:
	static DarkGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DarkGrassTexture(cocos2d::ValueMap& properties);
	virtual ~DarkGrassTexture();

private:
	typedef TextureObject super;
};
