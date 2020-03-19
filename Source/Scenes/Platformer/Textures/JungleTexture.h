#pragma once

#include "Engine/Terrain/TextureObject.h"

class JungleTexture : public TextureObject
{
public:
	static JungleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	JungleTexture(cocos2d::ValueMap& properties);
	virtual ~JungleTexture();

private:
	typedef TextureObject super;
};
