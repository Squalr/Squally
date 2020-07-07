#pragma once

#include "Engine/Terrain/TextureObject.h"

class StoneDarkTexture : public TextureObject
{
public:
	static StoneDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	StoneDarkTexture(cocos2d::ValueMap& properties);
	virtual ~StoneDarkTexture();

private:
	typedef TextureObject super;
};
