#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/FragGrenade/FragGrenade.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/LargeBomb/LargeBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/PepperBomb/PepperBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/MeteoriteBomb/MeteoriteBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SmallBomb/SmallBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SpikedBomb/SpikedBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SteelBomb/SteelBomb.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/GreaterHealthPotion/GreaterHealthPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/HealthPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/SuperiorHealthFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/IncrementManaFlask/IncrementManaFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion/ManaPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/GreaterManaPotion/GreaterManaPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/SuperiorManaFlask/SuperiorManaFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Special/DualElixir/DualElixir.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/Bamboo.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/Meteorite.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/Pepper.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/PhoenixFeather.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/Stinger.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/StrongChitin.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/BombReagents/WeakChitin.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Bone.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Coal.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Copper.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Crystal.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Diamond.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Emerald.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Gold.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Iron.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Mithril.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Obsidian.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Quartz.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Ruby.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Sapphire.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/Sulfur.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Ores/VoidCrystal.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Acorn.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/BlackBlood.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/BlackMushroom.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Clover.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/DarkSeed.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/DemonRoot.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Feather.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/FrostBerries.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/GoldWeed.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Honey.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Mandrake.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/RatTail.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/SandRoot.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/Snowball.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/PotionReagents/VoidFlower.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Special/HeartOfFire.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Special/HeartOfShadow.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Wood/DarkWood.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Wood/LightWood.h"
#include "Scenes/Platformer/Inventory/Items/Crafting/Wood/Wood.h"
#include "Scenes/Platformer/Inventory/Items/Error/MissingNo.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/AquaMarineEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/CrystalEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/EmeraldEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/HeartEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/RoseEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/SapphireEarrings.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/AmethystNecklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/AquaMarineNecklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/EmeraldPendant.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/GlowingPendant.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/HolyNecklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/MarineNecklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/SapphireNecklace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/TopazPendant.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/BrocksHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/CowboyHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/GardenersHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/JesterHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/OrnateHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/RoyalCrown.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/SamuraiHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/ShamanTiara.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/SnailShell.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/TheldarsHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/Tiara.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/TopHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Deprecated/ToySoldierHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier1/BucketHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier1/GrandpasLuckyHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier1/OldShoe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier2/AcolytesCap.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier2/ArchersHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier2/CopperHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier2/VikingHelmet.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/BarbedHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/ConchHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/GoldenDungHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/MagesHatBlue.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/MagesHatRed.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier3/WolfHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/GuardsHelmet.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/GunnersHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/JoustingHelmet.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/LeatherCap.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/Monocle.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/SteelHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier4/WitchesHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/ReindeerHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/SantaHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WizardsHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WizardsHatArcane.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WizardsHatEarth.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WizardsHatShadow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WizardsHatWater.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier5/WolfHatWhite.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier6/DemonShell.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier6/DepressingWig.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier6/DraksHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier6/SnailShellSpiked.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier6/Turban.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier7/NecrobatHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier7/PirateHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier7/PriestHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier7/TheGoldenEagle.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier7/TigersBane.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier8/WarlocksHeaddress.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Tier8/WoodenPikeHelm.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/DarkHeartBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/EmeraldBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/GarnetBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/HeartBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/MarineBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/SapphireBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/ShellBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/SkullBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/SoulBand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Shields/WoodenShield.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/Axe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/BoneAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/CopperAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/CrystalAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/DemonicAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/GoldenAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/MithrilAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/SteelAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/VoidAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/WoodenAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/BoneBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/CrystalBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/DemonicBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/GoldenBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/HuntersBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/IvyBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/SteelBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/VoidBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/WoodenBow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/BoneHammer.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/CopperMallet.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/CrystalMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/DemonicMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/GoldenMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/MithrilMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/SteelMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/VoidMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/WoodenClub.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/AshenBlade.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/Bludgeon.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/CandySword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/ChieftainsWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/Dreadmourn.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/FireSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/Frostbane.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/FrostAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/Scythe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/SerpentWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/TaserRod.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/TheButcher.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/Timmy.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/WitchesWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Special/WitchingMace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/BoneSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CopperSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CrystalSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/DemonicSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/GoldenSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/MithrilSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/SteelSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/VoidSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/WoodenSword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/BoneWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/CrystalWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/DemonicWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/EmeraldWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/GoldenWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/QuartzWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/SapphireWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/VoidWand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/WoodenWand.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/BallmerPeaks/IceKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/BallmerPeaks/FrostKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/BallmerPeaks/FrozenKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/CastleValgrind/CryptKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/HeliumBomb.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/DemonKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/DemonHeart.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/HellKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/UnstableElement.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/FirewallFissure/UnstableConcoction.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/LetterForThePrincess.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/TrainTicket.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/EndianForest/MagesGuildPrisonKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/EndianForest/RamWheel.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/EndianForest/TownKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/LambdaCrypts/AncientKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/LambdaCrypts/RustyKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/VoidStar/MayanGemBlueItem.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/VoidStar/MayanGemPurpleItem.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/VoidStar/MayanGemRedItem.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/MinesKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/FountainRoomKey.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Maps/EndianForest/TempleMap.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Dismantle/DismantleRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/HeliumBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/FragGrenadeRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/LargeBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/MeteoriteBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/PepperBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/SmallBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/SpikedBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/SteelBombRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/DualElixirRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/GreaterHealthPotionRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/GreaterManaPotionRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/HealthPotionRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/IncrementHealthFlaskRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/IncrementManaFlaskRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/ManaPotionRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/PotionRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/SuperiorHealthFlaskRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/SuperiorManaFlaskRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/IncrementHealthFlaskRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Special/DemonHeartPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteCopperToIron.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteCopperToQuartzRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteQuartzToEmerald.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteWoodToCoalRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/BoneAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/CopperAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/CrystalAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/DemonicAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/GoldenAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/MithrilAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/SteelAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/VoidAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/WoodenAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BoneBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/CrystalBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/DemonicBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/GoldenBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/HuntersBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/IvyBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/SteelBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/VoidBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/WoodenBowPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/BoneHammerPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/CopperMalletPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/CrystalMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/DemonicMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/GoldenMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MithrilMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/SteelMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/VoidMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/WoodenClubPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/AshenBladePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/BludgeonPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/CandySwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/ChieftainsWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/DreadmournPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/FireSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/FrostAxePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/FrostbanePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/ScythePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/TaserRodPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/TimmyPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/TheButcherPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/SerpentWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/WitchingMacePlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/BoneSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/CopperSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/CrystalSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/DemonicSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/GoldenSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/MithrilSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SteelSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/VoidSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/WoodenSwordPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/BoneWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/CrystalWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/DemonicWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/EmeraldWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/GoldenWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/QuartzWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/SapphireWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/VoidWandPlans.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WoodenWandPlans.h"