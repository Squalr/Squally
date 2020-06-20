#pragma once

#include "Engine/Terrain/TextureObject.h"

class ArabicStarTexture : public TextureObject
{
public:
	static ArabicStarTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArabicStarTexture(cocos2d::ValueMap& properties);
	virtual ~ArabicStarTexture();

private:
	typedef TextureObject super;
};
