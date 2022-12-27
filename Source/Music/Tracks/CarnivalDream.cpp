#include "CarnivalDream.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CarnivalDream::TrackKey = "carnival-dream";

CarnivalDream* CarnivalDream::create(cocos2d::ValueMap& properties)
{
	CarnivalDream* instance = new CarnivalDream(properties);

	instance->autorelease();

	return instance;
}

CarnivalDream::CarnivalDream(cocos2d::ValueMap& properties) : super(properties, MusicResources::CarnivalDream, Strings::TODO::create(), Strings::TODO::create())
{
}

CarnivalDream::~CarnivalDream()
{
}
