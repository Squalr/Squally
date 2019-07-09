#include "MusicLayer.h"

using namespace cocos2d;

MusicLayer* MusicLayer::create(ValueMap& initProperties, std::string name)
{
	MusicLayer* instance = new MusicLayer(initProperties, name);

	instance->autorelease();

	return instance;
}

MusicLayer::MusicLayer(ValueMap& initProperties, std::string name) : super(initProperties, name)
{
}

MusicLayer::~MusicLayer()
{
}
