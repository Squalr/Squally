#pragma once

#include "Engine/Terrain/TextureObject.h"

class LavaTexture : public TextureObject
{
public:
	static LavaTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	LavaTexture(cocos2d::ValueMap& properties);
	virtual ~LavaTexture();

private:
	typedef TextureObject super;
};
