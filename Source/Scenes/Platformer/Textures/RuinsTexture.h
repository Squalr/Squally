#pragma once

#include "Engine/Terrain/TextureObject.h"

class RuinsTexture : public TextureObject
{
public:
	static RuinsTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsTexture(cocos2d::ValueMap& properties);
	virtual ~RuinsTexture();

private:
	typedef TextureObject super;
};
