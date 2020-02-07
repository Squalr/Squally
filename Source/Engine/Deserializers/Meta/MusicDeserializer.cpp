#include "MusicDeserializer.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Sound/Track.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MusicDeserializer::MapKeyMusicProperty = "music";
const std::string MusicDeserializer::MapKeyDelayProperty = "delay";

MusicDeserializer* MusicDeserializer::create()
{
	MusicDeserializer* instance = new MusicDeserializer();

	instance->autorelease();

	return instance;
}

MusicDeserializer::MusicDeserializer() : super()
{
}

MusicDeserializer::~MusicDeserializer()
{
}

void MusicDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string trackSerializationKey = GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyMusicProperty, Value("")).asString();

	SoundEvents::TriggerRequestTrackDeserialization(SoundEvents::RequestTrackDeserializationArgs(trackSerializationKey, owner, [=](Track* track)
	{
		owner->addChild(track);

		track->play(GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyDelayProperty, Value(0.0f)).asFloat());
	}));
}
