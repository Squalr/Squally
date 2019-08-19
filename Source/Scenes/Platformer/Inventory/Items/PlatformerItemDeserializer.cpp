#include "PlatformerItemDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Inventory/Item.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PlatformerItemDeserializer* PlatformerItemDeserializer::instance = nullptr;

PlatformerItemDeserializer* PlatformerItemDeserializer::getInstance()
{
	if (PlatformerItemDeserializer::instance == nullptr)
	{
		PlatformerItemDeserializer::instance = new PlatformerItemDeserializer();

		instance->autorelease();
	}

	return PlatformerItemDeserializer::instance;
}

void PlatformerItemDeserializer::registerGlobalNode()
{
	// Register this class globally so that it can always listen for events
	GlobalDirector::getInstance()->registerGlobalNode(PlatformerItemDeserializer::getInstance());
}

PlatformerItemDeserializer::PlatformerItemDeserializer()
{
	this->deserializers = std::map<std::string, std::function<Item*()>>();

	// Consumables
	this->deserializers[HealthPotion::SaveKeyHealthPotion] = [=]() { return (Item*)HealthPotion::create(); };
	this->deserializers[ManaPotion::SaveKeyManaPotion] = [=]() { return (Item*)ManaPotion::create(); };
	this->deserializers[SpeedRune::SaveKeySpeedRune] = [=]() { return (Item*)SpeedRune::create(); };

	// Axes
	this->deserializers[BlueAxe::SaveKeyBlueAxe] = [=]() { return (Item*)BlueAxe::create(); };

	// Swords
	this->deserializers[AshenBlade::SaveKeyAshenBlade] = [=]() { return (Item*)AshenBlade::create(); };
	this->deserializers[BattleSword::SaveKeyBattleSword] = [=]() { return (Item*)BattleSword::create(); };
	this->deserializers[BlueSword::SaveKeyBlueSword] = [=]() { return (Item*)BlueSword::create(); };
	this->deserializers[CandySword::SaveKeyCandySword] = [=]() { return (Item*)CandySword::create(); };
	this->deserializers[Cleaver::SaveKeyCleaver] = [=]() { return (Item*)Cleaver::create(); };
	this->deserializers[CrystalSword::SaveKeyCrystalSword] = [=]() { return (Item*)CrystalSword::create(); };
	this->deserializers[FangBlade::SaveKeyFangBlade] = [=]() { return (Item*)FangBlade::create(); };
	this->deserializers[GladiatorSword::SaveKeyGladiatorSword] = [=]() { return (Item*)GladiatorSword::create(); };
	this->deserializers[Gladius::SaveKeyGladius] = [=]() { return (Item*)Gladius::create(); };
	this->deserializers[Harbinger::SaveKeyHarbinger] = [=]() { return (Item*)Harbinger::create(); };
	this->deserializers[IronSword::SaveKeyIronSword] = [=]() { return (Item*)IronSword::create(); };
	this->deserializers[Katana::SaveKeyKatana] = [=]() { return (Item*)Katana::create(); };
	this->deserializers[MoonBlade::SaveKeyMoonBlade] = [=]() { return (Item*)MoonBlade::create(); };
	this->deserializers[Rapier::SaveKeyRapier] = [=]() { return (Item*)Rapier::create(); };
	this->deserializers[SteelSword::SaveKeySteelSword] = [=]() { return (Item*)SteelSword::create(); };
	this->deserializers[VikingSword::SaveKeyVikingSword] = [=]() { return (Item*)VikingSword::create(); };
	this->deserializers[WarCutlas::SaveKeyWarCutlas] = [=]() { return (Item*)WarCutlas::create(); };

	// Hats
	this->deserializers[SantaHat::SaveKeySantaHat] = [=]() { return (Item*)SantaHat::create(); };

	// Offhands
	this->deserializers[WoodenShield::SaveKeyWoodenShield] = [=]() { return (Item*)WoodenShield::create(); };
}

PlatformerItemDeserializer::~PlatformerItemDeserializer()
{
}

void PlatformerItemDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		InventoryEvents::EventRequestItemDeserialization,
		[=](EventCustom* eventCustom)
		{
			InventoryEvents::RequestItemDeserializationArgs* args = static_cast<InventoryEvents::RequestItemDeserializationArgs*>(eventCustom->getUserData());
			
			if (args != nullptr)
			{
				PlatformerItemDeserializer::deserialize(*args); 
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PlatformerItemDeserializer::deserialize(InventoryEvents::RequestItemDeserializationArgs args)
{
	std::string serializationKey = args.itemSerializationKey;

	if (args.onItemDeserializedCallback != nullptr && this->deserializers.find(serializationKey) != this->deserializers.end())
	{
		args.onItemDeserializedCallback(this->deserializers[serializationKey]());
	}
	else
	{
		CCLOG("Unknown item encountered: %s", serializationKey.c_str());
	}
}
