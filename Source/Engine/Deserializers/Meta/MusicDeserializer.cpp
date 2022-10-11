#include "MusicDeserializer.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Sound/Music.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MusicDeserializer::MapKey = "music";
const std::string MusicDeserializer::MapKeyDelayProperty = "music-delay";

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
	std::string MusicSerializationKey = GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKey, Value("")).asString();

	SoundEvents::TriggerRequestMusicDeserialization(SoundEvents::RequestMusicDeserializationArgs(MusicSerializationKey, [=](Music* music)
	{
		owner->addChild(music);

		music->pushTrack(GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyDelayProperty, Value(0.5f)).asFloat());
	}));
}
