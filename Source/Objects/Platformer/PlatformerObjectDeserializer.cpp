#include "PlatformerObjectDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

PlatformerObjectDeserializer* PlatformerObjectDeserializer::instance = nullptr;
const std::string PlatformerObjectDeserializer::KeyTypeObject = "object";

void PlatformerObjectDeserializer::registerGlobalNode()
{
	if (PlatformerObjectDeserializer::instance == nullptr)
	{
		PlatformerObjectDeserializer::instance = new PlatformerObjectDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerObjectDeserializer::instance);
	}
}

void PlatformerObjectDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PlatformerObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerObjectDeserializer::KeyTypeObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();
		SerializableObject* newObject = nullptr;

		if (name == CameraFocus::MapKeyCameraFocus)
		{
			newObject = CameraFocus::create(&properties);
		}
		else if (name == DartGun::MapKeyDartGun)
		{
			newObject = DartGun::create(&properties);
		}
		else if (name == HeavenHug::MapKeyHeavenHug)
		{
			newObject = HeavenHug::create(&properties);
		}
		else if (name == MetalSpikes::MapKeyMetalSpikes)
		{
			newObject = MetalSpikes::create(&properties);
		}
		else if (name == MechanicalFlail::MapKeyMechanicalFlail)
		{
			newObject = MechanicalFlail::create(&properties);
		}
		else if (name == PendulumBlade::MapKeyPendulumBlade)
		{
			newObject = PendulumBlade::create(&properties);
		}
		else if (name == SpikeLog::MapKeySpikeLog)
		{
			newObject = SpikeLog::create(&properties);
		}
		else if (name == PlushieMonkey::MapKeyPlushieMonkey)
		{
			newObject = PlushieMonkey::create(&properties);
		}
		else if (name == Monitor::MapKeyMonitor)
		{
			newObject = Monitor::create(&properties);
		}
		else if (name == Wind::MapKeyWind)
		{
			newObject = Wind::create(&properties);
		}
		else
		{
			CCLOG("Missing properties on platformer object");
			return;
		}

		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newObject));
	}
}
