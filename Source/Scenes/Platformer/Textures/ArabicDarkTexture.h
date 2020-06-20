#pragma once

#include "Engine/Terrain/TextureObject.h"

class ArabicDarkTexture : public TextureObject
{
public:
	static ArabicDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArabicDarkTexture(cocos2d::ValueMap& properties);
	virtual ~ArabicDarkTexture();

private:
	typedef TextureObject super;
};
