#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleGreenTexture : public TextureObject
{
public:
	static TempleGreenTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleGreenTexture(cocos2d::ValueMap& properties);
	virtual ~TempleGreenTexture();

private:
	typedef TextureObject super;
};
