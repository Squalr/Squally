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
	this->componentDeserializers = std::map<std::string, std::function<GameComponent*(GameObject*)>>();

	this->componentDeserializers[AgroBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AgroBehavior::create(owner); };
	this->componentDeserializers[BirdBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BirdBehavior::create(owner); };
	this->componentDeserializers[BridgeBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BridgeBehavior::create(owner); };
	this->componentDeserializers[DisabledPortal::MapKey] = [=](GameObject* owner) { return (GameComponent*)DisabledPortal::create(owner); };
	this->componentDeserializers[EnemyBattleAllyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)EnemyBattleAllyBehaviorGroup::create(owner); };
	this->componentDeserializers[EnemyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)EnemyBehaviorGroup::create(owner); };
	this->componentDeserializers[EntityBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityBehaviorGroup::create(owner); };
	this->componentDeserializers[EntityDisarmedBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityDisarmedBehavior::create(owner); };
	this->componentDeserializers[EntityNoGravityBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityNoGravityBehavior::create(owner); };
	this->componentDeserializers[EntityPacingBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityPacingBehavior::create(owner); };
	this->componentDeserializers[EntityPetrificationBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityPetrificationBehavior::create(owner); };
	this->componentDeserializers[EntityPickPocketBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityPickPocketBehavior::create(owner); };
	this->componentDeserializers[EntityRunBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EntityRunBehavior::create(owner); };
	this->componentDeserializers[DispelIllusionBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DispelIllusionBehavior::create(owner); };
	this->componentDeserializers[FriendlyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)FriendlyBehaviorGroup::create(owner); };
	this->componentDeserializers[FirstIOUFound::MapKey] = [=](GameObject* owner) { return (GameComponent*)FirstIOUFound::create(owner); };
	this->componentDeserializers[IllusionBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)IllusionBehavior::create(owner); };
	this->componentDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LookAtSquallyBehavior::create(owner); };
	this->componentDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LookAtSquallyBehavior::create(owner); };
	this->componentDeserializers[LockedPortal::MapKey] = [=](GameObject* owner) { return (GameComponent*)LockedPortal::create(owner); };
	this->componentDeserializers[MageCastBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MageCastBehavior::create(owner); };
	this->componentDeserializers[NoDefendBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)NoDefendBehavior::create(owner); };
	this->componentDeserializers[NoItemsBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)NoItemsBehavior::create(owner); };
	this->componentDeserializers[PetrificationLinkBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PetrificationLinkBehavior::create(owner); };
	this->componentDeserializers[ShopkeeperBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)ShopkeeperBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)SquallyBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)SquallyCombatBehaviorGroup::create(owner); };
	this->componentDeserializers[SquallyNoSavePositionBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SquallyNoSavePositionBehavior::create(owner); };
	this->componentDeserializers[ZFadeBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ZFadeBehavior::create(owner); };
	
	/*********************
	    Clippy
	*********************/
	this->componentDeserializers[DartLauncherClippyNopBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DartLauncherClippyNopBehavior::create(owner); };
	this->componentDeserializers[IsSwimmingClippyBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)IsSwimmingClippyBehavior::create(owner); };
	this->componentDeserializers[MechanicalFlailClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MechanicalFlailClippyAngleBehavior::create(owner); };
	this->componentDeserializers[PendulumBladeClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PendulumBladeClippyAngleBehavior::create(owner); };
	
	/*********************
	    Combat
	*********************/
	this->componentDeserializers[CurseOfTonguesTutorialBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CurseOfTonguesTutorialBehavior::create(owner); };
	this->componentDeserializers[FireballTutorialBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)FireballTutorialBehavior::create(owner); };
	this->componentDeserializers[IncrementHealthFlaskTutorialBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)IncrementHealthFlaskTutorialBehavior::create(owner); };
	this->componentDeserializers[TrainingHealTutorialBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TrainingHealTutorialBehavior::create(owner); };
	
	/*********************
	    Transportation
	*********************/
	this->componentDeserializers[EFURTransportationBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFURTransportationBehavior::create(owner); };

	// Helpers
	this->componentDeserializers[GeckyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)GeckyBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)GuanoBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoPetrifiedBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)GuanoPetrifiedBehaviorGroup::create(owner); };
	this->componentDeserializers[ScrappyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)ScrappyBehaviorGroup::create(owner); };
	this->componentDeserializers[ScrappyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)ScrappyCombatBehaviorGroup::create(owner); };
	
	/*********************
		Hexus
	*********************/

	// EF
	this->componentDeserializers[EFPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleABehavior::create(owner); };
	this->componentDeserializers[EFPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleBBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleCBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleDBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleEBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleFBehavior::create(owner); };
	this->componentDeserializers[EFPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EFPuzzleGBehavior::create(owner); };

	this->componentDeserializers[AraHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AraHexusBehavior::create(owner); };
	this->componentDeserializers[BardHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BardHexusBehavior::create(owner); };
	this->componentDeserializers[BlackbeardHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BlackbeardHexusBehavior::create(owner); };
	this->componentDeserializers[ChironHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ChironHexusBehavior::create(owner); };
	this->componentDeserializers[ElrielHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ElrielHexusBehavior::create(owner); };
	this->componentDeserializers[GrampsHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GrampsHexusBehavior::create(owner); };
	this->componentDeserializers[LianaHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LianaHexusBehavior::create(owner); };
	this->componentDeserializers[LycanHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LycanHexusBehavior::create(owner); };
	this->componentDeserializers[MarcelHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MarcelHexusBehavior::create(owner); };
	this->componentDeserializers[MatuHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MatuHexusBehavior::create(owner); };
	this->componentDeserializers[MinosHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MinosHexusBehavior::create(owner); };
	this->componentDeserializers[PolyphemusHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PolyphemusHexusBehavior::create(owner); };
	this->componentDeserializers[RobinHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)RobinHexusBehavior::create(owner); };
	this->componentDeserializers[TobenHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TobenHexusBehavior::create(owner); };
		
	// UR
	this->componentDeserializers[URPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleABehavior::create(owner); };
	this->componentDeserializers[URPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleBBehavior::create(owner); };
	this->componentDeserializers[URPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleCBehavior::create(owner); };
	this->componentDeserializers[URPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleDBehavior::create(owner); };
	this->componentDeserializers[URPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleEBehavior::create(owner); };
	this->componentDeserializers[URPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleFBehavior::create(owner); };
	this->componentDeserializers[URPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)URPuzzleGBehavior::create(owner); };

	this->componentDeserializers[AjaxHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AjaxHexusBehavior::create(owner); };
	this->componentDeserializers[AngelHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AngelHexusBehavior::create(owner); };
	this->componentDeserializers[AphroditeHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AphroditeHexusBehavior::create(owner); };
	this->componentDeserializers[AresHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AresHexusBehavior::create(owner); };
	this->componentDeserializers[AthenaHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AthenaHexusBehavior::create(owner); };
	this->componentDeserializers[CleopatraHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CleopatraHexusBehavior::create(owner); };
	this->componentDeserializers[GeyronHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GeyronHexusBehavior::create(owner); };
	this->componentDeserializers[GriffinHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GriffinHexusBehavior::create(owner); };
	this->componentDeserializers[HeraHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)HeraHexusBehavior::create(owner); };
	this->componentDeserializers[HorusHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)HorusHexusBehavior::create(owner); };
	this->componentDeserializers[PoseidonHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PoseidonHexusBehavior::create(owner); };
	this->componentDeserializers[RupertHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)RupertHexusBehavior::create(owner); };
	this->componentDeserializers[ThorHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ThorHexusBehavior::create(owner); };
	this->componentDeserializers[ZeusHexusBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ZeusHexusBehavior::create(owner); };

	/*********************
		ENTITIES / OVERWORLD
	*********************/

	// EF
	this->componentDeserializers[AraBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AraBehavior::create(owner); };
	this->componentDeserializers[CypressBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CypressBehavior::create(owner); };
	this->componentDeserializers[LycanBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LycanBehavior::create(owner); };
	this->componentDeserializers[KingGroggBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)KingGroggBehaviorGroup::create(owner); };
	this->componentDeserializers[OrcBomberBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrcBomberBehaviorGroup::create(owner); };

	// UR
	this->componentDeserializers[PoseidonBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PoseidonBehavior::create(owner); };
	this->componentDeserializers[RupertBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)RupertBehavior::create(owner); };

	/*********************
		COMBAT / IN-COMBAT
	*********************/

	// Helpers
	this->componentDeserializers[GuanoCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)GuanoCombatBehaviorGroup::create(owner); };
	this->componentDeserializers[GuanoPetrifiedCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (GameComponent*)GuanoPetrifiedCombatBehaviorGroup::create(owner); };
	
	// EF
	this->componentDeserializers[TrainingDummyCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TrainingDummyCombatBehavior::create(owner); };
	this->componentDeserializers[CentaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CentaurCombatBehavior::create(owner); };
	this->componentDeserializers[CyclopsCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CyclopsCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinGruntBoarCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GoblinGruntBoarCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GoblinShamanCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinWarriorPigCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GoblinWarriorPigCombatBehavior::create(owner); };
	this->componentDeserializers[GorgonCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GorgonCombatBehavior::create(owner); };
	this->componentDeserializers[KingGroggCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KingGroggCombatBehavior::create(owner); };
	this->componentDeserializers[OgreCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OgreCombatBehavior::create(owner); };
	this->componentDeserializers[OrcBomberCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrcBomberCombatBehavior::create(owner); };
	this->componentDeserializers[OrcGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrcGruntCombatBehavior::create(owner); };
	this->componentDeserializers[OrcSwordsmanCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrcSwordsmanCombatBehavior::create(owner); };
	this->componentDeserializers[OrcWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrcWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[OrthrusCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OrthrusCombatBehavior::create(owner); };
	this->componentDeserializers[TrollCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TrollCombatBehavior::create(owner); };

	// UR
	this->componentDeserializers[AnubisPupCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AnubisPupCombatBehavior::create(owner); };
	this->componentDeserializers[AnubisWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AnubisWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[LionessCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LionessCombatBehavior::create(owner); };
	this->componentDeserializers[LionManCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LionManCombatBehavior::create(owner); };
	this->componentDeserializers[MedusaCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MedusaCombatBehavior::create(owner); };
	this->componentDeserializers[MermaidCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MermaidCombatBehavior::create(owner); };
	this->componentDeserializers[MinotaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MinotaurCombatBehavior::create(owner); };
	this->componentDeserializers[MummyPriestCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MummyPriestCombatBehavior::create(owner); };
	this->componentDeserializers[MummyWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MummyWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[OsirisCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)OsirisCombatBehavior::create(owner); };
	this->componentDeserializers[TigressCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TigressCombatBehavior::create(owner); };
	this->componentDeserializers[TigerManCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TigerManCombatBehavior::create(owner); };

	// DM
	this->componentDeserializers[BarbarianCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BarbarianCombatBehavior::create(owner); };
	this->componentDeserializers[EarthElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EarthElementalCombatBehavior::create(owner); };
	this->componentDeserializers[EarthGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EarthGolemCombatBehavior::create(owner); };
	this->componentDeserializers[ForestGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ForestGolemCombatBehavior::create(owner); };
	this->componentDeserializers[KrampusCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KrampusCombatBehavior::create(owner); };
	this->componentDeserializers[RhinomanCombatBeahvior::MapKey] = [=](GameObject* owner) { return (GameComponent*)RhinomanCombatBeahvior::create(owner); };
	this->componentDeserializers[ShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ShamanCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalArcherCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalArcherCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalNecromancerCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalNecromancerCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[ThugCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ThugCombatBehavior::create(owner); };
	this->componentDeserializers[TikiGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)TikiGolemCombatBehavior::create(owner); };
	
	// CV
	this->componentDeserializers[AgnesCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AgnesCombatBehavior::create(owner); };
	this->componentDeserializers[GorillaCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GorillaCombatBehavior::create(owner); };
	this->componentDeserializers[JackCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)JackCombatBehavior::create(owner); };
	this->componentDeserializers[ReanimatedFighterCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ReanimatedFighterCombatBehavior::create(owner); };
	this->componentDeserializers[ReaperCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ReaperCombatBehavior::create(owner); };
	this->componentDeserializers[ScarecrowCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ScarecrowCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalBaronCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalBaronCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalPirateCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalPirateCombatBehavior::create(owner); };
	this->componentDeserializers[VampireLordCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)VampireLordCombatBehavior::create(owner); };
	this->componentDeserializers[VampiressCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)VampiressCombatBehavior::create(owner); };
	this->componentDeserializers[WerewolfCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)WerewolfCombatBehavior::create(owner); };
	this->componentDeserializers[WraithCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)WraithCombatBehavior::create(owner); };

	// BP
	this->componentDeserializers[CryogenCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)CryogenCombatBehavior::create(owner); };
	this->componentDeserializers[FrostFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)FrostFiendCombatBehavior::create(owner); };
	this->componentDeserializers[GoblinElfCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GoblinElfCombatBehavior::create(owner); };
	this->componentDeserializers[IceGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)IceGolemCombatBehavior::create(owner); };
	this->componentDeserializers[PenguinGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PenguinGruntCombatBehavior::create(owner); };
	this->componentDeserializers[PenguinWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)PenguinWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[SantaCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SantaCombatBehavior::create(owner); };
	this->componentDeserializers[SnowFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SnowFiendCombatBehavior::create(owner); };
	this->componentDeserializers[ToySoldierGoblinCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ToySoldierGoblinCombatBehavior::create(owner); };
	this->componentDeserializers[VikingCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)VikingCombatBehavior::create(owner); };
	this->componentDeserializers[WaterElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)WaterElementalCombatBehavior::create(owner); };
	this->componentDeserializers[YetiCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)YetiCombatBehavior::create(owner); };

	// DH
	this->componentDeserializers[AsmodeusCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AsmodeusCombatBehavior::create(owner); };
	this->componentDeserializers[DemonDragonCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonDragonCombatBehavior::create(owner); };
	this->componentDeserializers[DemonGhostCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonGhostCombatBehavior::create(owner); };
	this->componentDeserializers[DemonGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonGruntCombatBehavior::create(owner); };
	this->componentDeserializers[DemonRogueCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonRogueCombatBehavior::create(owner); };
	this->componentDeserializers[DemonShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonShamanCombatBehavior::create(owner); };
	this->componentDeserializers[DemonSwordsmanCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonSwordsmanCombatBehavior::create(owner); };
	this->componentDeserializers[DemonWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DemonWarriorCombatBehavior::create(owner); };
	this->componentDeserializers[FireElementalCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)FireElementalCombatBehavior::create(owner); };
	this->componentDeserializers[FireTigerCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)FireTigerCombatBehavior::create(owner); };
	this->componentDeserializers[LavaGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LavaGolemCombatBehavior::create(owner); };

	// LC
	this->componentDeserializers[BoneFiendCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BoneFiendCombatBehavior::create(owner); };
	this->componentDeserializers[HunterCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)HunterCombatBehavior::create(owner); };
	this->componentDeserializers[KingZulCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KingZulCombatBehavior::create(owner); };
	this->componentDeserializers[LazarusCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LazarusCombatBehavior::create(owner); };
	this->componentDeserializers[MysticCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)MysticCombatBehavior::create(owner); };
	this->componentDeserializers[ReanimatedPigCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ReanimatedPigCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalCleaverCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalCleaverCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalKnightCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalKnightCombatBehavior::create(owner); };
	this->componentDeserializers[SkeletalPriestessCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)SkeletalPriestessCombatBehavior::create(owner); };
	this->componentDeserializers[UndeadCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)UndeadCombatBehavior::create(owner); };
	this->componentDeserializers[ZombieCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ZombieCombatBehavior::create(owner); };
	this->componentDeserializers[ZombieElricCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ZombieElricCombatBehavior::create(owner); };

	// VS
	this->componentDeserializers[AbominationCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AbominationCombatBehavior::create(owner); };
	this->componentDeserializers[AssassinCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)AssassinCombatBehavior::create(owner); };
	this->componentDeserializers[BoneKnightCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)BoneKnightCombatBehavior::create(owner); };
	this->componentDeserializers[DarkTigerCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)DarkTigerCombatBehavior::create(owner); };
	this->componentDeserializers[EvilEyeCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)EvilEyeCombatBehavior::create(owner); };
	this->componentDeserializers[ExterminatorCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ExterminatorCombatBehavior::create(owner); };
	this->componentDeserializers[GargoyleCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)GargoyleCombatBehavior::create(owner); };
	this->componentDeserializers[LightningGolemCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)LightningGolemCombatBehavior::create(owner); };
	this->componentDeserializers[ShadeCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)ShadeCombatBehavior::create(owner); };
	this->componentDeserializers[VoidArcherCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)VoidArcherCombatBehavior::create(owner); };
	this->componentDeserializers[VoidDemonCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)VoidDemonCombatBehavior::create(owner); };
	this->componentDeserializers[WarlockCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)WarlockCombatBehavior::create(owner); };

	// Misc
	this->componentDeserializers[RamWeakenedCombatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)RamWeakenedCombatBehavior::create(owner); };
	
	/*********************
		Squalr
	*********************/

	this->componentDeserializers[KnownValueBarDoubleBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KnownValueBarDoubleBehavior::create(owner); };
	this->componentDeserializers[KnownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KnownValueBarFloatBehavior::create(owner); };
	this->componentDeserializers[KnownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)KnownValueBarInt32Behavior::create(owner); };
	this->componentDeserializers[UnknownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)UnknownValueBarFloatBehavior::create(owner); };
	this->componentDeserializers[UnknownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (GameComponent*)UnknownValueBarInt32Behavior::create(owner); };
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
			GameComponent* component = this->deserialize(GameComponentDeserializer::ComponentDeserializationRequestArgs(owner, next));

			if (component != nullptr)
			{
				owner->attachComponent(component);
			}
		}
	}
}

std::string PlatformerComponentDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyComponent;
}
