#pragma once

#include "Engine/Terrain/TextureObject.h"

class TrailTexture : public TextureObject
{
public:
	static TrailTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TrailTexture(cocos2d::ValueMap& properties);
	virtual ~TrailTexture();

private:
	typedef TextureObject super;
};
