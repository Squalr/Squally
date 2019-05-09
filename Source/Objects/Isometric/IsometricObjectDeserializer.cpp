#include "IsometricObjectDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Isometric/IsometricObjects.h"

using namespace cocos2d;

IsometricObjectDeserializer* IsometricObjectDeserializer::instance = nullptr;
const std::string IsometricObjectDeserializer::KeyTypeIsometricObject = "iso_object";

void IsometricObjectDeserializer::registerGlobalNode()
{
	if (IsometricObjectDeserializer::instance == nullptr)
	{
		IsometricObjectDeserializer::instance = new IsometricObjectDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(IsometricObjectDeserializer::instance);
	}
}

void IsometricObjectDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::ObjectDeserializationRequestArgs* args = static_cast<DeserializationEvents::ObjectDeserializationRequestArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void IsometricObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricObjectDeserializer::KeyTypeIsometricObject)
	{
		ValueMap properties = args->properties;
		const std::string name = GameUtils::getKeyOrDefault(properties, SerializableObject::MapKeyName, Value("")).asString();
		SerializableObject* newObject = nullptr;

		if (name == HexusArcade::MapKeyHexusArcade)
		{
			newObject = HexusArcade::create(properties);
		}
		else if (name == LevelNode::MapKeyLevelNode)
		{
			newObject = LevelNode::create(properties);
		}
		else if (name == MemoryGrid::MapKeyMemoryGrid)
		{
			newObject = MemoryGrid::create(properties);
		}
		else if (name == ExitCrystal::MapKeyExitCrystal)
		{
			newObject = ExitCrystal::create(properties);
		}
		else if (name == EaxInitializer::MapKeyEaxInitializer)
		{
			newObject = EaxInitializer::create(properties);
		}
		else if (name == EbxInitializer::MapKeyEbxInitializer)
		{
			newObject = EbxInitializer::create(properties);
		}
		else if (name == EcxInitializer::MapKeyEcxInitializer)
		{
			newObject = EcxInitializer::create(properties);
		}
		else if (name == EdxInitializer::MapKeyEdxInitializer)
		{
			newObject = EdxInitializer::create(properties);
		}
		else if (name == EdiInitializer::MapKeyEdiInitializer)
		{
			newObject = EdiInitializer::create(properties);
		}
		else if (name == EsiInitializer::MapKeyEsiInitializer)
		{
			newObject = EsiInitializer::create(properties);
		}
		else if (name == EbpInitializer::MapKeyEbpInitializer)
		{
			newObject = EbpInitializer::create(properties);
		}
		else if (name == EspInitializer::MapKeyEspInitializer)
		{
			newObject = EspInitializer::create(properties);
		}
		else if (name == EaxCrystal::MapKeyEaxCrystal)
		{
			newObject = EaxCrystal::create(properties);
		}
		else if (name == EbxCrystal::MapKeyEbxCrystal)
		{
			newObject = EbxCrystal::create(properties);
		}
		else if (name == EcxCrystal::MapKeyEcxCrystal)
		{
			newObject = EcxCrystal::create(properties);
		}
		else if (name == EdxCrystal::MapKeyEdxCrystal)
		{
			newObject = EdxCrystal::create(properties);
		}
		else if (name == EdiCrystal::MapKeyEdiCrystal)
		{
			newObject = EdiCrystal::create(properties);
		}
		else if (name == EsiCrystal::MapKeyEsiCrystal)
		{
			newObject = EsiCrystal::create(properties);
		}
		else if (name == EbpCrystal::MapKeyEbpCrystal)
		{
			newObject = EbpCrystal::create(properties);
		}
		else if (name == EspCrystal::MapKeyEspCrystal)
		{
			newObject = EspCrystal::create(properties);
		}
		else if (name == EaxJmp::MapKeyEaxJmp)
		{
			newObject = EaxJmp::create(properties);
		}
		else if (name == EbxJmp::MapKeyEbxJmp)
		{
			newObject = EbxJmp::create(properties);
		}
		else if (name == EcxJmp::MapKeyEcxJmp)
		{
			newObject = EcxJmp::create(properties);
		}
		else if (name == EdxJmp::MapKeyEdxJmp)
		{
			newObject = EdxJmp::create(properties);
		}
		else if (name == EdiJmp::MapKeyEdiJmp)
		{
			newObject = EdiJmp::create(properties);
		}
		else if (name == EsiJmp::MapKeyEsiJmp)
		{
			newObject = EsiJmp::create(properties);
		}
		else if (name == EbpJmp::MapKeyEbpJmp)
		{
			newObject = EbpJmp::create(properties);
		}
		else if (name == EspJmp::MapKeyEspJmp)
		{
			newObject = EspJmp::create(properties);
		}
		else if (name == EaxPtrJmp::MapKeyEaxPtrJmp)
		{
			newObject = EaxPtrJmp::create(properties);
		}
		else if (name == EbxPtrJmp::MapKeyEbxPtrJmp)
		{
			newObject = EbxPtrJmp::create(properties);
		}
		else if (name == EcxPtrJmp::MapKeyEcxPtrJmp)
		{
			newObject = EcxPtrJmp::create(properties);
		}
		else if (name == EdxPtrJmp::MapKeyEdxPtrJmp)
		{
			newObject = EdxPtrJmp::create(properties);
		}
		else if (name == EdiPtrJmp::MapKeyEdiPtrJmp)
		{
			newObject = EdiPtrJmp::create(properties);
		}
		else if (name == EsiPtrJmp::MapKeyEsiPtrJmp)
		{
			newObject = EsiPtrJmp::create(properties);
		}
		else if (name == EbpPtrJmp::MapKeyEbpPtrJmp)
		{
			newObject = EbpPtrJmp::create(properties);
		}
		else if (name == EspPtrJmp::MapKeyEspPtrJmp)
		{
			newObject = EspPtrJmp::create(properties);
		}
		else if (StrUtils::startsWith(name, ValueInitializer::MapKeyValueInitializerPrefix, false))
		{
			newObject = ValueInitializer::create(properties);
		}
		else if (name == EaxPtrInitializer::MapKeyEaxPtrInitializer)
		{
			newObject = EaxPtrInitializer::create(properties);
		}
		else if (name == EbxPtrInitializer::MapKeyEbxPtrInitializer)
		{
			newObject = EbxPtrInitializer::create(properties);
		}
		else if (name == EcxPtrInitializer::MapKeyEcxPtrInitializer)
		{
			newObject = EcxPtrInitializer::create(properties);
		}
		else if (name == EdxPtrInitializer::MapKeyEdxPtrInitializer)
		{
			newObject = EdxPtrInitializer::create(properties);
		}
		else if (name == EdiPtrInitializer::MapKeyEdiPtrInitializer)
		{
			newObject = EdiPtrInitializer::create(properties);
		}
		else if (name == EsiPtrInitializer::MapKeyEsiPtrInitializer)
		{
			newObject = EsiPtrInitializer::create(properties);
		}
		else if (name == EbpPtrInitializer::MapKeyEbpPtrInitializer)
		{
			newObject = EbpPtrInitializer::create(properties);
		}
		else if (name == EspPtrInitializer::MapKeyEspPtrInitializer)
		{
			newObject = EspPtrInitializer::create(properties);
		}
		else
		{
			CCLOG("Missing properties on isometric object");
			return;
		}

		if (newObject != nullptr)
		{
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newObject));
		}
	}
}
