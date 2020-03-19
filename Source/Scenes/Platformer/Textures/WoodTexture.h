#pragma once

#include "Engine/Terrain/TextureObject.h"

class WoodTexture : public TextureObject
{
public:
	static WoodTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WoodTexture(cocos2d::ValueMap& properties);
	virtual ~WoodTexture();

private:
	typedef TextureObject super;
};
