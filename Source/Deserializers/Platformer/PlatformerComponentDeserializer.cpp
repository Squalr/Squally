#include "PlatformerComponentDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Components/PlatformerComponents.h"

using namespace cocos2d;

PlatformerComponentDeserializer* PlatformerComponentDeserializer::create()
{
	PlatformerComponentDeserializer* instance = new PlatformerComponentDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerComponentDeserializer::PlatformerComponentDeserializer() : super()
{
	this->componentDeserializers = std::map<std::string, std::function<Component*(GameObject*)>>();

	this->componentDeserializers[AgroBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AgroBehavior::create(owner); };
	this->componentDeserializers[BirdBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BirdBehavior::create(owner); };
	this->componentDeserializers[BridgeBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BridgeBehavior::create(owner); };
	this->componentDeserializers[DisabledPortal::MapKey] = [=](GameObject* owner) { return (Component*)DisabledPortal::create(owner); };
	this->componentDeserializers[EnemyBattleAllyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)EnemyBattleAllyBehaviorGroup::create(owner); };
	this->componentDeserializers[EnemyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)EnemyBehaviorGroup::create(owner); };
	this->componentDeserializers[EntityBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)EntityBehaviorGroup::create(owner); };
	this->componentDeserializers[EntityDisarmedBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityDisarmedBehavior::create(owner); };
	this->componentDeserializers[EntityNoGravityBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityNoGravityBehavior::create(owner); };
	this->componentDeserializers[EntityPacingBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityPacingBehavior::create(owner); };
	this->componentDeserializers[EntityPetrificationBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityPetrificationBehavior::create(owner); };
	this->componentDeserializers[EntityPickPocketBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityPickPocketBehavior::create(owner); };
	this->componentDeserializers[EntityRunBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EntityRunBehavior::create(owner); };
	this->componentDeserializers[DispelIllusionBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DispelIllusionBehavior::create(owner); };
	this->componentDeserializers[FriendlyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)FriendlyBehaviorGroup::create(owner); };
	this->componentDeserializers[FirstIOUFound::MapKey] = [=](GameObject* owner) { return (Component*)FirstIOUFound::create(owner); };
	this->componentDeserializers[IllusionBehavior::MapKey] = [=](GameObject* owner) { return (Component*)IllusionBehavior::create(owner); };
	this->componentDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LookAtSquallyBehavior::create(owner); };
	this->componentDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LookAtSquallyBehavior::create(owner); };
	this->componentDeserializers[LockedPortal::MapKey] = [=](GameObject* owner) { return (Component*)LockedPortal::create(owner); };
	this->componentDeserializers[MageCastBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MageCastBehavior::create(owner); };
	this->componentDeserializers[NoDefendBehavior::MapKey] = [=](GameObject* owner) { return (Component*)NoDefendBehavior::create(owner); };
	this->componentDeserializers[NoItemsBehavior::MapKey] = [=](GameObject* owner) { return (Component*)NoItemsBehavior::create(owner); };
	this->componentDeserializers[PetrificationLinkBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PetrificationLinkBehavior::create(owner); };
	this->componentDeserializers[ShopkeeperBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)ShopkeeperBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)SquallyBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)SquallyCombatBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyNoSavePositionBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SquallyNoSavePositionBehavior::create(owner); };
	this->componentDeserializers[ZFadeBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ZFadeBehavior::create(owner); };
	
	/*********************
	    Clippy
	*********************/
	this->componentDeserializers[DartLauncherClippyNopBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DartLauncherClippyNopBehavior::create(owner); };
	this->componentDeserializers[IsSwimmingClippyBehavior::MapKey] = [=](GameObject* owner) { return (Component*)IsSwimmingClippyBehavior::create(owner); };
	this->componentDeserializers[MechanicalFlailClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MechanicalFlailClippyAngleBehavior::create(owner); };
	this->componentDeserializers[PendulumBladeClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PendulumBladeClippyAngleBehavior::create(owner); };
	
	/*********************
	    Combat
	*********************/
	this->componentDeserializers[CurseOfTonguesTutorialBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CurseOfTonguesTutorialBehavior::create(owner); };
	this->componentDeserializers[FireballTutorialBehavior::MapKey] = [=](GameObject* owner) { return (Component*)FireballTutorialBehavior::create(owner); };
	this->componentDeserializers[IncrementHealthFlaskTutorialBehavior::MapKey] = [=](GameObject* owner) { return (Component*)IncrementHealthFlaskTutorialBehavior::create(owner); };
	this->componentDeserializers[TrainingHealTutorialBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TrainingHealTutorialBehavior::create(owner); };
	
	/*********************
	    Transportation
	*********************/
	this->componentDeserializers[EFURTransportationBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFURTransportationBehavior::create(owner); };

	// Helpers
	this->componentDeserializers[GeckyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)GeckyBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)GuanoBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoPetrifiedBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)GuanoPetrifiedBehaviorGroup::create(owner); };
	this->componentDeserializers[ScrappyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)ScrappyBehaviorGroup::create(owner); };
	this->componentDeserializers[ScrappyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)ScrappyCombatBehaviorGroup::create(owner); };
	
	/*********************
		Hexus
	*********************/

	// EF
	this->componentDeserializers[EFPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleABehavior::create(owner); };
	this->componentDeserializers[EFPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleBBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleCBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleDBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleEBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleFBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EFPuzzleGBehavior::create(owner); };

	this->componentDeserializers[AraHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AraHexusBehavior::create(owner); };
	this->componentDeserializers[BardHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BardHexusBehavior::create(owner); };
	this->componentDeserializers[BlackbeardHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BlackbeardHexusBehavior::create(owner); };
	this->componentDeserializers[ChironHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ChironHexusBehavior::create(owner); };
	this->componentDeserializers[ElrielHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ElrielHexusBehavior::create(owner); };
	this->componentDeserializers[GrampsHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GrampsHexusBehavior::create(owner); };
	this->componentDeserializers[LianaHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LianaHexusBehavior::create(owner); };
	this->componentDeserializers[LycanHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LycanHexusBehavior::create(owner); };
	this->componentDeserializers[MarcelHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MarcelHexusBehavior::create(owner); };
	this->componentDeserializers[MatuHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MatuHexusBehavior::create(owner); };
	this->componentDeserializers[MinosHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MinosHexusBehavior::create(owner); };
	this->componentDeserializers[PolyphemusHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PolyphemusHexusBehavior::create(owner); };
	this->componentDeserializers[RobinHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)RobinHexusBehavior::create(owner); };
	this->componentDeserializers[TobenHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TobenHexusBehavior::create(owner); };
		
	// UR
	this->componentDeserializers[URPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleABehavior::create(owner); };
	this->componentDeserializers[URPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleBBehavior::create(owner); };
	this->componentDeserializers[URPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleCBehavior::create(owner); };
	this->componentDeserializers[URPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleDBehavior::create(owner); };
	this->componentDeserializers[URPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleEBehavior::create(owner); };
	this->componentDeserializers[URPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleFBehavior::create(owner); };
	this->componentDeserializers[URPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (Component*)URPuzzleGBehavior::create(owner); };

	this->componentDeserializers[AjaxHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AjaxHexusBehavior::create(owner); };
	this->componentDeserializers[AngelHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AngelHexusBehavior::create(owner); };
	this->componentDeserializers[AphroditeHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AphroditeHexusBehavior::create(owner); };
	this->componentDeserializers[AresHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AresHexusBehavior::create(owner); };
	this->componentDeserializers[AthenaHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AthenaHexusBehavior::create(owner); };
	this->componentDeserializers[CleopatraHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CleopatraHexusBehavior::create(owner); };
	this->componentDeserializers[GeyronHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GeyronHexusBehavior::create(owner); };
	this->componentDeserializers[GriffinHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GriffinHexusBehavior::create(owner); };
	this->componentDeserializers[HeraHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)HeraHexusBehavior::create(owner); };
	this->componentDeserializers[HorusHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)HorusHexusBehavior::create(owner); };
	this->componentDeserializers[PoseidonHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PoseidonHexusBehavior::create(owner); };
	this->componentDeserializers[RupertHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)RupertHexusBehavior::create(owner); };
	this->componentDeserializers[ThorHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ThorHexusBehavior::create(owner); };
	this->componentDeserializers[ZeusHexusBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ZeusHexusBehavior::create(owner); };

	/*********************
		ENTITIES / OVERWORLD
	*********************/

	// EF
	this->componentDeserializers[AraBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AraBehavior::create(owner); };
	this->componentDeserializers[CypressBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CypressBehavior::create(owner); };
	this->componentDeserializers[LycanBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LycanBehavior::create(owner); };
	this->componentDeserializers[KingGroggBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)KingGroggBehaviorGroup::create(owner); };
	this->componentDeserializers[OrcBomberBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)OrcBomberBehaviorGroup::create(owner); };

	// UR
	this->componentDeserializers[PoseidonBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PoseidonBehavior::create(owner); };
	this->componentDeserializers[RupertBehavior::MapKey] = [=](GameObject* owner) { return (Component*)RupertBehavior::create(owner); };

	/*********************
		COMBAT / IN-COMBAT
	*********************/

	// Helpers
	this->componentDeserializers[GuanoCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)GuanoCombatBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoPetrifiedCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (Component*)GuanoPetrifiedCombatBehaviorGroup::create(owner); };
	
	// EF
	this->componentDeserializers[TrainingDummyCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TrainingDummyCombatBehavior::create(owner); };
	this->componentDeserializers[CentaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CentaurCombatBehavior::create(owner); };
	this->componentDeserializers[CyclopsCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CyclopsCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinGruntBoarCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GoblinGruntBoarCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GoblinShamanCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinWarriorPigCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GoblinWarriorPigCombatBehavior::create(owner); };
	this->componentDeserializers[GorgonCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GorgonCombatBehavior::create(owner); };
	this->componentDeserializers[KingGroggCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)KingGroggCombatBehavior::create(owner); };
	this->componentDeserializers[OgreCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OgreCombatBehavior::create(owner); };
	this->componentDeserializers[OrcBomberCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OrcBomberCombatBehavior::create(owner); };
	this->componentDeserializers[OrcGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OrcGruntCombatBehavior::create(owner); };
	this->componentDeserializers[OrcSwordsmanCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OrcSwordsmanCombatBehavior::create(owner); };
	this->componentDeserializers[OrcWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OrcWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[OrthrusCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OrthrusCombatBehavior::create(owner); };
	this->componentDeserializers[TrollCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TrollCombatBehavior::create(owner); };

	// UR
	this->componentDeserializers[AnubisPupCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AnubisPupCombatBehavior::create(owner); };
	this->componentDeserializers[AnubisWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AnubisWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[LionessCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LionessCombatBehavior::create(owner); };
	this->componentDeserializers[LionManCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LionManCombatBehavior::create(owner); };
	this->componentDeserializers[MedusaCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MedusaCombatBehavior::create(owner); };
	this->componentDeserializers[MermaidCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MermaidCombatBehavior::create(owner); };
	this->componentDeserializers[MinotaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MinotaurCombatBehavior::create(owner); };
	this->componentDeserializers[MummyPriestCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MummyPriestCombatBehavior::create(owner); };
	this->componentDeserializers[MummyWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MummyWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[OsirisCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)OsirisCombatBehavior::create(owner); };
	this->componentDeserializers[TigressCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TigressCombatBehavior::create(owner); };
	this->componentDeserializers[TigerManCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TigerManCombatBehavior::create(owner); };

	// DM
	this->componentDeserializers[BarbarianCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BarbarianCombatBehavior::create(owner); };
	this->componentDeserializers[EarthElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EarthElementalCombatBehavior::create(owner); };
	this->componentDeserializers[EarthGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EarthGolemCombatBehavior::create(owner); };
	this->componentDeserializers[ForestGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ForestGolemCombatBehavior::create(owner); };
	this->componentDeserializers[KrampusCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)KrampusCombatBehavior::create(owner); };
	this->componentDeserializers[RhinomanCombatBeahvior::MapKey] = [=](GameObject* owner) { return (Component*)RhinomanCombatBeahvior::create(owner); };
	this->componentDeserializers[ShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ShamanCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalArcherCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalArcherCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalNecromancerCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalNecromancerCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[ThugCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ThugCombatBehavior::create(owner); };
	this->componentDeserializers[TikiGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)TikiGolemCombatBehavior::create(owner); };
	
	// CV
	this->componentDeserializers[AgnesCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AgnesCombatBehavior::create(owner); };
	this->componentDeserializers[GorillaCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GorillaCombatBehavior::create(owner); };
	this->componentDeserializers[JackCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)JackCombatBehavior::create(owner); };
	this->componentDeserializers[ReanimatedFighterCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ReanimatedFighterCombatBehavior::create(owner); };
	this->componentDeserializers[ReaperCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ReaperCombatBehavior::create(owner); };
	this->componentDeserializers[ScarecrowCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ScarecrowCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalBaronCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalBaronCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalPirateCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalPirateCombatBehavior::create(owner); };
	this->componentDeserializers[VampireLordCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)VampireLordCombatBehavior::create(owner); };
	this->componentDeserializers[VampiressCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)VampiressCombatBehavior::create(owner); };
	this->componentDeserializers[WerewolfCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)WerewolfCombatBehavior::create(owner); };
	this->componentDeserializers[WraithCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)WraithCombatBehavior::create(owner); };

	// BP
	this->componentDeserializers[CryogenCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)CryogenCombatBehavior::create(owner); };
	this->componentDeserializers[FrostFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)FrostFiendCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinElfCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GoblinElfCombatBehavior::create(owner); };
	this->componentDeserializers[IceGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)IceGolemCombatBehavior::create(owner); };
	this->componentDeserializers[PenguinGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PenguinGruntCombatBehavior::create(owner); };
	this->componentDeserializers[PenguinWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)PenguinWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[SantaCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SantaCombatBehavior::create(owner); };
	this->componentDeserializers[SnowFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SnowFiendCombatBehavior::create(owner); };
	this->componentDeserializers[ToySoldierGoblinCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ToySoldierGoblinCombatBehavior::create(owner); };
	this->componentDeserializers[VikingCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)VikingCombatBehavior::create(owner); };
	this->componentDeserializers[WaterElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)WaterElementalCombatBehavior::create(owner); };
	this->componentDeserializers[YetiCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)YetiCombatBehavior::create(owner); };

	// DH
	this->componentDeserializers[AsmodeusCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AsmodeusCombatBehavior::create(owner); };
	this->componentDeserializers[DemonDragonCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonDragonCombatBehavior::create(owner); };
	this->componentDeserializers[DemonGhostCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonGhostCombatBehavior::create(owner); };
	this->componentDeserializers[DemonGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonGruntCombatBehavior::create(owner); };
	this->componentDeserializers[DemonRogueCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonRogueCombatBehavior::create(owner); };
	this->componentDeserializers[DemonShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonShamanCombatBehavior::create(owner); };
	this->componentDeserializers[DemonSwordsmanCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonSwordsmanCombatBehavior::create(owner); };
	this->componentDeserializers[DemonWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DemonWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[FireElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)FireElementalCombatBehavior::create(owner); };
	this->componentDeserializers[FireTigerCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)FireTigerCombatBehavior::create(owner); };
	this->componentDeserializers[LavaGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LavaGolemCombatBehavior::create(owner); };

	// LC
	this->componentDeserializers[BoneFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BoneFiendCombatBehavior::create(owner); };
	this->componentDeserializers[HunterCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)HunterCombatBehavior::create(owner); };
	this->componentDeserializers[KingZulCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)KingZulCombatBehavior::create(owner); };
	this->componentDeserializers[LazarusCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LazarusCombatBehavior::create(owner); };
	this->componentDeserializers[MysticCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)MysticCombatBehavior::create(owner); };
	this->componentDeserializers[ReanimatedPigCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ReanimatedPigCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalCleaverCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalCleaverCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalKnightCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalKnightCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalPriestessCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)SkeletalPriestessCombatBehavior::create(owner); };
	this->componentDeserializers[UndeadCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)UndeadCombatBehavior::create(owner); };
	this->componentDeserializers[ZombieCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ZombieCombatBehavior::create(owner); };
	this->componentDeserializers[ZombieElricCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ZombieElricCombatBehavior::create(owner); };

	// VS
	this->componentDeserializers[AbominationCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AbominationCombatBehavior::create(owner); };
	this->componentDeserializers[AssassinCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)AssassinCombatBehavior::create(owner); };
	this->componentDeserializers[BoneKnightCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)BoneKnightCombatBehavior::create(owner); };
	this->componentDeserializers[DarkTigerCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)DarkTigerCombatBehavior::create(owner); };
	this->componentDeserializers[EvilEyeCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)EvilEyeCombatBehavior::create(owner); };
	this->componentDeserializers[ExterminatorCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ExterminatorCombatBehavior::create(owner); };
	this->componentDeserializers[GargoyleCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)GargoyleCombatBehavior::create(owner); };
	this->componentDeserializers[LightningGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)LightningGolemCombatBehavior::create(owner); };
	this->componentDeserializers[ShadeCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)ShadeCombatBehavior::create(owner); };
	this->componentDeserializers[VoidArcherCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)VoidArcherCombatBehavior::create(owner); };
	this->componentDeserializers[VoidDemonCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)VoidDemonCombatBehavior::create(owner); };
	this->componentDeserializers[WarlockCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)WarlockCombatBehavior::create(owner); };

	// Misc
	this->componentDeserializers[RamWeakenedCombatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)RamWeakenedCombatBehavior::create(owner); };
	
	/*********************
		Squalr
	*********************/

	this->componentDeserializers[KnownValueBarDoubleBehavior::MapKey] = [=](GameObject* owner) { return (Component*)KnownValueBarDoubleBehavior::create(owner); };
	this->componentDeserializers[KnownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)KnownValueBarFloatBehavior::create(owner); };
	this->componentDeserializers[KnownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (Component*)KnownValueBarInt32Behavior::create(owner); };
	this->componentDeserializers[UnknownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (Component*)UnknownValueBarFloatBehavior::create(owner); };
	this->componentDeserializers[UnknownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (Component*)UnknownValueBarInt32Behavior::create(owner); };
}

PlatformerComponentDeserializer::~PlatformerComponentDeserializer()
{
}

void PlatformerComponentDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string componentName = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyComponent, Value("")).asString();
	
	if (!componentName.empty())
	{
		std::vector<std::string> components = StrUtils::splitOn(componentName, ", ", false);
		
		for (auto next : components)
		{
			Component* component = this->deserialize(ComponentDeserializer::ComponentDeserializationRequestArgs(owner, next));

			if (component != nullptr)
			{
				owner->attachBehavior(component);
			}
		}
	}
}

std::string PlatformerComponentDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyComponent;
}
