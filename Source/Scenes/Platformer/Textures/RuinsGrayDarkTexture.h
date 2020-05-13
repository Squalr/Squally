#pragma once

#include "Engine/Terrain/TextureObject.h"

class RuinsGrayDarkTexture : public TextureObject
{
public:
	static RuinsGrayDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsGrayDarkTexture(cocos2d::ValueMap& properties);
	virtual ~RuinsGrayDarkTexture();

private:
	typedef TextureObject super;
};
