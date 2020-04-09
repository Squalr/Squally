#pragma once

#include "Engine/Terrain/TextureObject.h"

class ShipTexture : public TextureObject
{
public:
	static ShipTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ShipTexture(cocos2d::ValueMap& properties);
	virtual ~ShipTexture();

private:
	typedef TextureObject super;
};
