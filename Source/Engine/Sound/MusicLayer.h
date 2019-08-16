#pragma once

#include "Engine/Maps/MapLayer.h"

class MusicLayer : public MapLayer
{
public:
	static MusicLayer* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyMusicType;

private:
	typedef MapLayer super;

	MusicLayer(cocos2d::ValueMap& properties, std::string name);
	~MusicLayer();
};
