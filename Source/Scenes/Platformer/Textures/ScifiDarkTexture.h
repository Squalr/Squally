#pragma once

#include "Engine/Terrain/TextureObject.h"

class ScifiDarkTexture : public TextureObject
{
public:
	static ScifiDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ScifiDarkTexture(cocos2d::ValueMap& properties);
	virtual ~ScifiDarkTexture();

private:
	typedef TextureObject super;
};
