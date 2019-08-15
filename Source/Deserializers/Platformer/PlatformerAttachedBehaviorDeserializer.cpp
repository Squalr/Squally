#include "PlatformerAttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/AttachedBehavior/PlatformerAttachedBehavior.h"

using namespace cocos2d;

PlatformerAttachedBehaviorDeserializer* PlatformerAttachedBehaviorDeserializer::create()
{
	PlatformerAttachedBehaviorDeserializer* instance = new PlatformerAttachedBehaviorDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerAttachedBehaviorDeserializer::PlatformerAttachedBehaviorDeserializer() : super()
{
	this->attachedBehaviorDeserializers = std::map<std::string, std::function<AttachedBehavior*(GameObject*)>>();

	this->attachedBehaviorDeserializers[EnemyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EnemyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[FirstIOUFound::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FirstIOUFound::create(owner); };
	this->attachedBehaviorDeserializers[FlyBotBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FlyBotBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[NpcBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)NpcBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[RestorePotionTutorial::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RestorePotionTutorial::create(owner); };
	this->attachedBehaviorDeserializers[SquallyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyCombatBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyCombatBehaviorGroup::create(owner); };
	
	// this->attachedBehaviorDeserializers[CyrogenCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CyrogenCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FrostFiendCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FrostFiendCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GoblinElfCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinElfCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[IceGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)IceGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PenguinGruntCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PenguinGruntCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PenguinWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PenguinWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SantaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SantaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SnowFiendCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SnowFiendCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ToySoldierGoblinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ToySoldierGoblinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VikingCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VikingCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[WaterElementalCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)WaterElementalCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[YetiCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)YetiCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SnowmanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SnowmanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[YetiBabyCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)YetiBabyCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AspenCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AspenCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AsterCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AsterCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BodomCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BodomCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CookieCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CookieCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CooperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CooperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[IrmikCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)IrmikCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[JinglesCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)JinglesCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[JuniperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)JuniperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KringleCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KringleCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[NessieCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)NessieCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessPepperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessPepperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ThatcherCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ThatcherCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TheldarCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TheldarCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TinselCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TinselCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AgnesCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AgnesCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[JackCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)JackCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ReaperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ReaperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ScarecrowCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ScarecrowCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalPirateCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalPirateCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ThugCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ThugCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VampireLordCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VampireLordCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VampiressCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VampiressCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[WerewolfCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)WerewolfCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[WraithCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)WraithCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ZombieCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ZombieCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ZombieElricCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ZombieElricCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KnightCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KnightCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ElricCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ElricCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GarinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GarinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GauntCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GauntCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KingRedsongCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KingRedsongCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KingRedsongSlimeCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KingRedsongSlimeCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LeopoldCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LeopoldCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LeroyCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LeroyCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MabelCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MabelCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MerlinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MerlinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessOpalCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessOpalCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RavenCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RavenCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RogasCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RogasCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ThurstanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ThurstanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TyraciusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TyraciusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AsmodeusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AsmodeusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonDragonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonDragonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonGhostCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonGhostCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonGruntCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonGruntCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonRogueCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonRogueCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonShamanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonShamanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonSwordsmanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonSwordsmanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DemonWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DemonWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FireElementalCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FireElementalCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FireTigerCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FireTigerCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KrampusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KrampusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LavaGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LavaGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AppleCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AppleCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CritterDemonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CritterDemonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FlyBotCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FlyBotCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AshCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AshCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BrineCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BrineCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CelesteCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CelesteCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CindraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CindraCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DrakCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DrakCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[IgneusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)IgneusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LuciferCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LuciferCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MagnusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MagnusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessMittensCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessMittensCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RagnisCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RagnisCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RupertCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RupertCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RustyCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RustyCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ScaldorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ScaldorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CentaurCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CentaurCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CyclopsCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CyclopsCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GoblinGruntBoarCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinGruntBoarCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GoblinShamanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinShamanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GoblinWarriorPigCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinWarriorPigCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KingGroggCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KingGroggCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OgreCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OgreCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OrcBomberCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcBomberCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcGruntCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcGruntCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OrcSwordsmanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcSwordsmanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OrcWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TrollCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TrollCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GoblinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TurtleCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TurtleCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AppoloCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AppoloCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AraCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BardCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BardCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BlackbeardCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BlackbeardCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ChironCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ChironCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ElrielCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ElrielCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GrampsCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GrampsCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[QueenLianaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)QueenLianaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LycanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LycanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MinosCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MinosCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PolyphemusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PolyphemusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MatuCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MatuCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RobinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RobinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TobenCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TobenCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BoneFiendCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BoneFiendCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[HunterCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)HunterCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[KingZulCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KingZulCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MysticCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MysticCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ReanimatedFighterCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ReanimatedFighterCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ReanimatedPigCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ReanimatedPigCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalBaronCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalBaronCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalCleaverCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalCleaverCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalKnightCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalKnightCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalPriestessCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalPriestessCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[UndeadCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)UndeadCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GhostCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GhostCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GrimCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GrimCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AmeliaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AmeliaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AzmusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AzmusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DudlyCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DudlyCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GarrickCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GarrickCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[JohannCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)JohannCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[NecronCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)NecronCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessNebeaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessNebeaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RogerCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RogerCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ThionCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ThionCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[UrsulaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)UrsulaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VesuviusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VesuviusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ViperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ViperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ZanaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ZanaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ZelinaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ZelinaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BarbarianCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BarbarianCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[EarthElementalCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EarthElementalCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[EarthGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EarthGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ForestGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ForestGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GorillaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GorillaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LightningGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LightningGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RhinomanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RhinomanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ShamanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ShamanCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalArcherCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalArcherCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalNecromancerCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalNecromancerCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SkeletalWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SkeletalWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TikiGolemCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TikiGolemCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GeckoCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GeckoCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AlderCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AlderCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BonnieCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BonnieCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BrockCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BrockCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BurchCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BurchCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CypressCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CypressCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FinchCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FinchCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[FrayaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FrayaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[JasperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)JasperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MildredCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MildredCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OliveCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OliveCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PrincessDawnCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PrincessDawnCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RakaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RakaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[SarudeCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SarudeCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ShenCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ShenCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AnubisPupCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AnubisPupCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AnubisWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AnubisWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LionManCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LionManCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LionessCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LionessCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MedusaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MedusaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MermaidCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MermaidCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MinotaurCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MinotaurCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MummyPriestCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MummyPriestCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MummyWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MummyWarriorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[OsirisCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OsirisCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TigerManCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TigerManCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[TigressCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TigressCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MummyCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MummyCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AjaxCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AjaxCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AngelCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AngelCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AphroditeCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AphroditeCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AresCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AresCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AthenaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AthenaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[CleopatraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CleopatraCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GeryonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GeryonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GriffinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GriffinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[HadesCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)HadesCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[HeraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)HeraCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[HorusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)HorusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PoseidonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PoseidonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ThorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ThorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ZeusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ZeusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AbominationCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AbominationCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AssassinCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AssassinCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BoneKnightCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BoneKnightCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[DarkTigerCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DarkTigerCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[EvilEyeCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EvilEyeCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ExterminatorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ExterminatorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GargoyleCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GargoyleCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ShadeCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ShadeCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VoidArcherCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VoidArcherCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[VoidDemonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)VoidDemonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[WarlockCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)WarlockCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[ProfessorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ProfessorCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RobotCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RobotCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[AtreusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AtreusCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[BancroftCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BancroftCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[GodivaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GodivaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[IlliaCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)IlliaCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[LeonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LeonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MaraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MaraCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[MarcelCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MarcelCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[PiperCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PiperCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[QueenEliseCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)QueenEliseCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RadonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RadonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[RalstonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RalstonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[XenonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)XenonCombatBehavior::create(owner); };
	// this->attachedBehaviorDeserializers[YsaraCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)YsaraCombatBehavior::create(owner); };
}

PlatformerAttachedBehaviorDeserializer::~PlatformerAttachedBehaviorDeserializer()
{
}

void PlatformerAttachedBehaviorDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string attachedBehaviorName = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAttachedBehavior, Value("")).asString();
	
	if (!attachedBehaviorName.empty())
	{
		std::vector<std::string> attachedBehaviors = StrUtils::splitOn(attachedBehaviorName, ", ");
		
		for (auto it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
		{
			AttachedBehavior* attachedBehavior = this->deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs(owner, *it));

			if (attachedBehavior != nullptr)
			{
				owner->attachBehavior(attachedBehavior);
			}
		}
	}
}

std::string PlatformerAttachedBehaviorDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyAttachedBehavior;
}
