#pragma once

#include "Engine/Terrain/TextureObject.h"

class CastleTexture : public TextureObject
{
public:
	static CastleTexture* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CastleTexture(cocos2d::ValueMap& properties);
	virtual ~CastleTexture();

private:
	typedef TextureObject super;
};
