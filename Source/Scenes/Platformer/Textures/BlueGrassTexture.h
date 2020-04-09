#pragma once

#include "Engine/Terrain/TextureObject.h"

class BlueGrassTexture : public TextureObject
{
public:
	static BlueGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BlueGrassTexture(cocos2d::ValueMap& properties);
	virtual ~BlueGrassTexture();

private:
	typedef TextureObject super;
};
