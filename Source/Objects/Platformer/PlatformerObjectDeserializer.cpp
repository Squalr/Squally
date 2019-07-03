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

PlatformerObjectDeserializer::PlatformerObjectDeserializer()
{
	this->deserializers = std::map<std::string, std::function<SerializableObject*(ValueMap)>>();

	this->deserializers[CastleDoor::MapKeyCastleDoor] = [=](ValueMap properties) { return (SerializableObject*)CastleDoor::create(properties); };
	this->deserializers[CrystalPuzzle::MapKeyCrystalPuzzle] = [=](ValueMap properties) { return (SerializableObject*)CrystalPuzzle::create(properties); };
	this->deserializers[CombatSpawn::MapKeyCombatSpawn] = [=](ValueMap properties) { return (SerializableObject*)CombatSpawn::create(properties); };
	this->deserializers[CastleDoorFront::MapKeyCastleDoorFront] = [=](ValueMap properties) { return (SerializableObject*)CastleDoorFront::create(properties); };
	this->deserializers[Catapult::MapKeyCatapult] = [=](ValueMap properties) { return (SerializableObject*)Catapult::create(properties); };
	this->deserializers[Chest::MapKeyChest] = [=](ValueMap properties) { return (SerializableObject*)Chest::create(properties); };
	this->deserializers[CinematicMarker::MapKeyCinematicMarker] = [=](ValueMap properties) { return (SerializableObject*)CinematicMarker::create(properties); };
	this->deserializers[DartGun::MapKeyDartGun] = [=](ValueMap properties) { return (SerializableObject*)DartGun::create(properties); };
	this->deserializers[Doubloon::MapKeyDoubloon] = [=](ValueMap properties) { return (SerializableObject*)Doubloon::create(properties); };
	this->deserializers[EdgePortal::MapKeyEdgePortal] = [=](ValueMap properties) { return (SerializableObject*)EdgePortal::create(properties); };
	this->deserializers[FloatingAsteroid::MapKeyFloatingAsteroid] = [=](ValueMap properties) { return (SerializableObject*)FloatingAsteroid::create(properties); };
	this->deserializers[FloatingBomb::MapKeyFloatingBomb] = [=](ValueMap properties) { return (SerializableObject*)FloatingBomb::create(properties); };
	this->deserializers[FloatingCrate::MapKeyFloatingCrate] = [=](ValueMap properties) { return (SerializableObject*)FloatingCrate::create(properties); };
	this->deserializers[FloatingRock::MapKeyFloatingRock] = [=](ValueMap properties) { return (SerializableObject*)FloatingRock::create(properties); };
	this->deserializers[FloatingWoodenBeam::MapKeyFloatingWoodenBeam] = [=](ValueMap properties) { return (SerializableObject*)FloatingWoodenBeam::create(properties); };
	this->deserializers[HackableHint::MapKeyHackableHint] = [=](ValueMap properties) { return (SerializableObject*)HackableHint::create(properties); };
	this->deserializers[HeavenHug::MapKeyHeavenHug] = [=](ValueMap properties) { return (SerializableObject*)HeavenHug::create(properties); };
	this->deserializers[Laser::MapKeyLaser] = [=](ValueMap properties) { return (SerializableObject*)Laser::create(properties); };
	this->deserializers[MetalSpikes::MapKeyMetalSpikes] = [=](ValueMap properties) { return (SerializableObject*)MetalSpikes::create(properties); };
	this->deserializers[WoodenSpikes::MapKeyWoodenSpikes] = [=](ValueMap properties) { return (SerializableObject*)WoodenSpikes::create(properties); };
	this->deserializers[MechanicalFlail::MapKeyMechanicalFlail] = [=](ValueMap properties) { return (SerializableObject*)MechanicalFlail::create(properties); };
	this->deserializers[PendulumBlade::MapKeyPendulumBlade] = [=](ValueMap properties) { return (SerializableObject*)PendulumBlade::create(properties); };
	this->deserializers[SpikedBall::MapKeySpikedBall] = [=](ValueMap properties) { return (SerializableObject*)SpikedBall::create(properties); };
	this->deserializers[SpikeLog::MapKeySpikeLog] = [=](ValueMap properties) { return (SerializableObject*)SpikeLog::create(properties); };
	this->deserializers[SquallyShip::MapKeySquallyShip] = [=](ValueMap properties) { return (SerializableObject*)SquallyShip::create(properties); };
	this->deserializers[Monkey::MapKeyMonkey] = [=](ValueMap properties) { return (SerializableObject*)Monkey::create(properties); };
	this->deserializers[StoneButton::MapKeyStoneButton] = [=](ValueMap properties) { return (SerializableObject*)StoneButton::create(properties); };
	this->deserializers[Tent::MapKeyTent] = [=](ValueMap properties) { return (SerializableObject*)Tent::create(properties); };
	this->deserializers[TrapDoor::MapKeyTrapDoor] = [=](ValueMap properties) { return (SerializableObject*)TrapDoor::create(properties); };
	this->deserializers[TrapDoorFrame::MapKeyTrapDoorFrame] = [=](ValueMap properties) { return (SerializableObject*)TrapDoorFrame::create(properties); };
	this->deserializers[Trigger::MapKeyTrigger] = [=](ValueMap properties) { return (SerializableObject*)Trigger::create(properties); };
	this->deserializers[Water::MapKeyWater] = [=](ValueMap properties) { return (SerializableObject*)Water::create(properties); };
	this->deserializers[WoodenCrate::MapKeyWoodenCrate] = [=](ValueMap properties) { return (SerializableObject*)WoodenCrate::create(properties); };
	this->deserializers[Wind::MapKeyWind] = [=](ValueMap properties) { return (SerializableObject*)Wind::create(properties); };
}

PlatformerObjectDeserializer::~PlatformerObjectDeserializer()
{
}

void PlatformerObjectDeserializer::initializeListeners()
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

void PlatformerObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerObjectDeserializer::KeyTypeObject)
	{
		std::string name = args->properties.at(SerializableObject::MapKeyName).asString();

		if (this->deserializers.find(name) != this->deserializers.end())
		{
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(this->deserializers[name](args->properties)));
		}
		else
		{
			CCLOG("Unknown object encountered: %s", name.c_str());
		}
	}
}
