#include "RegisterStateDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCTMXObjectGroup.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Maps/Backgrounds/Background.h"
#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

RegisterStateDeserializer* RegisterStateDeserializer::instance = nullptr;
const std::string RegisterStateDeserializer::MapKeyRegisterState = "register-state";
const std::string RegisterStateDeserializer::MapKeyRegisterEax = "eax";
const std::string RegisterStateDeserializer::MapKeyRegisterEbx = "ebx";
const std::string RegisterStateDeserializer::MapKeyRegisterEcx = "ecx";
const std::string RegisterStateDeserializer::MapKeyRegisterEdx = "edx";
const std::string RegisterStateDeserializer::MapKeyRegisterEdi = "edi";
const std::string RegisterStateDeserializer::MapKeyRegisterEsi = "esi";
const std::string RegisterStateDeserializer::MapKeyRegisterEbp = "ebp";
const std::string RegisterStateDeserializer::MapKeyRegisterEsp = "esp";
const std::string RegisterStateDeserializer::MapKeyRegisterEip = "eip";

void RegisterStateDeserializer::registerGlobalNode()
{
	if (RegisterStateDeserializer::instance == nullptr)
	{
		RegisterStateDeserializer::instance = new RegisterStateDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(RegisterStateDeserializer::instance);
	}
}

void RegisterStateDeserializer::initializeListeners()
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

void RegisterStateDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (GameUtils::getKeyOrDefault(properties, SerializableLayer::KeyType, Value("")).asString() != RegisterStateDeserializer::MapKeyRegisterState)
	{
		return;
	}

	args->handled = true;

	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEax, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEbx, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEcx, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEdx, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEdi, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEsi, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEbp, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEsp, Value(0)).asInt());
	RegisterState::setRegisterEax(GameUtils::getKeyOrDefault(properties, RegisterStateDeserializer::MapKeyRegisterEip, Value(0)).asInt());
}
