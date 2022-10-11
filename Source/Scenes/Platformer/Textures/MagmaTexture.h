#pragma once

#include "Engine/Terrain/TextureObject.h"

class MagmaTexture : public TextureObject
{
public:
	static MagmaTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MagmaTexture(cocos2d::ValueMap& properties);
	virtual ~MagmaTexture();

private:
	typedef TextureObject super;
};
