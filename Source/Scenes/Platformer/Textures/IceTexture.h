#pragma once

#include "Engine/Terrain/TextureObject.h"

class IceTexture : public TextureObject
{
public:
	static IceTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTextureType;

private:
	typedef TextureObject super;

	IceTexture(cocos2d::ValueMap& properties);
	~IceTexture();
};
