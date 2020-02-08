#include "Medieval2.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medieval2::TrackKey = "medieval2";

Medieval2* Medieval2::create()
{
	Medieval2* instance = new Medieval2();

	instance->autorelease();

	return instance;
}

Medieval2::Medieval2() : super(MusicResources::Hexus2)
{
}

Medieval2::~Medieval2()
{
}
