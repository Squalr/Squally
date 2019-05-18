#include "MusicDeserializer.h"

#include "cocos/2d/CCTMXObjectGroup.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/Music.h"
#include "Sound/MusicLayer.h"

using namespace cocos2d;

MusicDeserializer* MusicDeserializer::instance = nullptr;
const std::string MusicDeserializer::MapKeyDelayProperty = "delay";
const std::string MusicDeserializer::MapKeyMusicProperty = "music";

void MusicDeserializer::registerGlobalNode()
{
	if (MusicDeserializer::instance == nullptr)
	{
		MusicDeserializer::instance = new MusicDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MusicDeserializer::instance);
	}
}

void MusicDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::LayerDeserializationRequestArgs* args = static_cast<DeserializationEvents::LayerDeserializationRequestArgs*>(eventCustom->getUserData());
			
			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void MusicDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->objectGroup->getProperties();
	std::string name = GameUtils::getKeyOrDefault(properties, SerializableLayer::MapKeyPropertyName, Value("")).asString();

	if (GameUtils::getKeyOrDefault(properties, SerializableLayer::KeyType, Value("")).asString() != MusicDeserializer::MapKeyMusicProperty)
	{
		return;
	}
	
	MusicLayer* newObject = MusicLayer::create(properties, name);
	float delay = GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyDelayProperty, Value(0.0f)).asFloat();
	Music* music = Music::create(GameUtils::getKeyOrDefault(properties, MusicDeserializer::MapKeyMusicProperty, Value("")).asString());

	newObject->addChild(music);

	if (delay <= 0.0f)
	{
		music->play(true);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create([=]()
			{
				music->play(true);
			}),
			nullptr
		));
	}

	args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(newObject, args->objectGroup->layerIndex));
}
