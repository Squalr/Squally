#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShipAltTexture : public TextureObject
{
public:
	static ShipAltTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

protected:
	ShipAltTexture(cocos2d::ValueMap& properties);
	virtual ~ShipAltTexture();

private:
	typedef TextureObject super;
};
