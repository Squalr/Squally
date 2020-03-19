#pragma once

#include "Engine/Terrain/TextureObject.h"

class FrostTexture : public TextureObject
{
public:
	static FrostTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	FrostTexture(cocos2d::ValueMap& properties);
	virtual ~FrostTexture();

private:
	typedef TextureObject super;
};
