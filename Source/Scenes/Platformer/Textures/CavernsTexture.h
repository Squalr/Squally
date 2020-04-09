#pragma once

#include "Engine/Terrain/TextureObject.h"

class CavernsTexture : public TextureObject
{
public:
	static CavernsTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CavernsTexture(cocos2d::ValueMap& properties);
	virtual ~CavernsTexture();

private:
	typedef TextureObject super;
};
