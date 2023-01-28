#pragma once

#include "Engine/Terrain/TextureObject.h"

class CatacombsTexture : public TextureObject
{
public:
	static CatacombsTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CatacombsTexture(cocos2d::ValueMap& properties);
	virtual ~CatacombsTexture();

private:
	typedef TextureObject super;
};
