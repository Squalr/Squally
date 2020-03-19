#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleGrassTexture : public TextureObject
{
public:
	static MarbleGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MarbleGrassTexture(cocos2d::ValueMap& properties);
	virtual ~MarbleGrassTexture();

private:
	typedef TextureObject super;
};
