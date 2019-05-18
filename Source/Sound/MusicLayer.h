#pragma once

#include "Engine/Maps/SerializableLayer.h"

class MusicLayer : public SerializableLayer
{
public:
	static MusicLayer* create(cocos2d::ValueMap& initProperties, std::string name);

private:
	typedef SerializableLayer super;

	MusicLayer(cocos2d::ValueMap& initProperties, std::string name);
	~MusicLayer();
};
