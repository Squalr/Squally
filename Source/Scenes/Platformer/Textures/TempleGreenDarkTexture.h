#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleGreenDarkTexture : public TextureObject
{
public:
	static TempleGreenDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleGreenDarkTexture(cocos2d::ValueMap& properties);
	virtual ~TempleGreenDarkTexture();

private:
	typedef TextureObject super;
};
