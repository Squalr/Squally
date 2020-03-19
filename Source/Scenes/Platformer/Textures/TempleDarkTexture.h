#pragma once

#include "Engine/Terrain/TextureObject.h"

class TempleDarkTexture : public TextureObject
{
public:
	static TempleDarkTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleDarkTexture(cocos2d::ValueMap& properties);
	virtual ~TempleDarkTexture();

private:
	typedef TextureObject super;
};
