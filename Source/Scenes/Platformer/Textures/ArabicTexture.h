#pragma once

#include "Engine/Terrain/TextureObject.h"

class ArabicTexture : public TextureObject
{
public:
	static ArabicTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArabicTexture(cocos2d::ValueMap& properties);
	virtual ~ArabicTexture();

private:
	typedef TextureObject super;
};
