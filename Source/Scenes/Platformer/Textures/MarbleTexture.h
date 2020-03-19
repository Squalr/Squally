#pragma once

#include "Engine/Terrain/TextureObject.h"

class MarbleTexture : public TextureObject
{
public:
	static MarbleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MarbleTexture(cocos2d::ValueMap& properties);
	virtual ~MarbleTexture();

private:
	typedef TextureObject super;
};
