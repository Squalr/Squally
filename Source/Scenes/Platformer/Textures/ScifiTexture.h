#pragma once

#include "Engine/Terrain/TextureObject.h"

class ScifiTexture : public TextureObject
{
public:
	static ScifiTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ScifiTexture(cocos2d::ValueMap& properties);
	virtual ~ScifiTexture();

private:
	typedef TextureObject super;
};
