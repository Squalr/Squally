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

	this->attachedBehaviorDeserializers[AgroBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AgroBehavior::create(owner); };
	this->attachedBehaviorDeserializers[BridgeBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)BridgeBehavior::create(owner); };
	this->attachedBehaviorDeserializers[DisabledPortal::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)DisabledPortal::create(owner); };
	this->attachedBehaviorDeserializers[EnemyBattleAllyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EnemyBattleAllyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EnemyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EnemyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityDisarmedBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityDisarmedBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityNoGravityBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityNoGravityBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityPacingBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityPacingBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityPetrificationBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityPetrificationBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityPickPocketBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityPickPocketBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityRunBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EntityRunBehavior::create(owner); };
	this->attachedBehaviorDeserializers[DispelIllusionBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)DispelIllusionBehavior::create(owner); };
	this->attachedBehaviorDeserializers[FriendlyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)FriendlyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[FirstIOUFound::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)FirstIOUFound::create(owner); };
	this->attachedBehaviorDeserializers[IllusionBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)IllusionBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)LookAtSquallyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LookAtSquallyBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)LookAtSquallyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LockedPortal::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)LockedPortal::create(owner); };
	this->attachedBehaviorDeserializers[MageCastBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MageCastBehavior::create(owner); };
	this->attachedBehaviorDeserializers[NoDefendBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)NoDefendBehavior::create(owner); };
	this->attachedBehaviorDeserializers[NoItemsBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)NoItemsBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PetrificationLinkBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)PetrificationLinkBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ShopkeeperBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ShopkeeperBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyCombatBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyNoSavePositionBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyNoSavePositionBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ZFadeBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ZFadeBehavior::create(owner); };
	
	/*********************
	    Clippy
	*********************/
	this->attachedBehaviorDeserializers[DartLauncherClippyNopBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)DartLauncherClippyNopBehavior::create(owner); };
	this->attachedBehaviorDeserializers[IsSwimmingClippyBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)IsSwimmingClippyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MechanicalFlailClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MechanicalFlailClippyAngleBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PendulumBladeClippyAngleBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)PendulumBladeClippyAngleBehavior::create(owner); };
	
	/*********************
	    Combat
	*********************/
	this->attachedBehaviorDeserializers[FireballTutorialBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)FireballTutorialBehavior::create(owner); };
	this->attachedBehaviorDeserializers[IncrementHealthFlaskTutorialBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)IncrementHealthFlaskTutorialBehavior::create(owner); };
	this->attachedBehaviorDeserializers[TrainingHealTutorialBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)TrainingHealTutorialBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ReflectTutorial::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ReflectTutorial::create(owner); };
	
	/*********************
	    Transportation
	*********************/
	this->attachedBehaviorDeserializers[EFURTransportationBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFURTransportationBehavior::create(owner); };

	// Helpers
	this->attachedBehaviorDeserializers[GuanoBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GuanoBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[GuanoPetrifiedBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GuanoPetrifiedBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[ScrappyBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ScrappyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[ScrappyCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ScrappyCombatBehaviorGroup::create(owner); };
	
	/*********************
		Hexus
	*********************/

	// EF
	this->attachedBehaviorDeserializers[EFPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleABehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleBBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleCBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleDBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleEBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleFBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EFPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)EFPuzzleGBehavior::create(owner); };

	this->attachedBehaviorDeserializers[AraHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AraHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[BardHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)BardHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[BlackbeardHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)BlackbeardHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ChironHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ChironHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ElrielHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ElrielHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GrampsHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GrampsHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LianaHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)LianaHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LycanHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)LycanHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MarcelHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MarcelHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MatuHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MatuHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MinosHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MinosHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PolyphemusHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)PolyphemusHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[RobinHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)RobinHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[TobenHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)TobenHexusBehavior::create(owner); };
		
	// UR
	this->attachedBehaviorDeserializers[URPuzzleABehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleABehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleBBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleBBehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleCBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleCBehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleDBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleDBehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleEBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleEBehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleFBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleFBehavior::create(owner); };
	this->attachedBehaviorDeserializers[URPuzzleGBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)URPuzzleGBehavior::create(owner); };

	this->attachedBehaviorDeserializers[AjaxHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AjaxHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[AngelHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AngelHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[AphroditeHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AphroditeHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[AresHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AresHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[AthenaHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AthenaHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[CleopatraHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)CleopatraHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GeyronHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GeyronHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GriffinHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GriffinHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[HeraHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)HeraHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[HorusHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)HorusHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PoseidonHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)PoseidonHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[RupertHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)RupertHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ThorHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ThorHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ZeusHexusBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)ZeusHexusBehavior::create(owner); };

	/*********************
		ENTITIES / OVERWORLD
	*********************/

	// Endian forest
	this->attachedBehaviorDeserializers[AraBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AraBehavior::create(owner); };
	this->attachedBehaviorDeserializers[CypressBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)CypressBehavior::create(owner); };
	this->attachedBehaviorDeserializers[KingGroggBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)KingGroggBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[OrcBomberBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrcBomberBehaviorGroup::create(owner); };

	/*********************
		COMBAT / IN-COMBAT
	*********************/

	// Helpers
	this->attachedBehaviorDeserializers[GuanoCombatBehaviorGroup::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GuanoCombatBehaviorGroup::create(owner); };
	
	// EF
	this->attachedBehaviorDeserializers[TrainingDummyCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)TrainingDummyCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[CentaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)CentaurCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[CyclopsCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)CyclopsCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinGruntBoarCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinGruntBoarCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinShamanCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinShamanCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinWarriorPigCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinWarriorPigCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GorgonCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)GorgonCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[KingGroggCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)KingGroggCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OgreCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OgreCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcBomberCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrcBomberCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcGruntCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrcGruntCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcSwordsmanCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrcSwordsmanCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrcWarriorCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrthrusCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)OrthrusCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[TrollCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)TrollCombatBehavior::create(owner); };

	// UR
	this->attachedBehaviorDeserializers[AnubisPupCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AnubisPupCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[AnubisWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)AnubisWarriorCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MinotaurCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MinotaurCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MummyWarriorCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)MummyWarriorCombatBehavior::create(owner); };

	// Misc
	this->attachedBehaviorDeserializers[RamWeakenedCombatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)RamWeakenedCombatBehavior::create(owner); };
	
	/*********************
		Squalr
	*********************/

	this->attachedBehaviorDeserializers[KnownValueBarDoubleBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)KnownValueBarDoubleBehavior::create(owner); };
	this->attachedBehaviorDeserializers[KnownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)KnownValueBarFloatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[KnownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)KnownValueBarInt32Behavior::create(owner); };
	this->attachedBehaviorDeserializers[UnknownValueBarFloatBehavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)UnknownValueBarFloatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[UnknownValueBarInt32Behavior::MapKey] = [=](GameObject* owner) { return (AttachedBehavior*)UnknownValueBarInt32Behavior::create(owner); };
}

PlatformerAttachedBehaviorDeserializer::~PlatformerAttachedBehaviorDeserializer()
{
}

void PlatformerAttachedBehaviorDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string attachedBehaviorName = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAttachedBehavior, Value("")).asString();
	
	if (!attachedBehaviorName.empty())
	{
		std::vector<std::string> attachedBehaviors = StrUtils::splitOn(attachedBehaviorName, ", ", false);
		
		for (auto next : attachedBehaviors)
		{
			AttachedBehavior* attachedBehavior = this->deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs(owner, next));

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
