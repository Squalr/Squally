#include "MusicLayer.h"

using namespace cocos2d;

const std::string MusicLayer::MapKeyMusicType = "music";

MusicLayer* MusicLayer::create(ValueMap& properties, std::string name)
{
	MusicLayer* instance = new MusicLayer(properties, name);

	instance->autorelease();

	return instance;
}

MusicLayer::MusicLayer(ValueMap& properties, std::string name) : super(properties, name, MusicLayer::MapKeyMusicType)
{
}

MusicLayer::~MusicLayer()
{
}
