#pragma once

#include "Engine/Terrain/TextureObject.h"

class DryTexture : public TextureObject
{
public:
	static DryTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DryTexture(cocos2d::ValueMap& properties);
	virtual ~DryTexture();

private:
	typedef TextureObject super;
};
