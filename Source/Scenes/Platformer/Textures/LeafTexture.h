#pragma once

#include "Engine/Terrain/TextureObject.h"

class LeafTexture : public TextureObject
{
public:
	static LeafTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	LeafTexture(cocos2d::ValueMap& properties);
	virtual ~LeafTexture();

private:
	typedef TextureObject super;
};
