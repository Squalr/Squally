#pragma once

#include "Engine/Terrain/TextureObject.h"

class CaveTexture : public TextureObject
{
public:
	static CaveTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CaveTexture(cocos2d::ValueMap& properties);
	virtual ~CaveTexture();

private:
	typedef TextureObject super;
};
