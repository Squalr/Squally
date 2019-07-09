#include "IsometricObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Isometric/IsometricObjects.h"

using namespace cocos2d;

const std::string IsometricObjectDeserializer::MapKeyTypeObject = "object";

IsometricObjectDeserializer* IsometricObjectDeserializer::create()
{
	IsometricObjectDeserializer* instance = new IsometricObjectDeserializer();

	instance->autorelease();

	return instance;
}

IsometricObjectDeserializer::IsometricObjectDeserializer() : super(IsometricObjectDeserializer::MapKeyTypeObject)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[CameraFocus::MapKeyCameraFocus] = [=](ValueMap properties) { return (GameObject*)CameraFocus::create(properties); };
	this->deserializers[CameraScrollTracker::MapKeyCameraScrollTracker] = [=](ValueMap properties) { return (GameObject*)CameraScrollTracker::create(properties); };
	this->deserializers[HexusArcade::MapKeyHexusArcade] = [=](ValueMap properties) { return (GameObject*)HexusArcade::create(properties); };
	this->deserializers[LevelNode::MapKeyLevelNode] = [=](ValueMap properties) { return (GameObject*)LevelNode::create(properties); };
	this->deserializers[MemoryGrid::MapKeyMemoryGrid] = [=](ValueMap properties) { return (GameObject*)MemoryGrid::create(properties); };
	this->deserializers[ExitCrystal::MapKeyExitCrystal] = [=](ValueMap properties) { return (GameObject*)ExitCrystal::create(properties); };
	this->deserializers[EaxInitializer::MapKeyEaxInitializer] = [=](ValueMap properties) { return (GameObject*)EaxInitializer::create(properties); };
	this->deserializers[EbxInitializer::MapKeyEbxInitializer] = [=](ValueMap properties) { return (GameObject*)EbxInitializer::create(properties); };
	this->deserializers[EcxInitializer::MapKeyEcxInitializer] = [=](ValueMap properties) { return (GameObject*)EcxInitializer::create(properties); };
	this->deserializers[EdxInitializer::MapKeyEdxInitializer] = [=](ValueMap properties) { return (GameObject*)EdxInitializer::create(properties); };
	this->deserializers[EdiInitializer::MapKeyEdiInitializer] = [=](ValueMap properties) { return (GameObject*)EdiInitializer::create(properties); };
	this->deserializers[EsiInitializer::MapKeyEsiInitializer] = [=](ValueMap properties) { return (GameObject*)EsiInitializer::create(properties); };
	this->deserializers[EbpInitializer::MapKeyEbpInitializer] = [=](ValueMap properties) { return (GameObject*)EbpInitializer::create(properties); };
	this->deserializers[EspInitializer::MapKeyEspInitializer] = [=](ValueMap properties) { return (GameObject*)EspInitializer::create(properties); };
	this->deserializers[EaxCrystal::MapKeyEaxCrystal] = [=](ValueMap properties) { return (GameObject*)EaxCrystal::create(properties); };
	this->deserializers[EbxCrystal::MapKeyEbxCrystal] = [=](ValueMap properties) { return (GameObject*)EbxCrystal::create(properties); };
	this->deserializers[EcxCrystal::MapKeyEcxCrystal] = [=](ValueMap properties) { return (GameObject*)EcxCrystal::create(properties); };
	this->deserializers[EdxCrystal::MapKeyEdxCrystal] = [=](ValueMap properties) { return (GameObject*)EdxCrystal::create(properties); };
	this->deserializers[EdiCrystal::MapKeyEdiCrystal] = [=](ValueMap properties) { return (GameObject*)EdiCrystal::create(properties); };
	this->deserializers[EsiCrystal::MapKeyEsiCrystal] = [=](ValueMap properties) { return (GameObject*)EsiCrystal::create(properties); };
	this->deserializers[EbpCrystal::MapKeyEbpCrystal] = [=](ValueMap properties) { return (GameObject*)EbpCrystal::create(properties); };
	this->deserializers[EspCrystal::MapKeyEspCrystal] = [=](ValueMap properties) { return (GameObject*)EspCrystal::create(properties); };
	this->deserializers[EaxJmp::MapKeyEaxJmp] = [=](ValueMap properties) { return (GameObject*)EaxJmp::create(properties); };
	this->deserializers[EbxJmp::MapKeyEbxJmp] = [=](ValueMap properties) { return (GameObject*)EbxJmp::create(properties); };
	this->deserializers[EcxJmp::MapKeyEcxJmp] = [=](ValueMap properties) { return (GameObject*)EcxJmp::create(properties); };
	this->deserializers[EdxJmp::MapKeyEdxJmp] = [=](ValueMap properties) { return (GameObject*)EdxJmp::create(properties); };
	this->deserializers[EdiJmp::MapKeyEdiJmp] = [=](ValueMap properties) { return (GameObject*)EdiJmp::create(properties); };
	this->deserializers[EsiJmp::MapKeyEsiJmp] = [=](ValueMap properties) { return (GameObject*)EsiJmp::create(properties); };
	this->deserializers[EbpJmp::MapKeyEbpJmp] = [=](ValueMap properties) { return (GameObject*)EbpJmp::create(properties); };
	this->deserializers[EspJmp::MapKeyEspJmp] = [=](ValueMap properties) { return (GameObject*)EspJmp::create(properties); };

	this->deserializers[EaxPtrJmp::MapKeyEaxPtrJmp] = [=](ValueMap properties) { return (GameObject*)EaxPtrJmp::create(properties); };
	this->deserializers[EbxPtrJmp::MapKeyEbxPtrJmp] = [=](ValueMap properties) { return (GameObject*)EbxPtrJmp::create(properties); };
	this->deserializers[EcxPtrJmp::MapKeyEcxPtrJmp] = [=](ValueMap properties) { return (GameObject*)EcxPtrJmp::create(properties); };
	this->deserializers[EdxPtrJmp::MapKeyEdxPtrJmp] = [=](ValueMap properties) { return (GameObject*)EdxPtrJmp::create(properties); };
	this->deserializers[EdiPtrJmp::MapKeyEdiPtrJmp] = [=](ValueMap properties) { return (GameObject*)EdiPtrJmp::create(properties); };
	this->deserializers[EsiPtrJmp::MapKeyEsiPtrJmp] = [=](ValueMap properties) { return (GameObject*)EsiPtrJmp::create(properties); };
	this->deserializers[EbpPtrJmp::MapKeyEbpPtrJmp] = [=](ValueMap properties) { return (GameObject*)EbpPtrJmp::create(properties); };
	this->deserializers[EspPtrJmp::MapKeyEspPtrJmp] = [=](ValueMap properties) { return (GameObject*)EspPtrJmp::create(properties); };
	
	// GG
	/*
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
	} */
}

IsometricObjectDeserializer::~IsometricObjectDeserializer()
{
}

void IsometricObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyPropertyName, Value("")).asString();

	if (this->deserializers.find(name) != this->deserializers.end())
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(this->deserializers[name](properties)));
	}
	else
	{
		CCLOG("Unknown object encountered: %s", name.c_str());
	}
}
