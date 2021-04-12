#pragma once
#include "Scenes/Platformer/AttachedBehavior/Combat/NoDefendBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/NoItemsBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/Tutorials/CurseOfTonguesTutorialBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/Tutorials/FireballTutorialBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/Tutorials/IncrementHealthFlaskTutorialBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/Tutorials/TrainingHealTutorialBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityPickPocketBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/MageCastBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Ally/EnemyBattleAllyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Overworld/EndianForest/KingGrogg/KingGroggBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Overworld/EndianForest/OrcBomber/OrcBomberBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/EnemyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/EnemyCombatBehaviors.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Critters/BirdBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/EndianForest/AraBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/EndianForest/CypressBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/EndianForest/LycanBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/UnderflowRuins/PoseidonBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/UnderflowRuins/RupertBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/HelperCombatBehaviors.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityNoGravityBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityPacingBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityRunBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/ScrappyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Gecky/GeckyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/GuanoPetrified/GuanoPetrifiedBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviors.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/FriendlyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Shopkeepers/ShopkeeperBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Transportation/EFURTransportationBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Petrification/EntityPetrificationBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Combat/SquallyCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyNoSavePositionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/SquallyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityDisarmedBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Bridges/BridgeBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Clippy/DartLauncherClippyNopBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Clippy/IsSwimmingClippyBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Clippy/MechanicalFlailClippyAngleBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Clippy/PendulumBladeClippyAngleBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/DisabledPortal.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Fade/ZFadeBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Illusions/IllusionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/LockedPortal.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/Petrification/PetrificationLinkBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/IOU/FirstIOUFound.h"
#include "Scenes/Platformer/AttachedBehavior/Squalr/KnownValueScanDouble/KnownValueBarDoubleBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squalr/KnownValueScanFloat/KnownValueBarFloatBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squalr/KnownValueScanInt32/KnownValueBarInt32Behavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squalr/UnknownValueScanFloat/UnknownValueBarFloatBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squalr/UnknownValueScanInt32/UnknownValueBarInt32Behavior.h"
