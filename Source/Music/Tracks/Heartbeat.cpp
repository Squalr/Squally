#include "Heartbeat.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Heartbeat::TrackKey = "heartbeat";

Heartbeat* Heartbeat::create(SmartNode* owner)
{
	Heartbeat* instance = new Heartbeat(owner);

	instance->autorelease();

	return instance;
}

Heartbeat::Heartbeat(SmartNode* owner) : super(MusicResources::HeartBeat, owner)
{
}

Heartbeat::~Heartbeat()
{
}
