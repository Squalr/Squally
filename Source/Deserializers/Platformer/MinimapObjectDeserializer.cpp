#include "MiniMapObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Quests/QuestTask.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

const std::string MiniMapObjectDeserializer::MapKeyTypeObject = "object";
const Color4B MiniMapObjectDeserializer::WarpColor = Color4B::ORANGE;
const Color4B MiniMapObjectDeserializer::PortalColor = Color4B(255, 0, 0, 255);
const Color4B MiniMapObjectDeserializer::WaterColor = Color4B(72, 156, 189, 255);
const Color4B MiniMapObjectDeserializer::DestroyableColor = Color4B(102, 56, 38, 255);
const Color4B MiniMapObjectDeserializer::InteractableColor = Color4B::YELLOW;

MiniMapObjectDeserializer* MiniMapObjectDeserializer::create()
{
	MiniMapObjectDeserializer* instance = new MiniMapObjectDeserializer();

	instance->autorelease();

	return instance;
}

MiniMapObjectDeserializer::MiniMapObjectDeserializer() : super(MiniMapObjectDeserializer::MapKeyTypeObject)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	// Custom objects
	this->deserializers[AddDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[AlchemyLab::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Anvil::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[BreakableBarrel::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::DestroyableColor); };
	this->deserializers[BreakableCage::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::DestroyableColor); };
	this->deserializers[CagedBat::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBear::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBeaver::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBee::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBird::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBlowfish::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBull::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedBunny::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedCat::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedChicken::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedCow::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedCrocodile::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedDinosaur::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedDog::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedDuck::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedFox::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedGiraffe::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedGoat::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedHedgehog::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedHippo::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedHorse::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedKillerWhale::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedKoala::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedLadybug::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedLion::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedLizard::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedMonkey::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedMountainLion::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedMouse::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedPanda::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedParrot::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedPenguin::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedPig::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedRaccoon::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedReindeer::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedRhino::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSheep::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSkunk::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSnail::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSnake::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSquid::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedSquirrel::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedTiger::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedTucan::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedTurtle::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedWhale::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedWolf::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedWorm::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedYeti::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CagedZebra::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CartLift::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CartStop::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CastleGate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Catapult::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Chest::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CinematicMarker::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[CipherChest::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[DartLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[DartTripodLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[DartTripodLauncherSqualr::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[DragonDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[EdgePortal::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[ElectricityBeam::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FireplaceFire::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FireLauncher::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FireLauncherSqualr::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatingAsteroid::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatingBomb::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatingCrate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatingRock::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatTutorialPortal::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[FloatingWoodenBeam::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Gate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[GlassDisplayItem::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[LanternGate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[LogicGate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[EdgeLanternGate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[Icicle::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[IOUDrop::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[IOUDrop5::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[IOUDrop10::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[IOUDrop25::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemAttacking::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemEndOfDemo::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemEquipment::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemHacking::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemHexusCards::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemPickPocket::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemPotions::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HelpTotemSwimHack::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[HeavenHug::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Laser::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Lever::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[LifeStone::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[LogicTorch::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[PullyHorizontal::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[PullyVertical::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[ManaOrb::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MagePortal::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[MagicWall::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MayanDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[MetalChest::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MetalSpikes::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MechanicalFlail::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineCart::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineCartLootable::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineClaw::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineElevatorLift::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineLantern::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineWheel::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MineWinch::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[MulDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[ObjectiveTrigger::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[OptionWarp::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Portal::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[PendulumBlade::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Ram::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[RegisterStone::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[RewardItem::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Sarcophagus::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[ShopItem::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[SpikedBall::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[SpikedLog::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[SquallyShip::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Stalactite::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[StoneButton::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[StoneStack::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[TempleDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[Tent::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Torch::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[TrapDoor::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[TrapDoorFrame::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Vase::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[Warp::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::WarpColor); };
	this->deserializers[WarpGateBP::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateCV::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateDH::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateDM::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateEF::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateLC::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateUR::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[WarpGateVS::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties, MiniMapObjectDeserializer::PortalColor); };
	this->deserializers[Water::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties,MiniMapObjectDeserializer::WaterColor); };
	this->deserializers[Wind::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[WoodenCrate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[WoodenGate::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
	this->deserializers[WoodenSpikes::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapObject::create(properties); };
}

MiniMapObjectDeserializer::~MiniMapObjectDeserializer()
{
}
