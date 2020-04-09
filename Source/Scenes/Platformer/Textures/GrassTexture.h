#pragma once

#include "Engine/Terrain/TextureObject.h"

class GrassTexture : public TextureObject
{
public:
	static GrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	GrassTexture(cocos2d::ValueMap& properties);
	virtual ~GrassTexture();

private:
	typedef TextureObject super;
};
