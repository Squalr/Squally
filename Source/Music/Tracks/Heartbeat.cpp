#include "Heartbeat.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Heartbeat::TrackKey = "heartbeat";

Heartbeat* Heartbeat::create(cocos2d::ValueMap& properties)
{
	Heartbeat* instance = new Heartbeat(properties);

	instance->autorelease();

	return instance;
}

Heartbeat::Heartbeat(cocos2d::ValueMap& properties) : super(properties, MusicResources::HeartBeat, Strings::Menus_Music_AlexanderIvanov_Heartbeat::create(), Strings::Menus_Music_AlexanderIvanov_AlexanderIvanov::create())
{
}

Heartbeat::~Heartbeat()
{
}
