#include "MusicDeserializer.h"

#include "cocos/2d/CCTMXObjectGroup.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Sound/SoundManager.h"

using namespace cocos2d;

MusicDeserializer* MusicDeserializer::instance = nullptr;
const std::string MusicDeserializer::KeyMusicProperty = "music";

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

	if (GameUtils::getKeyOrDefault(properties, SerializableLayer::KeyType, Value("")).asString() != MusicDeserializer::KeyMusicProperty)
	{
		return;
	}

	SoundManager::playMusicResource(GameUtils::getKeyOrDefault(properties, SerializableLayer::KeyType, Value("")).asString());
}
