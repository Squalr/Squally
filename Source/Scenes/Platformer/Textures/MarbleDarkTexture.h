#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleDarkTexture : public TextureObject
{
public:
	static MarbleDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MarbleDarkTexture(cocos2d::ValueMap& properties);
	virtual ~MarbleDarkTexture();

private:
	typedef TextureObject super;
};
