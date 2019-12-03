#include "MusicDeserializer.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
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
	Music* music = Music::createAndAddGlobally(GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyMusicProperty, Value("")).asString(), owner);
	float delay = GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyDelayProperty, Value(0.0f)).asFloat();

	MusicPlayer::play(music, true, delay);
}
