#include "MusicDeserializer.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Music.h"
#include "Sound/MusicLayer.h"

using namespace cocos2d;

const std::string MusicDeserializer::MapKeyMusicProperty = "music";
const std::string MusicDeserializer::MapKeyDelayProperty = "delay";

MusicDeserializer* MusicDeserializer::create()
{
	MusicDeserializer* instance = new MusicDeserializer();

	instance->autorelease();

	return instance;
}

MusicDeserializer::MusicDeserializer() : super(MusicDeserializer::MapKeyMusicProperty)
{
}

MusicDeserializer::~MusicDeserializer()
{
}

void MusicDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyPropertyName, Value("")).asString();
	
	MusicLayer* newObject = MusicLayer::create(properties, name);
	float delay = GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyDelayProperty, Value(0.0f)).asFloat();
	Music* music = Music::create(GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyMusicProperty, Value("")).asString());

	newObject->addChild(music);

	music->play(true, delay);

	args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(newObject, args->layerIndex));
}
