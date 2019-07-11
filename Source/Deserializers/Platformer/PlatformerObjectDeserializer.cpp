#include "PlatformerObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

const std::string PlatformerObjectDeserializer::MapKeyTypeObject = "object";

PlatformerObjectDeserializer* PlatformerObjectDeserializer::create()
{
	PlatformerObjectDeserializer* instance = new PlatformerObjectDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerObjectDeserializer::PlatformerObjectDeserializer() : super(PlatformerObjectDeserializer::MapKeyTypeObject)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[CameraFocus::MapKeyCameraFocus] = [=](ValueMap properties) { return (GameObject*)CameraFocus::create(properties); };
	this->deserializers[CameraScrollTracker::MapKeyCameraScrollTracker] = [=](ValueMap properties) { return (GameObject*)CameraScrollTracker::create(properties); };
	this->deserializers[CastleDoor::MapKeyCastleDoor] = [=](ValueMap properties) { return (GameObject*)CastleDoor::create(properties); };
	this->deserializers[CombatSpawn::MapKeyCombatSpawn] = [=](ValueMap properties) { return (GameObject*)CombatSpawn::create(properties); };
	this->deserializers[CastleDoorFront::MapKeyCastleDoorFront] = [=](ValueMap properties) { return (GameObject*)CastleDoorFront::create(properties); };
	this->deserializers[Catapult::MapKeyCatapult] = [=](ValueMap properties) { return (GameObject*)Catapult::create(properties); };
	this->deserializers[Chest::MapKeyChest] = [=](ValueMap properties) { return (GameObject*)Chest::create(properties); };
	this->deserializers[CinematicMarker::MapKeyCinematicMarker] = [=](ValueMap properties) { return (GameObject*)CinematicMarker::create(properties); };
	this->deserializers[DartGun::MapKeyDartGun] = [=](ValueMap properties) { return (GameObject*)DartGun::create(properties); };
	this->deserializers[Doubloon::MapKeyDoubloon] = [=](ValueMap properties) { return (GameObject*)Doubloon::create(properties); };
	this->deserializers[EdgePortal::MapKeyEdgePortal] = [=](ValueMap properties) { return (GameObject*)EdgePortal::create(properties); };
	this->deserializers[FloatingAsteroid::MapKeyFloatingAsteroid] = [=](ValueMap properties) { return (GameObject*)FloatingAsteroid::create(properties); };
	this->deserializers[FloatingBomb::MapKeyFloatingBomb] = [=](ValueMap properties) { return (GameObject*)FloatingBomb::create(properties); };
	this->deserializers[FloatingCrate::MapKeyFloatingCrate] = [=](ValueMap properties) { return (GameObject*)FloatingCrate::create(properties); };
	this->deserializers[FloatingRock::MapKeyFloatingRock] = [=](ValueMap properties) { return (GameObject*)FloatingRock::create(properties); };
	this->deserializers[FloatingWoodenBeam::MapKeyFloatingWoodenBeam] = [=](ValueMap properties) { return (GameObject*)FloatingWoodenBeam::create(properties); };
	this->deserializers[HackableHint::MapKeyHackableHint] = [=](ValueMap properties) { return (GameObject*)HackableHint::create(properties); };
	this->deserializers[HeavenHug::MapKeyHeavenHug] = [=](ValueMap properties) { return (GameObject*)HeavenHug::create(properties); };
	this->deserializers[Laser::MapKeyLaser] = [=](ValueMap properties) { return (GameObject*)Laser::create(properties); };
	this->deserializers[MetalSpikes::MapKeyMetalSpikes] = [=](ValueMap properties) { return (GameObject*)MetalSpikes::create(properties); };
	this->deserializers[MechanicalFlail::MapKeyMechanicalFlail] = [=](ValueMap properties) { return (GameObject*)MechanicalFlail::create(properties); };
	this->deserializers[Monkey::MapKeyMonkey] = [=](ValueMap properties) { return (GameObject*)Monkey::create(properties); };
	this->deserializers[MulDoor::MapKeyMulDoor] = [=](ValueMap properties) { return (GameObject*)MulDoor::create(properties); };
	this->deserializers[PendulumBlade::MapKeyPendulumBlade] = [=](ValueMap properties) { return (GameObject*)PendulumBlade::create(properties); };
	this->deserializers[SpikedBall::MapKeySpikedBall] = [=](ValueMap properties) { return (GameObject*)SpikedBall::create(properties); };
	this->deserializers[SpikeLog::MapKeySpikeLog] = [=](ValueMap properties) { return (GameObject*)SpikeLog::create(properties); };
	this->deserializers[SquallyShip::MapKeySquallyShip] = [=](ValueMap properties) { return (GameObject*)SquallyShip::create(properties); };
	this->deserializers[StoneButton::MapKeyStoneButton] = [=](ValueMap properties) { return (GameObject*)StoneButton::create(properties); };
	this->deserializers[Tent::MapKeyTent] = [=](ValueMap properties) { return (GameObject*)Tent::create(properties); };
	this->deserializers[TrapDoor::MapKeyTrapDoor] = [=](ValueMap properties) { return (GameObject*)TrapDoor::create(properties); };
	this->deserializers[TrapDoorFrame::MapKeyTrapDoorFrame] = [=](ValueMap properties) { return (GameObject*)TrapDoorFrame::create(properties); };
	this->deserializers[Trigger::MapKeyTrigger] = [=](ValueMap properties) { return (GameObject*)Trigger::create(properties); };
	this->deserializers[Water::MapKeyWater] = [=](ValueMap properties) { return (GameObject*)Water::create(properties); };
	this->deserializers[Wind::MapKeyWind] = [=](ValueMap properties) { return (GameObject*)Wind::create(properties); };
	this->deserializers[WoodenCrate::MapKeyWoodenCrate] = [=](ValueMap properties) { return (GameObject*)WoodenCrate::create(properties); };
	this->deserializers[WoodenSpikes::MapKeyWoodenSpikes] = [=](ValueMap properties) { return (GameObject*)WoodenSpikes::create(properties); };
}

PlatformerObjectDeserializer::~PlatformerObjectDeserializer()
{
}

void PlatformerObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
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
