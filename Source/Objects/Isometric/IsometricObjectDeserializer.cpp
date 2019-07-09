#include "IsometricObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Isometric/IsometricObjects.h"

using namespace cocos2d;

const std::string IsometricObjectDeserializer::KeyTypeIsometricObject = "iso_object";

IsometricObjectDeserializer* IsometricObjectDeserializer::create()
{
	IsometricObjectDeserializer* instance = new IsometricObjectDeserializer();

	instance->autorelease();

	return instance;
}

IsometricObjectDeserializer::IsometricObjectDeserializer() : super(IsometricObjectDeserializer::KeyTypeIsometricObject)
{
}

IsometricObjectDeserializer::~IsometricObjectDeserializer()
{
}

void IsometricObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	const std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();
	GameObject* newObject = nullptr;

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
	else if (StrUtils::isRegexMatch(name, ValueInitializer::MapKeyValueInitializerRegex))
	{
		newObject = ValueInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EaxPtrInitializer::MapKeyEaxPtrInitializerRegex))
	{
		newObject = EaxPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EbxPtrInitializer::MapKeyEbxPtrInitializerRegex))
	{
		newObject = EbxPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EcxPtrInitializer::MapKeyEcxPtrInitializerRegex))
	{
		newObject = EcxPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EdxPtrInitializer::MapKeyEdxPtrInitializerRegex))
	{
		newObject = EdxPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EdiPtrInitializer::MapKeyEdiPtrInitializerRegex))
	{
		newObject = EdiPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EsiPtrInitializer::MapKeyEsiPtrInitializerRegex))
	{
		newObject = EsiPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EbpPtrInitializer::MapKeyEbpPtrInitializerRegex))
	{
		newObject = EbpPtrInitializer::create(properties);
	}
	else if (StrUtils::isRegexMatch(name, EspPtrInitializer::MapKeyEspPtrInitializerRegex))
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
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newObject));
	}
}
