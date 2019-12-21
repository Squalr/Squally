#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShipAltTexture : public TextureObject
{
public:
	static ShipAltTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	ShipAltTexture(cocos2d::ValueMap& properties);
	~ShipAltTexture();
};
