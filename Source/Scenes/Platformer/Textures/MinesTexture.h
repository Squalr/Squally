#pragma once

#include "Engine/Terrain/TextureObject.h"

class MinesTexture : public TextureObject
{
public:
	static MinesTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MinesTexture(cocos2d::ValueMap& properties);
	virtual ~MinesTexture();

private:
	typedef TextureObject super;
};
