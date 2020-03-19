#pragma once

#include "Engine/Terrain/TextureObject.h"

class BrickInteriorTexture : public TextureObject
{
public:
	static BrickInteriorTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BrickInteriorTexture(cocos2d::ValueMap& properties);
	virtual ~BrickInteriorTexture();

private:
	typedef TextureObject super;
};
