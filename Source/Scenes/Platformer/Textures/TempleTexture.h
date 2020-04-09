#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleTexture : public TextureObject
{
public:
	static TempleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleTexture(cocos2d::ValueMap& properties);
	virtual ~TempleTexture();

private:
	typedef TextureObject super;
};
