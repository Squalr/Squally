#include "MusicLayer.h"

using namespace cocos2d;

const std::string MusicLayer::MapKeyMusicType = "music";

MusicLayer* MusicLayer::create(ValueMap& initProperties, std::string name)
{
	MusicLayer* instance = new MusicLayer(initProperties, name);

	instance->autorelease();

	return instance;
}

MusicLayer::MusicLayer(ValueMap& initProperties, std::string name) : super(initProperties, name, MusicLayer::MapKeyMusicType)
{
}

MusicLayer::~MusicLayer()
{
}
