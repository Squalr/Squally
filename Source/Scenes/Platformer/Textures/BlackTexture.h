#pragma once

#include "Engine/Terrain/TextureObject.h"

class BlackTexture : public TextureObject
{
public:
	static BlackTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BlackTexture(cocos2d::ValueMap& properties);
	virtual ~BlackTexture();

private:
	typedef TextureObject super;
};
