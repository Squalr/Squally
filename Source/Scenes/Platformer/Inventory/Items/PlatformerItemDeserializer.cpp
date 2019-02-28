#include "PlatformerItemDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Inventory/Item.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PlatformerItemDeserializer* PlatformerItemDeserializer::instance = nullptr;

void PlatformerItemDeserializer::registerGlobalNode()
{
	if (PlatformerItemDeserializer::instance == nullptr)
	{
		PlatformerItemDeserializer::instance = new PlatformerItemDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerItemDeserializer::instance);
	}
}

void PlatformerItemDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		InventoryEvents::RequestItemDeserializationEvent,
		[=](EventCustom* args) { PlatformerItemDeserializer::onDeserializationRequest(static_cast<InventoryEvents::RequestItemDeserializationArgs>(args->getUserData())); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PlatformerItemDeserializer::onDeserializationRequest(const InventoryEvents::RequestItemDeserializationArgs& args)
{
	Item* result = nullptr;
	std::string serializationKey = args.itemSerializationKey;

	if (serializationKey == HealthPotion::SaveKeyHealthPotion)
	{
		result = HealthPotion::create();
	}
	else if (serializationKey == ManaPotion::SaveKeyManaPotion)
	{
		result = ManaPotion::create();
	}
	else if (serializationKey == SpeedPotion::SaveKeySpeedPotion)
	{
		result = SpeedPotion::create();
	}
	else if (serializationKey == CrystalSword::SaveKeyCrystalSword)
	{
		result = CrystalSword::create();
	}

	if (result != nullptr && args.onItemDeserializedCallback != nullptr)
	{
		args.onItemDeserializedCallback(result);
	}
}
