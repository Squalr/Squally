#include "Medieval.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medieval::TrackKey = "medieval";

Medieval* Medieval::create()
{
	Medieval* instance = new Medieval();

	instance->autorelease();

	return instance;
}

Medieval::Medieval() : super(MusicResources::HeartBeat)
{
}

Medieval::~Medieval()
{
}
