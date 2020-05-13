#pragma once

#include "Engine/Terrain/TextureObject.h"

class RuinsGrayTexture : public TextureObject
{
public:
	static RuinsGrayTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsGrayTexture(cocos2d::ValueMap& properties);
	virtual ~RuinsGrayTexture();

private:
	typedef TextureObject super;
};
