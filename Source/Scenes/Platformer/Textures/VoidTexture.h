#pragma once

#include "Engine/Terrain/TextureObject.h"

class VoidTexture : public TextureObject
{
public:
	static VoidTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	VoidTexture(cocos2d::ValueMap& properties);
	virtual ~VoidTexture();

private:
	typedef TextureObject super;
};
