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
	
	// Engine objects
	this->deserializers[Sound::MapKey] = [=](ValueMap properties) { return (GameObject*)Sound::create(properties); };
	this->deserializers[WorldSound::MapKey] = [=](ValueMap properties) { return (GameObject*)WorldSound::create(properties); };

	// Custom objects
	this->deserializers[AddDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)AddDoor::create(properties); };
	this->deserializers[Airship1::MapKey] = [=](ValueMap properties) { return (GameObject*)Airship1::create(properties); };
	this->deserializers[Airship2::MapKey] = [=](ValueMap properties) { return (GameObject*)Airship2::create(properties); };
	this->deserializers[AlchemyLab::MapKey] = [=](ValueMap properties) { return (GameObject*)AlchemyLab::create(properties); };
	this->deserializers[Anvil::MapKey] = [=](ValueMap properties) { return (GameObject*)Anvil::create(properties); };
	this->deserializers[BreakableBarrel::MapKey] = [=](ValueMap properties) { return (GameObject*)BreakableBarrel::create(properties); };
	this->deserializers[BreakableCage::MapKey] = [=](ValueMap properties) { return (GameObject*)BreakableCage::create(properties); };
	this->deserializers[CagedBat::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBat::create(properties); };
	this->deserializers[CagedBear::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBear::create(properties); };
	this->deserializers[CagedBeaver::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBeaver::create(properties); };
	this->deserializers[CagedBee::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBee::create(properties); };
	this->deserializers[CagedBird::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBird::create(properties); };
	this->deserializers[CagedBlowfish::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBlowfish::create(properties); };
	this->deserializers[CagedBull::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBull::create(properties); };
	this->deserializers[CagedBunny::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedBunny::create(properties); };
	this->deserializers[CagedCat::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedCat::create(properties); };
	this->deserializers[CagedChicken::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedChicken::create(properties); };
	this->deserializers[CagedCow::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedCow::create(properties); };
	this->deserializers[CagedCrocodile::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedCrocodile::create(properties); };
	this->deserializers[CagedDinosaur::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedDinosaur::create(properties); };
	this->deserializers[CagedDog::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedDog::create(properties); };
	this->deserializers[CagedDuck::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedDuck::create(properties); };
	this->deserializers[CagedFox::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedFox::create(properties); };
	this->deserializers[CagedGiraffe::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedGiraffe::create(properties); };
	this->deserializers[CagedGoat::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedGoat::create(properties); };
	this->deserializers[CagedHedgehog::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedHedgehog::create(properties); };
	this->deserializers[CagedHippo::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedHippo::create(properties); };
	this->deserializers[CagedHorse::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedHorse::create(properties); };
	this->deserializers[CagedKillerWhale::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedKillerWhale::create(properties); };
	this->deserializers[CagedKoala::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedKoala::create(properties); };
	this->deserializers[CagedLadybug::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedLadybug::create(properties); };
	this->deserializers[CagedLion::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedLion::create(properties); };
	this->deserializers[CagedLizard::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedLizard::create(properties); };
	this->deserializers[CagedMonkey::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedMonkey::create(properties); };
	this->deserializers[CagedMountainLion::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedMountainLion::create(properties); };
	this->deserializers[CagedMouse::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedMouse::create(properties); };
	this->deserializers[CagedPanda::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedPanda::create(properties); };
	this->deserializers[CagedParrot::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedParrot::create(properties); };
	this->deserializers[CagedPenguin::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedPenguin::create(properties); };
	this->deserializers[CagedPig::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedPig::create(properties); };
	this->deserializers[CagedRaccoon::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedRaccoon::create(properties); };
	this->deserializers[CagedReindeer::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedReindeer::create(properties); };
	this->deserializers[CagedRhino::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedRhino::create(properties); };
	this->deserializers[CagedSheep::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSheep::create(properties); };
	this->deserializers[CagedSkunk::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSkunk::create(properties); };
	this->deserializers[CagedSnail::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSnail::create(properties); };
	this->deserializers[CagedSnake::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSnake::create(properties); };
	this->deserializers[CagedSquid::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSquid::create(properties); };
	this->deserializers[CagedSquirrel::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedSquirrel::create(properties); };
	this->deserializers[CagedTiger::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedTiger::create(properties); };
	this->deserializers[CagedTucan::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedTucan::create(properties); };
	this->deserializers[CagedTurtle::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedTurtle::create(properties); };
	this->deserializers[CagedWhale::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedWhale::create(properties); };
	this->deserializers[CagedWolf::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedWolf::create(properties); };
	this->deserializers[CagedWorm::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedWorm::create(properties); };
	this->deserializers[CagedYeti::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedYeti::create(properties); };
	this->deserializers[CagedZebra::MapKey] = [=](ValueMap properties) { return (GameObject*)CagedZebra::create(properties); };
	this->deserializers[CameraControl::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraControl::create(properties); };
	this->deserializers[CameraFocus::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraFocus::create(properties); };
	this->deserializers[CameraScrollTracker::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraScrollTracker::create(properties); };
	this->deserializers[CameraStop::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraStop::create(properties); };
	this->deserializers[CameraTarget::MapKey] = [=](ValueMap properties) { return (GameObject*)CameraTarget::create(properties); };
	this->deserializers[CartLift::MapKey] = [=](ValueMap properties) { return (GameObject*)CartLift::create(properties); };
	this->deserializers[CartSpawn::MapKey] = [=](ValueMap properties) { return (GameObject*)CartSpawn::create(properties); };
	this->deserializers[CartStop::MapKey] = [=](ValueMap properties) { return (GameObject*)CartStop::create(properties); };
	this->deserializers[CastleGate::MapKey] = [=](ValueMap properties) { return (GameObject*)CastleGate::create(properties); };
	this->deserializers[CombatSpawn::MapKey] = [=](ValueMap properties) { return (GameObject*)CombatSpawn::create(properties); };
	this->deserializers[Catapult::MapKey] = [=](ValueMap properties) { return (GameObject*)Catapult::create(properties); };
	this->deserializers[Chest::MapKey] = [=](ValueMap properties) { return (GameObject*)Chest::create(properties); };
	this->deserializers[CinematicMarker::MapKey] = [=](ValueMap properties) { return (GameObject*)CinematicMarker::create(properties); };
	this->deserializers[CipherChest::MapKey] = [=](ValueMap properties) { return (GameObject*)CipherChest::create(properties); };
	this->deserializers[DartLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)DartLauncher::create(properties); };
	this->deserializers[DartTripodLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)DartTripodLauncher::create(properties); };
	this->deserializers[DartTripodLauncherSqualr::MapKey] = [=](ValueMap properties) { return (GameObject*)DartTripodLauncherSqualr::create(properties); };
	this->deserializers[DragonDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)DragonDoor::create(properties); };
	this->deserializers[EdgePortal::MapKey] = [=](ValueMap properties) { return (GameObject*)EdgePortal::create(properties); };
	this->deserializers[ElectricityBeam::MapKey] = [=](ValueMap properties) { return (GameObject*)ElectricityBeam::create(properties); };
	this->deserializers[FireplaceFire::MapKey] = [=](ValueMap properties) { return (GameObject*)FireplaceFire::create(properties); };
	this->deserializers[FireLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)FireLauncher::create(properties); };
	this->deserializers[FireLauncherSqualr::MapKey] = [=](ValueMap properties) { return (GameObject*)FireLauncherSqualr::create(properties); };
	this->deserializers[FloatingAsteroid::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatingAsteroid::create(properties); };
	this->deserializers[FloatingBomb::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatingBomb::create(properties); };
	this->deserializers[FloatingCrate::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatingCrate::create(properties); };
	this->deserializers[FloatingRock::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatingRock::create(properties); };
	this->deserializers[FloatTutorialPortal::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatTutorialPortal::create(properties); };
	this->deserializers[FloatingWoodenBeam::MapKey] = [=](ValueMap properties) { return (GameObject*)FloatingWoodenBeam::create(properties); };
	this->deserializers[Gate::MapKey] = [=](ValueMap properties) { return (GameObject*)Gate::create(properties); };
	this->deserializers[GlassDisplayItem::MapKey] = [=](ValueMap properties) { return (GameObject*)GlassDisplayItem::create(properties); };
	this->deserializers[LanternGate::MapKey] = [=](ValueMap properties) { return (GameObject*)LanternGate::create(properties); };
	this->deserializers[LogicGate::MapKey] = [=](ValueMap properties) { return (GameObject*)LogicGate::create(properties); };
	this->deserializers[EdgeLanternGate::MapKey] = [=](ValueMap properties) { return (GameObject*)EdgeLanternGate::create(properties); };
	this->deserializers[Icicle::MapKey] = [=](ValueMap properties) { return (GameObject*)Icicle::create(properties); };
	this->deserializers[IOUDrop::MapKey] = [=](ValueMap properties) { return (GameObject*)IOUDrop::create(properties); };
	this->deserializers[IOUDrop5::MapKey] = [=](ValueMap properties) { return (GameObject*)IOUDrop5::create(properties); };
	this->deserializers[IOUDrop10::MapKey] = [=](ValueMap properties) { return (GameObject*)IOUDrop10::create(properties); };
	this->deserializers[IOUDrop25::MapKey] = [=](ValueMap properties) { return (GameObject*)IOUDrop25::create(properties); };
	this->deserializers[HelpTotemAttacking::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemAttacking::create(properties); };
	this->deserializers[HelpTotemEndOfDemo::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemEndOfDemo::create(properties); };
	this->deserializers[HelpTotemEquipment::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemEquipment::create(properties); };
	this->deserializers[HelpTotemHacking::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemHacking::create(properties); };
	this->deserializers[HelpTotemHexusCards::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemHexusCards::create(properties); };
	this->deserializers[HelpTotemPickPocket::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemPickPocket::create(properties); };
	this->deserializers[HelpTotemPotions::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemPotions::create(properties); };
	this->deserializers[HelpTotemSwimHack::MapKey] = [=](ValueMap properties) { return (GameObject*)HelpTotemSwimHack::create(properties); };
	this->deserializers[HeavenHug::MapKey] = [=](ValueMap properties) { return (GameObject*)HeavenHug::create(properties); };
	this->deserializers[Laser::MapKey] = [=](ValueMap properties) { return (GameObject*)Laser::create(properties); };
	this->deserializers[Lever::MapKey] = [=](ValueMap properties) { return (GameObject*)Lever::create(properties); };
	this->deserializers[LifeStone::MapKey] = [=](ValueMap properties) { return (GameObject*)LifeStone::create(properties); };
	this->deserializers[LogicTorch::MapKey] = [=](ValueMap properties) { return (GameObject*)LogicTorch::create(properties); };
	this->deserializers[PullyHorizontal::MapKey] = [=](ValueMap properties) { return (GameObject*)PullyHorizontal::create(properties); };
	this->deserializers[PullyVertical::MapKey] = [=](ValueMap properties) { return (GameObject*)PullyVertical::create(properties); };
	this->deserializers[ManaOrb::MapKey] = [=](ValueMap properties) { return (GameObject*)ManaOrb::create(properties); };
	this->deserializers[MagePortal::MapKey] = [=](ValueMap properties) { return (GameObject*)MagePortal::create(properties); };
	this->deserializers[MagicWall::MapKey] = [=](ValueMap properties) { return (GameObject*)MagicWall::create(properties); };
	this->deserializers[MayanDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MayanDoor::create(properties); };
	this->deserializers[MetalChest::MapKey] = [=](ValueMap properties) { return (GameObject*)MetalChest::create(properties); };
	this->deserializers[MetalSpikes::MapKey] = [=](ValueMap properties) { return (GameObject*)MetalSpikes::create(properties); };
	this->deserializers[MechanicalFlail::MapKey] = [=](ValueMap properties) { return (GameObject*)MechanicalFlail::create(properties); };
	this->deserializers[MineCart::MapKey] = [=](ValueMap properties) { return (GameObject*)MineCart::create(properties); };
	this->deserializers[MineCartLootable::MapKey] = [=](ValueMap properties) { return (GameObject*)MineCartLootable::create(properties); };
	this->deserializers[MineClaw::MapKey] = [=](ValueMap properties) { return (GameObject*)MineClaw::create(properties); };
	this->deserializers[MineLantern::MapKey] = [=](ValueMap properties) { return (GameObject*)MineLantern::create(properties); };
	this->deserializers[MineWheel::MapKey] = [=](ValueMap properties) { return (GameObject*)MineWheel::create(properties); };
	this->deserializers[MineWinch::MapKey] = [=](ValueMap properties) { return (GameObject*)MineWinch::create(properties); };
	this->deserializers[MulDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MulDoor::create(properties); };
	this->deserializers[ObjectiveTrigger::MapKey] = [=](ValueMap properties) { return (GameObject*)ObjectiveTrigger::create(properties); };
	this->deserializers[OptionWarp::MapKey] = [=](ValueMap properties) { return (GameObject*)OptionWarp::create(properties); };
	this->deserializers[Portal::MapKey] = [=](ValueMap properties) { return (GameObject*)Portal::create(properties); };
	this->deserializers[PortalSpawn::MapKey] = [=](ValueMap properties) { return (GameObject*)PortalSpawn::create(properties); };
	this->deserializers[PendulumBlade::MapKey] = [=](ValueMap properties) { return (GameObject*)PendulumBlade::create(properties); };
	this->deserializers[Ram::MapKey] = [=](ValueMap properties) { return (GameObject*)Ram::create(properties); };
	this->deserializers[RegisterStone::MapKey] = [=](ValueMap properties) { return (GameObject*)RegisterStone::create(properties); };
	this->deserializers[RegisterStoneValue::MapKey] = [=](ValueMap properties) { return (GameObject*)RegisterStoneValue::create(properties); };
	this->deserializers[RewardItem::MapKey] = [=](ValueMap properties) { return (GameObject*)RewardItem::create(properties); };
	this->deserializers[RewardPoolHera::MapKey] = [=](ValueMap properties) { return (GameObject*)RewardPoolHera::create(properties); };
	this->deserializers[Sarcophagus::MapKey] = [=](ValueMap properties) { return (GameObject*)Sarcophagus::create(properties); };
	this->deserializers[ShopItem::MapKey] = [=](ValueMap properties) { return (GameObject*)ShopItem::create(properties); };
	this->deserializers[ShopPoolMinos::MapKey] = [=](ValueMap properties) { return (GameObject*)ShopPoolMinos::create(properties); };
	this->deserializers[ShopPoolToben::MapKey] = [=](ValueMap properties) { return (GameObject*)ShopPoolToben::create(properties); };
	this->deserializers[ShopPoolGriffin::MapKey] = [=](ValueMap properties) { return (GameObject*)ShopPoolGriffin::create(properties); };
	this->deserializers[ShopPoolGeryon::MapKey] = [=](ValueMap properties) { return (GameObject*)ShopPoolGeryon::create(properties); };
	this->deserializers[Ship::MapKey] = [=](ValueMap properties) { return (GameObject*)Ship::create(properties); };
	this->deserializers[SpawnPoolEF::MapKey] = [=](ValueMap properties) { return (GameObject*)SpawnPoolEF::create(properties); };
	this->deserializers[SpawnPoolUR::MapKey] = [=](ValueMap properties) { return (GameObject*)SpawnPoolUR::create(properties); };
	this->deserializers[SpikedBall::MapKey] = [=](ValueMap properties) { return (GameObject*)SpikedBall::create(properties); };
	this->deserializers[SpikedLog::MapKey] = [=](ValueMap properties) { return (GameObject*)SpikedLog::create(properties); };
	this->deserializers[SquallyShip::MapKey] = [=](ValueMap properties) { return (GameObject*)SquallyShip::create(properties); };
	this->deserializers[Stalactite::MapKey] = [=](ValueMap properties) { return (GameObject*)Stalactite::create(properties); };
	this->deserializers[StoneButton::MapKey] = [=](ValueMap properties) { return (GameObject*)StoneButton::create(properties); };
	this->deserializers[TempleDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleDoor::create(properties); };
	this->deserializers[Tent::MapKey] = [=](ValueMap properties) { return (GameObject*)Tent::create(properties); };
	this->deserializers[Torch::MapKey] = [=](ValueMap properties) { return (GameObject*)Torch::create(properties); };
	this->deserializers[TrapDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)TrapDoor::create(properties); };
	this->deserializers[TrapDoorFrame::MapKey] = [=](ValueMap properties) { return (GameObject*)TrapDoorFrame::create(properties); };
	this->deserializers[Trigger::MapKey] = [=](ValueMap properties) { return (GameObject*)Trigger::create(properties); };
	this->deserializers[Vase::MapKey] = [=](ValueMap properties) { return (GameObject*)Vase::create(properties); };
	this->deserializers[Warp::MapKey] = [=](ValueMap properties) { return (GameObject*)Warp::create(properties); };
	this->deserializers[WarpGateBP::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateBP::create(properties); };
	this->deserializers[WarpGateCV::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateCV::create(properties); };
	this->deserializers[WarpGateDH::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateDH::create(properties); };
	this->deserializers[WarpGateDM::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateDM::create(properties); };
	this->deserializers[WarpGateEF::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateEF::create(properties); };
	this->deserializers[WarpGateLC::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateLC::create(properties); };
	this->deserializers[WarpGateUR::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateUR::create(properties); };
	this->deserializers[WarpGateVS::MapKey] = [=](ValueMap properties) { return (GameObject*)WarpGateVS::create(properties); };
	this->deserializers[Water::MapKey] = [=](ValueMap properties) { return (GameObject*)Water::create(properties); };
	this->deserializers[Wind::MapKey] = [=](ValueMap properties) { return (GameObject*)Wind::create(properties); };
	this->deserializers[WoodenCrate::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodenCrate::create(properties); };
	this->deserializers[WoodDoorSpawn::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodDoorSpawn::create(properties); };
	this->deserializers[WoodenGate::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodenGate::create(properties); };
	this->deserializers[WoodenSpikes::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodenSpikes::create(properties); };
}

PlatformerObjectDeserializer::~PlatformerObjectDeserializer()
{
}
