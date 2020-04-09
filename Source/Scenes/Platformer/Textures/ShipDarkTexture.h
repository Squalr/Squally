#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShipDarkTexture : public TextureObject
{
public:
	static ShipDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ShipDarkTexture(cocos2d::ValueMap& properties);
	virtual ~ShipDarkTexture();

private:
	typedef TextureObject super;
};
