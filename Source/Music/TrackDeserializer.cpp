#include "TrackDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Sound/Music.h"
#include "Engine/Utils/LogUtils.h"

#include "Music/Tracks.h"

using namespace cocos2d;

TrackDeserializer* TrackDeserializer::Instance = nullptr;

TrackDeserializer* TrackDeserializer::getInstance()
{
	if (TrackDeserializer::Instance == nullptr)
	{
		TrackDeserializer::Instance = new TrackDeserializer();

		Instance->autorelease();
	}

	return TrackDeserializer::Instance;
}

void TrackDeserializer::RegisterGlobalNode()
{
	// Register this class globally so that it can always listen for events
	GlobalDirector::getInstance()->RegisterGlobalNode(TrackDeserializer::getInstance());
}

TrackDeserializer::TrackDeserializer()
{
	this->deserializers[Heartbeat::TrackKey] = [=]() { return (Music*)Heartbeat::create(); };
	this->deserializers[Medieval::TrackKey] = [=]() { return (Music*)Medieval::create(); };
	this->deserializers[Medieval2::TrackKey] = [=]() { return (Music*)Medieval2::create(); };
	this->deserializers[Solace::TrackKey] = [=]() { return (Music*)Solace::create(); };
	this->deserializers[TrickOrTreat::TrackKey] = [=]() { return (Music*)TrickOrTreat::create(); };
	this->deserializers[WeWillGetThereTogether::TrackKey] = [=]() { return (Music*)WeWillGetThereTogether::create(); };
}

TrackDeserializer::~TrackDeserializer()
{
}

void TrackDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		SoundEvents::EventRequestMusicDeserialization,
		[=](EventCustom* eventCustom)
		{
			SoundEvents::RequestMusicDeserializationArgs* args = static_cast<SoundEvents::RequestMusicDeserializationArgs*>(eventCustom->getData());
			
			if (args != nullptr)
			{
				TrackDeserializer::deserialize(*args); 
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void TrackDeserializer::deserialize(SoundEvents::RequestMusicDeserializationArgs args)
{
	std::string serializationKey = args.MusicSerializationKey;

	if (args.onMusicDeserializedCallback != nullptr && this->deserializers.find(serializationKey) != this->deserializers.end())
	{
		args.onMusicDeserializedCallback(this->deserializers[serializationKey]());
	}
	else
	{
		LogUtils::logError("Unknown track encountered: " + serializationKey);
	}
}
