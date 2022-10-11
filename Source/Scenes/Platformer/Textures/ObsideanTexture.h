#pragma once

#include "Engine/Terrain/TextureObject.h"

class ObsideanTexture : public TextureObject
{
public:
	static ObsideanTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ObsideanTexture(cocos2d::ValueMap& properties);
	virtual ~ObsideanTexture();

private:
	typedef TextureObject super;
};
