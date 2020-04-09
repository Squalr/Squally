#pragma once

#include "Engine/Terrain/TextureObject.h"

class IceTexture : public TextureObject
{
public:
	static IceTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IceTexture(cocos2d::ValueMap& properties);
	virtual ~IceTexture();

private:
	typedef TextureObject super;
};
