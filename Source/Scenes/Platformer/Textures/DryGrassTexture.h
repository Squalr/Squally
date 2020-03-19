#pragma once

#include "Engine/Terrain/TextureObject.h"

class DryGrassTexture : public TextureObject
{
public:
	static DryGrassTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DryGrassTexture(cocos2d::ValueMap& properties);
	virtual ~DryGrassTexture();

private:
	typedef TextureObject super;
};
