#pragma once

#include "Engine/Sound/Sound.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Terrain/TerrainHole.h"
#include "Objects/Camera/CameraFocus.h"
#include "Objects/Camera/CameraScrollTracker.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Breakables/BreakableBarrel.h"
#include "Objects/Platformer/Breakables/BreakableCage.h"
#include "Objects/Platformer/Breakables/BreakableCageTall.h"
#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimals.h"
#include "Objects/Platformer/Breakables/Vase.h"
#include "Objects/Platformer/Camera/CameraControl.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Cinematic/Sarcophagus/Sarcophagus.h"
#include "Objects/Platformer/Cinematic/SquallyShip.h"
#include "Objects/Platformer/Collectables/IOUDrop.h"
#include "Objects/Platformer/Collectables/IOUDrop5.h"
#include "Objects/Platformer/Collectables/IOUDrop10.h"
#include "Objects/Platformer/Collectables/IOUDrop25.h"
#include "Objects/Platformer/Collectables/ManaOrb.h"
#include "Objects/Platformer/Collectables/SpawnPools/SpawnPoolEF.h"
#include "Objects/Platformer/Collectables/SpawnPools/SpawnPoolUR.h"
#include "Objects/Platformer/Decor/LavaFall.h"
#include "Objects/Platformer/Decor/LavaGeyser.h"
#include "Objects/Platformer/Decor/FireplaceFire.h"
#include "Objects/Platformer/Decor/MagicWall.h"
#include "Objects/Platformer/Decor/MineClaw.h"
#include "Objects/Platformer/Decor/MineLantern.h"
#include "Objects/Platformer/Decor/MineWheel.h"
#include "Objects/Platformer/Decor/MineWinch.h"
#include "Objects/Platformer/Decor/PullyHorizontal.h"
#include "Objects/Platformer/Decor/PullyVertical.h"
#include "Objects/Platformer/Decor/RobotClaw.h"
#include "Objects/Platformer/Decor/Smoke.h"
#include "Objects/Platformer/Interactables/AlchemyLab/AlchemyLab.h"
#include "Objects/Platformer/Interactables/Anvil/AncientAnvil.h"
#include "Objects/Platformer/Interactables/Anvil/Anvil.h"
#include "Objects/Platformer/Interactables/Chests/ArcaneBook.h"
#include "Objects/Platformer/Interactables/Chests/Chest.h"
#include "Objects/Platformer/Interactables/Chests/CipherChest.h"
#include "Objects/Platformer/Interactables/Chests/EgyptianChest.h"
#include "Objects/Platformer/Interactables/Chests/GlassDisplays/GlassDisplayItem.h"
#include "Objects/Platformer/Interactables/Chests/MetalChest.h"
#include "Objects/Platformer/Interactables/Chests/MineCartLootable.h"
#include "Objects/Platformer/Interactables/Chests/PresentChest.h"
#include "Objects/Platformer/Interactables/Computer/Computer.h"
#include "Objects/Platformer/Interactables/Crack/Crack.h"
#include "Objects/Platformer/Interactables/Doors/CastleGate/CastleGate.h"
#include "Objects/Platformer/Interactables/Doors/ClockDoor/ClockDoor.h"
#include "Objects/Platformer/Interactables/Doors/Dragon/DragonDoor.h"
#include "Objects/Platformer/Interactables/Doors/EdgePortal.h"
#include "Objects/Platformer/Interactables/Doors/Gate/Gate.h"
#include "Objects/Platformer/Interactables/Doors/HellGate/HellGate.h"
#include "Objects/Platformer/Interactables/Doors/LanternGate/EdgeLanternGate.h"
#include "Objects/Platformer/Interactables/Doors/LanternGate/LanternGate.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/AnswerStone.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/RegisterStone.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/StoneStack.h"
#include "Objects/Platformer/Interactables/Doors/MineDoor/MineDoor.h"
#include "Objects/Platformer/Interactables/Doors/OptionWarp.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/Portcullus/Portcullus.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/AddDoor/AddDoor.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/MulDoor/MulDoor.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/ScreamingDoor.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/TrackingEye.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/TrackingEyeController.h"
#include "Objects/Platformer/Interactables/Doors/Temple/TempleDoor.h"
#include "Objects/Platformer/Interactables/Doors/TrapDoor/TrapDoor.h"
#include "Objects/Platformer/Interactables/Doors/TrapDoor/TrapDoorFrame.h"
#include "Objects/Platformer/Interactables/Doors/Warp.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateBP.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateCV.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateFF.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateDM.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateEF.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateLC.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateUR.h"
#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGateVS.h"
#include "Objects/Platformer/Interactables/Doors/WoodenGate/WoodenGate.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemAttacking.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemColdWater.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemEndOfDemo.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemEquipment.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemHacking.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemHexusCards.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemPickPocket.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemPotions.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemRepair.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemSwimHack.h"
#include "Objects/Platformer/Interactables/HexusShrine/HexusShrine.h"
#include "Objects/Platformer/Interactables/LifeStone.h"
#include "Objects/Platformer/Interactables/Lights/Torch.h"
#include "Objects/Platformer/Interactables/Mounts/GatlingGun/GatlingGun.h"
#include "Objects/Platformer/Interactables/Mounts/MineCart/CartStop.h"
#include "Objects/Platformer/Interactables/Mounts/MineCart/MineCart.h"
#include "Objects/Platformer/Interactables/Puzzles/Brazier.h"
#include "Objects/Platformer/Interactables/Puzzles/LogicGate.h"
#include "Objects/Platformer/Interactables/Puzzles/LogicPuzzleController.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Interactables/Tent.h"
#include "Objects/Platformer/Interactables/ShipWheel/ShipWheel.h"
#include "Objects/Platformer/Interactables/SmeltingPot/SmeltingPot.h"
#include "Objects/Platformer/Interactables/Spawns/CartSpawn.h"
#include "Objects/Platformer/Interactables/Spawns/PortalSpawn.h"
#include "Objects/Platformer/Interactables/Spawns/WoodDoorSpawn.h"
#include "Objects/Platformer/Liquids/Acid.h"
#include "Objects/Platformer/Liquids/Lava.h"
#include "Objects/Platformer/Liquids/Water.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"
#include "Objects/Platformer/MiniMap/MiniMapRelocator.h"
#include "Objects/Platformer/Physics/Blizzard/Blizzard.h"
#include "Objects/Platformer/Physics/Cannon/Cannon.h"
#include "Objects/Platformer/Physics/Catapult/Catapult.h"
#include "Objects/Platformer/Physics/FloatingAsteroid/FloatingAsteroid.h"
#include "Objects/Platformer/Physics/FloatingCrate/FloatingCrate.h"
#include "Objects/Platformer/Physics/FloatingRock/FloatingRock.h"
#include "Objects/Platformer/Physics/FloatingWoodenBeam/FloatingWoodenBeam.h"
#include "Objects/Platformer/Physics/Lifts/CartLift.h"
#include "Objects/Platformer/Physics/Lifts/MineElevatorLift.h"
#include "Objects/Platformer/Physics/Wind/Wind.h"
#include "Objects/Platformer/Physics/WoodenCrate/WoodenCrate.h"
#include "Objects/Platformer/Rewards/RewardItem.h"
#include "Objects/Platformer/Rewards/RewardPool.h"
#include "Objects/Platformer/Rewards/UnderflowRuins/RewardPoolHera.h"
#include "Objects/Platformer/Shops/BallmerPeaks/ShopPoolSmithT7.h"
#include "Objects/Platformer/Shops/BallmerPeaks/ShopPoolAlchT7.h"
#include "Objects/Platformer/Shops/BallmerPeaks/ShopPoolInnT7.h"
#include "Objects/Platformer/Shops/CastleValgrind/ShopPoolSmithT4.h"
#include "Objects/Platformer/Shops/CastleValgrind/ShopPoolAlchT4.h"
#include "Objects/Platformer/Shops/CastleValgrind/ShopPoolInnT4.h"
#include "Objects/Platformer/Shops/FirewallFissure/ShopPoolSmithT6.h"
#include "Objects/Platformer/Shops/FirewallFissure/ShopPoolAlchT6.h"
#include "Objects/Platformer/Shops/FirewallFissure/ShopPoolInnT6.h"
#include "Objects/Platformer/Shops/DataMines/ShopPoolSmithT3.h"
#include "Objects/Platformer/Shops/DataMines/ShopPoolAlchT3.h"
#include "Objects/Platformer/Shops/DataMines/ShopPoolInnT3.h"
#include "Objects/Platformer/Shops/EndianForest/ShopPoolSmithT1.h"
#include "Objects/Platformer/Shops/EndianForest/ShopPoolInnT1.h"
#include "Objects/Platformer/Shops/EndianForest/ShopPoolAlchT1.h"
#include "Objects/Platformer/Shops/LambdaCrypts/ShopPoolSmithT5.h"
#include "Objects/Platformer/Shops/LambdaCrypts/ShopPoolAlchT5.h"
#include "Objects/Platformer/Shops/LambdaCrypts/ShopPoolInnT5.h"
#include "Objects/Platformer/Shops/UnderflowRuins/ShopPoolInnT2.h"
#include "Objects/Platformer/Shops/UnderflowRuins/ShopPoolSmithT2.h"
#include "Objects/Platformer/Shops/UnderflowRuins/ShopPoolAlchT2.h"
#include "Objects/Platformer/Shops/VoidStar/ShopPoolInnT8.h"
#include "Objects/Platformer/Shops/VoidStar/ShopPoolSmithT8.h"
#include "Objects/Platformer/Shops/VoidStar/ShopPoolAlchT8.h"
#include "Objects/Platformer/Shops/ShopItem.h"
#include "Objects/Platformer/Shops/ShopPool.h"
#include "Objects/Platformer/Spawns/CombatSpawn.h"
#include "Objects/Platformer/Switches/Lever/Lever.h"
#include "Objects/Platformer/Switches/ObjectiveTrigger.h"
#include "Objects/Platformer/Switches/StoneButton/StoneButton.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Objects/Platformer/Switches/Switch/Switch.h"
#include "Objects/Platformer/Transportation/Airship.h"
#include "Objects/Platformer/Transportation/Ship.h"
#include "Objects/Platformer/Transportation/Train.h"
#include "Objects/Platformer/Transportation/VikingShip.h"
#include "Objects/Platformer/Traps/Crusher/Crusher.h"
#include "Objects/Platformer/Traps/ElectricityBeam/ElectricityBeam.h"
#include "Objects/Platformer/Traps/FireBird/FireBird.h"
#include "Objects/Platformer/Traps/FloatingBomb/FloatingBomb.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHug.h"
#include "Objects/Platformer/Traps/Icicle/Icicle.h"
#include "Objects/Platformer/Traps/Laser/Laser.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartLauncher.h"
#include "Objects/Platformer/Traps/Launchers/DartTripodLauncher/DartTripodLauncher.h"
#include "Objects/Platformer/Traps/Launchers/DartTripodLauncher/DartTripodLauncherSqualr.h"
#include "Objects/Platformer/Traps/Launchers/FireLauncher/FireLauncher.h"
#include "Objects/Platformer/Traps/Launchers/FireLauncher/FireLauncherSqualr.h"
#include "Objects/Platformer/Traps/Launchers/WaterLauncher/WaterLauncher.h"
#include "Objects/Platformer/Traps/LavaFlow/LavaFlow.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlail.h"
#include "Objects/Platformer/Traps/MetalSpikes/MetalSpikes.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBlade.h"
#include "Objects/Platformer/Traps/SpikedBall/SpikedBall.h"
#include "Objects/Platformer/Traps/SpikedLog/SpikedLog.h"
#include "Objects/Platformer/Traps/SpikedLogRailed/SpikedLogRailed.h"
#include "Objects/Platformer/Traps/Stalactite/Stalactite.h"
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikes.h"
#include "Objects/Platformer/Interactables/Tutorials/FloatTutorialPortal.h"
