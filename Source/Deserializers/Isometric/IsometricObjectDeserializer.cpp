#include "IsometricObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
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

	this->deserializers[CameraFocus::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraFocus::create(properties); };
	this->deserializers[CameraScrollTracker::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraScrollTracker::create(properties); };
	this->deserializers[LevelNode::MapKey] = [=](ValueMap properties) { return (GameObject*)LevelNode::create(properties); };
	this->deserializers[MemoryGrid::MapKey] = [=](ValueMap properties) { return (GameObject*)MemoryGrid::create(properties); };
	this->deserializers[ExitCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)ExitCrystal::create(properties); };
	this->deserializers[EaxInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EaxInitializer::create(properties); };
	this->deserializers[EbxInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EbxInitializer::create(properties); };
	this->deserializers[EcxInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EcxInitializer::create(properties); };
	this->deserializers[EdxInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EdxInitializer::create(properties); };
	this->deserializers[EdiInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EdiInitializer::create(properties); };
	this->deserializers[EsiInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EsiInitializer::create(properties); };
	this->deserializers[EbpInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EbpInitializer::create(properties); };
	this->deserializers[EspInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EspInitializer::create(properties); };
	this->deserializers[EaxCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EaxCrystal::create(properties); };
	this->deserializers[EbxCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EbxCrystal::create(properties); };
	this->deserializers[EcxCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EcxCrystal::create(properties); };
	this->deserializers[EdxCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EdxCrystal::create(properties); };
	this->deserializers[EdiCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EdiCrystal::create(properties); };
	this->deserializers[EsiCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EsiCrystal::create(properties); };
	this->deserializers[EbpCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EbpCrystal::create(properties); };
	this->deserializers[EspCrystal::MapKey] = [=](ValueMap properties) { return (GameObject*)EspCrystal::create(properties); };
	this->deserializers[EaxJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EaxJmp::create(properties); };
	this->deserializers[EbxJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EbxJmp::create(properties); };
	this->deserializers[EcxJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EcxJmp::create(properties); };
	this->deserializers[EdxJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EdxJmp::create(properties); };
	this->deserializers[EdiJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EdiJmp::create(properties); };
	this->deserializers[EsiJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EsiJmp::create(properties); };
	this->deserializers[EbpJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EbpJmp::create(properties); };
	this->deserializers[EspJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EspJmp::create(properties); };

	this->deserializers[EaxPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EaxPtrJmp::create(properties); };
	this->deserializers[EbxPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EbxPtrJmp::create(properties); };
	this->deserializers[EcxPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EcxPtrJmp::create(properties); };
	this->deserializers[EdxPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EdxPtrJmp::create(properties); };
	this->deserializers[EdiPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EdiPtrJmp::create(properties); };
	this->deserializers[EsiPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EsiPtrJmp::create(properties); };
	this->deserializers[EbpPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EbpPtrJmp::create(properties); };
	this->deserializers[EspPtrJmp::MapKey] = [=](ValueMap properties) { return (GameObject*)EspPtrJmp::create(properties); };
	
	this->deserializers[EaxPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EaxPtrInitializer::create(properties); };
	this->deserializers[EbxPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EbxPtrInitializer::create(properties); };
	this->deserializers[EcxPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EcxPtrInitializer::create(properties); };
	this->deserializers[EdxPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EdxPtrInitializer::create(properties); };
	this->deserializers[EdiPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EdiPtrInitializer::create(properties); };
	this->deserializers[EsiPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EsiPtrInitializer::create(properties); };
	this->deserializers[EbpPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EbpPtrInitializer::create(properties); };
	this->deserializers[EspPtrInitializer::MapKey] = [=](ValueMap properties) { return (GameObject*)EspPtrInitializer::create(properties); };
	
	// Create deserializers for variable-named objects (ie value-212 and value 256)
	for (int index = 0; index < 256; index++)
	{
		std::string indexStr = std::to_string(index);
		
		auto assignKey([=](std::string str, std::function<GameObject*(ValueMap properties)> deserializer)
		{
			std::string key = StrUtils::replaceFirstOccurence(str, "%d", indexStr);

			this->deserializers[key] = deserializer;
		});
		
		auto assignKeys([=](std::vector<std::string> strs, std::function<GameObject*(ValueMap properties)> deserializer)
		{
			for (auto str : strs)
			{
				assignKey(str, deserializer);
			}
		});

		assignKey(ValueInitializer::MapKeyBase, [=](ValueMap properties) { return (GameObject*)ValueInitializer::create(properties); });
		assignKeys(EaxPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EaxPtrInitializer::create(properties); });
		assignKeys(EbxPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EbxPtrInitializer::create(properties); });
		assignKeys(EcxPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EcxPtrInitializer::create(properties); });
		assignKeys(EdxPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EdxPtrInitializer::create(properties); });
		assignKeys(EdiPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EdiPtrInitializer::create(properties); });
		assignKeys(EsiPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EsiPtrInitializer::create(properties); });
		assignKeys(EbpPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EbpPtrInitializer::create(properties); });
		assignKeys(EspPtrInitializer::MapKeyBases, [=](ValueMap properties) { return (GameObject*)EspPtrInitializer::create(properties); });
	}
}

IsometricObjectDeserializer::~IsometricObjectDeserializer()
{
}
