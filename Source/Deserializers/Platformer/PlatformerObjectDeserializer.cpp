#include "PlatformerObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Quests/QuestTask.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

const std::string PlatformerObjectDeserializer::MapKeyTypeObject = "object";

PlatformerObjectDeserializer* PlatformerObjectDeserializer::create()
{
	PlatformerObjectDeserializer* instance = new PlatformerObjectDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerObjectDeserializer::PlatformerObjectDeserializer() : super(PlatformerObjectDeserializer::MapKeyTypeObject, { (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[AddDoor::MapKeyAddDoor] = [=](ValueMap properties) { return (GameObject*)AddDoor::create(properties); };
	this->deserializers[Anvil::MapKeyAnvil] = [=](ValueMap properties) { return (GameObject*)Anvil::create(properties); };
	this->deserializers[BreakableBarrel::MapKeyBreakableBarrel] = [=](ValueMap properties) { return (GameObject*)BreakableBarrel::create(properties); };
	this->deserializers[BreakableCage::MapKeyBreakableCage] = [=](ValueMap properties) { return (GameObject*)BreakableCage::create(properties); };
	this->deserializers[CagedBat::MapKeyCagedBat] = [=](ValueMap properties) { return (GameObject*)CagedBat::create(properties); };
	this->deserializers[CagedBear::MapKeyCagedBear] = [=](ValueMap properties) { return (GameObject*)CagedBear::create(properties); };
	this->deserializers[CagedBeaver::MapKeyCagedBeaver] = [=](ValueMap properties) { return (GameObject*)CagedBeaver::create(properties); };
	this->deserializers[CagedBee::MapKeyCagedBee] = [=](ValueMap properties) { return (GameObject*)CagedBee::create(properties); };
	this->deserializers[CagedBird::MapKeyCagedBird] = [=](ValueMap properties) { return (GameObject*)CagedBird::create(properties); };
	this->deserializers[CagedBlowfish::MapKeyCagedBlowfish] = [=](ValueMap properties) { return (GameObject*)CagedBlowfish::create(properties); };
	this->deserializers[CagedBull::MapKeyCagedBull] = [=](ValueMap properties) { return (GameObject*)CagedBull::create(properties); };
	this->deserializers[CagedBunny::MapKeyCagedBunny] = [=](ValueMap properties) { return (GameObject*)CagedBunny::create(properties); };
	this->deserializers[CagedCat::MapKeyCagedCat] = [=](ValueMap properties) { return (GameObject*)CagedCat::create(properties); };
	this->deserializers[CagedChicken::MapKeyCagedChicken] = [=](ValueMap properties) { return (GameObject*)CagedChicken::create(properties); };
	this->deserializers[CagedCow::MapKeyCagedCow] = [=](ValueMap properties) { return (GameObject*)CagedCow::create(properties); };
	this->deserializers[CagedCrocodile::MapKeyCagedCrocodile] = [=](ValueMap properties) { return (GameObject*)CagedCrocodile::create(properties); };
	this->deserializers[CagedDinosaur::MapKeyCagedDinosaur] = [=](ValueMap properties) { return (GameObject*)CagedDinosaur::create(properties); };
	this->deserializers[CagedDog::MapKeyCagedDog] = [=](ValueMap properties) { return (GameObject*)CagedDog::create(properties); };
	this->deserializers[CagedDuck::MapKeyCagedDuck] = [=](ValueMap properties) { return (GameObject*)CagedDuck::create(properties); };
	this->deserializers[CagedFox::MapKeyCagedFox] = [=](ValueMap properties) { return (GameObject*)CagedFox::create(properties); };
	this->deserializers[CagedGiraffe::MapKeyCagedGiraffe] = [=](ValueMap properties) { return (GameObject*)CagedGiraffe::create(properties); };
	this->deserializers[CagedGoat::MapKeyCagedGoat] = [=](ValueMap properties) { return (GameObject*)CagedGoat::create(properties); };
	this->deserializers[CagedHedgehog::MapKeyCagedHedgehog] = [=](ValueMap properties) { return (GameObject*)CagedHedgehog::create(properties); };
	this->deserializers[CagedHippo::MapKeyCagedHippo] = [=](ValueMap properties) { return (GameObject*)CagedHippo::create(properties); };
	this->deserializers[CagedHorse::MapKeyCagedHorse] = [=](ValueMap properties) { return (GameObject*)CagedHorse::create(properties); };
	this->deserializers[CagedKillerWhale::MapKeyCagedKillerWhale] = [=](ValueMap properties) { return (GameObject*)CagedKillerWhale::create(properties); };
	this->deserializers[CagedKoala::MapKeyCagedKoala] = [=](ValueMap properties) { return (GameObject*)CagedKoala::create(properties); };
	this->deserializers[CagedLadybug::MapKeyCagedLadybug] = [=](ValueMap properties) { return (GameObject*)CagedLadybug::create(properties); };
	this->deserializers[CagedLion::MapKeyCagedLion] = [=](ValueMap properties) { return (GameObject*)CagedLion::create(properties); };
	this->deserializers[CagedLizard::MapKeyCagedLizard] = [=](ValueMap properties) { return (GameObject*)CagedLizard::create(properties); };
	this->deserializers[CagedMonkey::MapKeyCagedMonkey] = [=](ValueMap properties) { return (GameObject*)CagedMonkey::create(properties); };
	this->deserializers[CagedMountainLion::MapKeyCagedMountainLion] = [=](ValueMap properties) { return (GameObject*)CagedMountainLion::create(properties); };
	this->deserializers[CagedMouse::MapKeyCagedMouse] = [=](ValueMap properties) { return (GameObject*)CagedMouse::create(properties); };
	this->deserializers[CagedPanda::MapKeyCagedPanda] = [=](ValueMap properties) { return (GameObject*)CagedPanda::create(properties); };
	this->deserializers[CagedParrot::MapKeyCagedParrot] = [=](ValueMap properties) { return (GameObject*)CagedParrot::create(properties); };
	this->deserializers[CagedPenguin::MapKeyCagedPenguin] = [=](ValueMap properties) { return (GameObject*)CagedPenguin::create(properties); };
	this->deserializers[CagedPig::MapKeyCagedPig] = [=](ValueMap properties) { return (GameObject*)CagedPig::create(properties); };
	this->deserializers[CagedRaccoon::MapKeyCagedRaccoon] = [=](ValueMap properties) { return (GameObject*)CagedRaccoon::create(properties); };
	this->deserializers[CagedReindeer::MapKeyCagedReindeer] = [=](ValueMap properties) { return (GameObject*)CagedReindeer::create(properties); };
	this->deserializers[CagedRhino::MapKeyCagedRhino] = [=](ValueMap properties) { return (GameObject*)CagedRhino::create(properties); };
	this->deserializers[CagedSheep::MapKeyCagedSheep] = [=](ValueMap properties) { return (GameObject*)CagedSheep::create(properties); };
	this->deserializers[CagedSkunk::MapKeyCagedSkunk] = [=](ValueMap properties) { return (GameObject*)CagedSkunk::create(properties); };
	this->deserializers[CagedSnail::MapKeyCagedSnail] = [=](ValueMap properties) { return (GameObject*)CagedSnail::create(properties); };
	this->deserializers[CagedSnake::MapKeyCagedSnake] = [=](ValueMap properties) { return (GameObject*)CagedSnake::create(properties); };
	this->deserializers[CagedSquid::MapKeyCagedSquid] = [=](ValueMap properties) { return (GameObject*)CagedSquid::create(properties); };
	this->deserializers[CagedSquirrel::MapKeyCagedSquirrel] = [=](ValueMap properties) { return (GameObject*)CagedSquirrel::create(properties); };
	this->deserializers[CagedTiger::MapKeyCagedTiger] = [=](ValueMap properties) { return (GameObject*)CagedTiger::create(properties); };
	this->deserializers[CagedTucan::MapKeyCagedTucan] = [=](ValueMap properties) { return (GameObject*)CagedTucan::create(properties); };
	this->deserializers[CagedTurtle::MapKeyCagedTurtle] = [=](ValueMap properties) { return (GameObject*)CagedTurtle::create(properties); };
	this->deserializers[CagedWhale::MapKeyCagedWhale] = [=](ValueMap properties) { return (GameObject*)CagedWhale::create(properties); };
	this->deserializers[CagedWolf::MapKeyCagedWolf] = [=](ValueMap properties) { return (GameObject*)CagedWolf::create(properties); };
	this->deserializers[CagedWorm::MapKeyCagedWorm] = [=](ValueMap properties) { return (GameObject*)CagedWorm::create(properties); };
	this->deserializers[CagedYeti::MapKeyCagedYeti] = [=](ValueMap properties) { return (GameObject*)CagedYeti::create(properties); };
	this->deserializers[CagedZebra::MapKeyCagedZebra] = [=](ValueMap properties) { return (GameObject*)CagedZebra::create(properties); };
	this->deserializers[CameraControl::MapKeyCameraControl] = [=](ValueMap properties) { return (GameObject*)CameraControl::create(properties); };
	this->deserializers[CameraFocus::MapKeyCameraFocus] = [=](ValueMap properties) { return (GameObject*)CameraFocus::create(properties); };
	this->deserializers[CameraScrollTracker::MapKeyCameraScrollTracker] = [=](ValueMap properties) { return (GameObject*)CameraScrollTracker::create(properties); };
	this->deserializers[CameraStop::MapKeyCameraStop] = [=](ValueMap properties) { return (GameObject*)CameraStop::create(properties); };
	this->deserializers[CameraTarget::MapKeyCameraTarget] = [=](ValueMap properties) { return (GameObject*)CameraTarget::create(properties); };
	this->deserializers[CastleGate::MapKeyCastleGate] = [=](ValueMap properties) { return (GameObject*)CastleGate::create(properties); };
	this->deserializers[CombatSpawn::MapKeyCombatSpawn] = [=](ValueMap properties) { return (GameObject*)CombatSpawn::create(properties); };
	this->deserializers[Catapult::MapKeyCatapult] = [=](ValueMap properties) { return (GameObject*)Catapult::create(properties); };
	this->deserializers[CinematicMarker::MapKeyCinematicMarker] = [=](ValueMap properties) { return (GameObject*)CinematicMarker::create(properties); };
	this->deserializers[CipherChest::MapKeyCipherChest] = [=](ValueMap properties) { return (GameObject*)CipherChest::create(properties); };
	this->deserializers[DarkPortal::MapKeyDarkPortal] = [=](ValueMap properties) { return (GameObject*)DarkPortal::create(properties); };
	this->deserializers[DartLauncher::MapKeyDartLauncher] = [=](ValueMap properties) { return (GameObject*)DartLauncher::create(properties); };
	this->deserializers[DartTripodLauncher::MapKeyDartTripodLauncher] = [=](ValueMap properties) { return (GameObject*)DartTripodLauncher::create(properties); };
	this->deserializers[EdgePortal::MapKeyEdgePortal] = [=](ValueMap properties) { return (GameObject*)EdgePortal::create(properties); };
	this->deserializers[FirePortal::MapKeyFirePortal] = [=](ValueMap properties) { return (GameObject*)FirePortal::create(properties); };
	this->deserializers[FireLauncher::MapKeyFireLauncher] = [=](ValueMap properties) { return (GameObject*)FireLauncher::create(properties); };
	this->deserializers[FloatingAsteroid::MapKeyFloatingAsteroid] = [=](ValueMap properties) { return (GameObject*)FloatingAsteroid::create(properties); };
	this->deserializers[FloatingBomb::MapKeyFloatingBomb] = [=](ValueMap properties) { return (GameObject*)FloatingBomb::create(properties); };
	this->deserializers[FloatingCrate::MapKeyFloatingCrate] = [=](ValueMap properties) { return (GameObject*)FloatingCrate::create(properties); };
	this->deserializers[FloatingRock::MapKeyFloatingRock] = [=](ValueMap properties) { return (GameObject*)FloatingRock::create(properties); };
	this->deserializers[FloatingWoodenBeam::MapKeyFloatingWoodenBeam] = [=](ValueMap properties) { return (GameObject*)FloatingWoodenBeam::create(properties); };
	this->deserializers[FrostPortal::MapKeyFrostPortal] = [=](ValueMap properties) { return (GameObject*)FrostPortal::create(properties); };
	this->deserializers[Gate::MapKeyGate] = [=](ValueMap properties) { return (GameObject*)Gate::create(properties); };
	this->deserializers[LanternGate::MapKeyLanternGate] = [=](ValueMap properties) { return (GameObject*)LanternGate::create(properties); };
	this->deserializers[EdgeLanternGate::MapKeyEdgeLanternGate] = [=](ValueMap properties) { return (GameObject*)EdgeLanternGate::create(properties); };
	this->deserializers[IOU::MapKeyIOU] = [=](ValueMap properties) { return (GameObject*)IOU::create(properties); };
	this->deserializers[HackableHint::MapKeyHackableHint] = [=](ValueMap properties) { return (GameObject*)HackableHint::create(properties); };
	this->deserializers[HelpTotemAttacking::MapKeyHelpTotemAttacking] = [=](ValueMap properties) { return (GameObject*)HelpTotemAttacking::create(properties); };
	this->deserializers[HelpTotemEndOfDemo::MapKeyHelpTotemEndOfDemo] = [=](ValueMap properties) { return (GameObject*)HelpTotemEndOfDemo::create(properties); };
	this->deserializers[HelpTotemHacking::MapKeyHelpTotemHacking] = [=](ValueMap properties) { return (GameObject*)HelpTotemHacking::create(properties); };
	this->deserializers[HelpTotemHexusCards::MapKeyHelpTotemHexusCards] = [=](ValueMap properties) { return (GameObject*)HelpTotemHexusCards::create(properties); };
	this->deserializers[HelpTotemPickPocket::MapKeyHelpTotemPickPocket] = [=](ValueMap properties) { return (GameObject*)HelpTotemPickPocket::create(properties); };
	this->deserializers[HeavenHug::MapKeyHeavenHug] = [=](ValueMap properties) { return (GameObject*)HeavenHug::create(properties); };
	this->deserializers[Laser::MapKeyLaser] = [=](ValueMap properties) { return (GameObject*)Laser::create(properties); };
	this->deserializers[Lever::MapKeyLever] = [=](ValueMap properties) { return (GameObject*)Lever::create(properties); };
	this->deserializers[LifeStone::MapKeyLifeStone] = [=](ValueMap properties) { return (GameObject*)LifeStone::create(properties); };
	this->deserializers[MagicWall::MapKeyMagicWall] = [=](ValueMap properties) { return (GameObject*)MagicWall::create(properties); };
	this->deserializers[MetalSpikes::MapKeyMetalSpikes] = [=](ValueMap properties) { return (GameObject*)MetalSpikes::create(properties); };
	this->deserializers[MechanicalFlail::MapKeyMechanicalFlail] = [=](ValueMap properties) { return (GameObject*)MechanicalFlail::create(properties); };
	this->deserializers[MulDoor::MapKeyMulDoor] = [=](ValueMap properties) { return (GameObject*)MulDoor::create(properties); };
	this->deserializers[NaturePortal::MapKeyNaturePortal] = [=](ValueMap properties) { return (GameObject*)NaturePortal::create(properties); };
	this->deserializers[Portal::MapKeyPortal] = [=](ValueMap properties) { return (GameObject*)Portal::create(properties); };
	this->deserializers[PortalSpawn::MapKeyPortalSpawn] = [=](ValueMap properties) { return (GameObject*)PortalSpawn::create(properties); };
	this->deserializers[PendulumBlade::MapKeyPendulumBlade] = [=](ValueMap properties) { return (GameObject*)PendulumBlade::create(properties); };
	this->deserializers[ShopItem::MapKeyShopItem] = [=](ValueMap properties) { return (GameObject*)ShopItem::create(properties); };
	this->deserializers[ShopPoolMinos::MapKeyShopPoolMinos] = [=](ValueMap properties) { return (GameObject*)ShopPoolMinos::create(properties); };
	this->deserializers[ShopPoolToben::MapKeyShopPoolToben] = [=](ValueMap properties) { return (GameObject*)ShopPoolToben::create(properties); };
	this->deserializers[Ship::MapKeyShip] = [=](ValueMap properties) { return (GameObject*)Ship::create(properties); };
	this->deserializers[SpikedBall::MapKeySpikedBall] = [=](ValueMap properties) { return (GameObject*)SpikedBall::create(properties); };
	this->deserializers[SpikeLog::MapKeySpikeLog] = [=](ValueMap properties) { return (GameObject*)SpikeLog::create(properties); };
	this->deserializers[SquallyShip::MapKeySquallyShip] = [=](ValueMap properties) { return (GameObject*)SquallyShip::create(properties); };
	this->deserializers[StoneButton::MapKeyStoneButton] = [=](ValueMap properties) { return (GameObject*)StoneButton::create(properties); };
	this->deserializers[TempleDoor::MapKeyTempleDoor] = [=](ValueMap properties) { return (GameObject*)TempleDoor::create(properties); };
	this->deserializers[Tent::MapKeyTent] = [=](ValueMap properties) { return (GameObject*)Tent::create(properties); };
	this->deserializers[TrapDoor::MapKeyTrapDoor] = [=](ValueMap properties) { return (GameObject*)TrapDoor::create(properties); };
	this->deserializers[TrapDoorFrame::MapKeyTrapDoorFrame] = [=](ValueMap properties) { return (GameObject*)TrapDoorFrame::create(properties); };
	this->deserializers[Trigger::MapKeyTrigger] = [=](ValueMap properties) { return (GameObject*)Trigger::create(properties); };
	this->deserializers[VoidPortal::MapKeyVoidPortal] = [=](ValueMap properties) { return (GameObject*)VoidPortal::create(properties); };
	this->deserializers[Warp::MapKeyWarp] = [=](ValueMap properties) { return (GameObject*)Warp::create(properties); };
	this->deserializers[Water::MapKeyWater] = [=](ValueMap properties) { return (GameObject*)Water::create(properties); };
	this->deserializers[WaterPortal::MapKeyWaterPortal] = [=](ValueMap properties) { return (GameObject*)WaterPortal::create(properties); };
	this->deserializers[Wind::MapKeyWind] = [=](ValueMap properties) { return (GameObject*)Wind::create(properties); };
	this->deserializers[WindPortal::MapKeyWindPortal] = [=](ValueMap properties) { return (GameObject*)WindPortal::create(properties); };
	this->deserializers[WoodenCrate::MapKeyWoodenCrate] = [=](ValueMap properties) { return (GameObject*)WoodenCrate::create(properties); };
	this->deserializers[WoodenGate::MapKeyWoodenGate] = [=](ValueMap properties) { return (GameObject*)WoodenGate::create(properties); };
	this->deserializers[WoodenSpikes::MapKeyWoodenSpikes] = [=](ValueMap properties) { return (GameObject*)WoodenSpikes::create(properties); };
}

PlatformerObjectDeserializer::~PlatformerObjectDeserializer()
{
}
