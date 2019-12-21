#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShipTexture : public TextureObject
{
public:
	static ShipTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	ShipTexture(cocos2d::ValueMap& properties);
	~ShipTexture();
};
