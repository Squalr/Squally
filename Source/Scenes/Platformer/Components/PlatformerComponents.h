#pragma once
#include "Scenes/Platformer/Components/Combat/NoDefendBehavior.h"
#include "Scenes/Platformer/Components/Combat/NoItemsBehavior.h"
#include "Scenes/Platformer/Components/Combat/Tutorials/CurseOfTonguesTutorialBehavior.h"
#include "Scenes/Platformer/Components/Combat/Tutorials/FireballTutorialBehavior.h"
#include "Scenes/Platformer/Components/Combat/Tutorials/IncrementHealthFlaskTutorialBehavior.h"
#include "Scenes/Platformer/Components/Combat/Tutorials/TrainingHealTutorialBehavior.h"
#include "Scenes/Platformer/Components/Entities/Abilities/EntityPickPocketBehavior.h"
#include "Scenes/Platformer/Components/Entities/Cinematic/MageCastBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Ally/EnemyBattleAllyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EndianForest/GoblinShaman/GoblinShamanBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EndianForest/KingGrogg/KingGroggBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EndianForest/OrcBomber/OrcBomberBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/Generic/MainhandThrow/MainhandThrowOutOfCombatAttackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/UnderflowRuins/KillingMachine/KillingMachineBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/EnemyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Enemies/EnemyCombatBehaviors.h"
#include "Scenes/Platformer/Components/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Critters/BirdBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/EndianForest/AraBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/EndianForest/JasperBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/EndianForest/LycanBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/UnderflowRuins/PoseidonBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/UnderflowRuins/RupertBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviors.h"
#include "Scenes/Platformer/Components/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/FriendlyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Shopkeepers/ShopkeeperBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Transportation/EFURTransportationBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperCombatBehaviors.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Scrappy/Combat/ScrappyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Scrappy/ScrappyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Guano/GuanoBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/GuanoPetrified/GuanoPetrifiedBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Mounts/GatlingGunBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityNoGravityBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityPacingBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityRunBehavior.h"
#include "Scenes/Platformer/Components/Entities/Petrification/EntityPetrificationBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Combat/SquallyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyNoSavePositionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/SquallyBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityDisarmedBehavior.h"
#include "Scenes/Platformer/Components/Objects/Bridges/BridgeBehavior.h"
#include "Scenes/Platformer/Components/Objects/Clippy/DartLauncherClippyNopBehavior.h"
#include "Scenes/Platformer/Components/Objects/Clippy/IsSwimmingClippyBehavior.h"
#include "Scenes/Platformer/Components/Objects/Clippy/MechanicalFlailClippyAngleBehavior.h"
#include "Scenes/Platformer/Components/Objects/Clippy/PendulumBladeClippyAngleBehavior.h"
#include "Scenes/Platformer/Components/Objects/DisabledPortal.h"
#include "Scenes/Platformer/Components/Objects/Fade/ZFadeBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/IllusionBehavior.h"
#include "Scenes/Platformer/Components/Objects/LockedPortal.h"
#include "Scenes/Platformer/Components/Objects/Petrification/PetrificationLinkBehavior.h"
#include "Scenes/Platformer/Components/IOU/FirstIOUFound.h"
#include "Scenes/Platformer/Components/Squalr/KnownValueScanDouble/KnownValueBarDoubleBehavior.h"
#include "Scenes/Platformer/Components/Squalr/KnownValueScanFloat/KnownValueBarFloatBehavior.h"
#include "Scenes/Platformer/Components/Squalr/KnownValueScanInt32/KnownValueBarInt32Behavior.h"
#include "Scenes/Platformer/Components/Squalr/UnknownValueScanFloat/UnknownValueBarFloatBehavior.h"
#include "Scenes/Platformer/Components/Squalr/UnknownValueScanInt32/UnknownValueBarInt32Behavior.h"
