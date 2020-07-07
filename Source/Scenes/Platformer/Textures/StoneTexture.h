#pragma once

#include "Engine/Terrain/TextureObject.h"

class StoneTexture : public TextureObject
{
public:
	static StoneTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	StoneTexture(cocos2d::ValueMap& properties);
	virtual ~StoneTexture();

private:
	typedef TextureObject super;
};
