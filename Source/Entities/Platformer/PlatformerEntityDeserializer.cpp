#include "PlatformerEntityDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableObject.h"
#include "Entities/Platformer/Squally/Squally.h"

////////////////////////////////////
// BEGIN: THIS CODE IS GENERATED: //
////V////V////V////V////V////V////V/

#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Viking.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/YetiBaby.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aspen.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Bodom.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cookie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cooper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Irmik.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Jingles.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Juniper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Kringle.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Nessie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/PrincessPepper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Thatcher.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Theldar.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Tinsel.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Agnes.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Jack.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Reaper.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Scarecrow.h"
#include "Entities/Platformer/Enemies/CastleValgrind/SkeletalPirate.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Thug.h"
#include "Entities/Platformer/Enemies/CastleValgrind/VampireLord.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Vampiress.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Werewolf.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Wraith.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Zombie.h"
#include "Entities/Platformer/Enemies/CastleValgrind/ZombieElric.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Knight.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Princess.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Elric.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Garin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Gaunt.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsong.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsongSlime.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leopold.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leroy.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Mabel.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Merlin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/PrincessOpal.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Raven.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Rogas.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Thurstan.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Tyracius.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/Asmodeus.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonDragon.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonGhost.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonGrunt.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonRogue.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonShaman.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonSwordsman.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonWarrior.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/FireElemental.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/FireTiger.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/Krampus.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/LavaGolem.h"
#include "Entities/Platformer/Helpers/DaemonsHallow/Apple.h"
#include "Entities/Platformer/Helpers/DaemonsHallow/CritterDemon.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Ash.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Brine.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Celeste.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Cindra.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Drak.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Igneus.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Lucifer.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Magnus.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Pan.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/PrincessMittens.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Ragnis.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Rupert.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Rusty.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Scaldor.h"
#include "Entities/Platformer/Enemies/EndianForest/Centaur.h"
#include "Entities/Platformer/Enemies/EndianForest/Cyclops.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinGruntBoar.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinWarriorPig.h"
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Enemies/EndianForest/Ogre.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcBomber.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcGrunt.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcSwordsman.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcWarrior.h"
#include "Entities/Platformer/Enemies/EndianForest/Troll.h"
#include "Entities/Platformer/Helpers/EndianForest/Goblin.h"
#include "Entities/Platformer/Helpers/EndianForest/Turtle.h"
#include "Entities/Platformer/Npcs/EndianForest/Appolo.h"
#include "Entities/Platformer/Npcs/EndianForest/Ara.h"
#include "Entities/Platformer/Npcs/EndianForest/Bard.h"
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Npcs/EndianForest/Elriel.h"
#include "Entities/Platformer/Npcs/EndianForest/Gramps.h"
#include "Entities/Platformer/Npcs/EndianForest/Liana.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Npcs/EndianForest/Minos.h"
#include "Entities/Platformer/Npcs/EndianForest/Polyphemus.h"
#include "Entities/Platformer/Npcs/EndianForest/PrincessMatu.h"
#include "Entities/Platformer/Npcs/EndianForest/Robin.h"
#include "Entities/Platformer/Npcs/EndianForest/Toben.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/BoneFiend.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Hunter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Mystic.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Ghost.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Grim.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Amelia.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Azmus.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Dudly.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Garrick.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Johann.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Necron.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/PrincessNebea.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Roger.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Thion.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Ursula.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Vesuvius.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Viper.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zana.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zelina.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Barbarian.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/EarthElemental.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/EarthGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/ForestGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Gorilla.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/LightningGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Rhinoman.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Shaman.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalArcher.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalNecromancer.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalWarrior.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/TikiGolem.h"
#include "Entities/Platformer/Helpers/SeaSharpCaverns/Gecko.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Alder.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Bonnie.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Brock.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Burch.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Cypress.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Finch.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Fraya.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Jasper.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Mildred.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Olive.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/PrincessDawn.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Raka.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Shen.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisPup.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/LionMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Lioness.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Medusa.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Mermaid.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Minotaur.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyPriest.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Osiris.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/TigerMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Tigress.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/Mummy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ajax.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Angel.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Aphrodite.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ares.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Athena.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Cleopatra.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Geryon.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Griffin.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hades.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hera.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Horus.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Poseidon.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Thor.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Zeus.h"
#include "Entities/Platformer/Enemies/VoidStar/Abomination.h"
#include "Entities/Platformer/Enemies/VoidStar/Assassin.h"
#include "Entities/Platformer/Enemies/VoidStar/BoneKnight.h"
#include "Entities/Platformer/Enemies/VoidStar/DarkTiger.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/VoidStar/Exterminator.h"
#include "Entities/Platformer/Enemies/VoidStar/Gargoyle.h"
#include "Entities/Platformer/Enemies/VoidStar/Shade.h"
#include "Entities/Platformer/Enemies/VoidStar/VoidArcher.h"
#include "Entities/Platformer/Enemies/VoidStar/VoidDemon.h"
#include "Entities/Platformer/Enemies/VoidStar/Warlock.h"
#include "Entities/Platformer/Helpers/VoidStar/Professor.h"
#include "Entities/Platformer/Helpers/VoidStar/Robot.h"
#include "Entities/Platformer/Npcs/VoidStar/Atreus.h"
#include "Entities/Platformer/Npcs/VoidStar/Bancroft.h"
#include "Entities/Platformer/Npcs/VoidStar/Godiva.h"
#include "Entities/Platformer/Npcs/VoidStar/Illia.h"
#include "Entities/Platformer/Npcs/VoidStar/Leon.h"
#include "Entities/Platformer/Npcs/VoidStar/Mara.h"
#include "Entities/Platformer/Npcs/VoidStar/Marcel.h"
#include "Entities/Platformer/Npcs/VoidStar/Piper.h"
#include "Entities/Platformer/Npcs/VoidStar/QueenElise.h"
#include "Entities/Platformer/Npcs/VoidStar/Radon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ralston.h"
#include "Entities/Platformer/Npcs/VoidStar/Xenon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ysara.h"

////Y////Y////Y////Y////Y////Y////Y/
// END: THIS CODE IS GENERATED    //
////////////////////////////////////

using namespace cocos2d;

const std::string PlatformerEntityDeserializer::KeyTypeEntity = "entity";

PlatformerEntityDeserializer* PlatformerEntityDeserializer::instance = nullptr;

void PlatformerEntityDeserializer::registerGlobalNode()
{
	// Register this class globally so that it can always listen for events
	GlobalDirector::getInstance()->registerGlobalNode(PlatformerEntityDeserializer::getInstance());
}

PlatformerEntityDeserializer* PlatformerEntityDeserializer::getInstance()
{
	if (PlatformerEntityDeserializer::instance == nullptr)
	{
		PlatformerEntityDeserializer::instance = new PlatformerEntityDeserializer();

		instance->autorelease();
	}

	return instance;
}

PlatformerEntityDeserializer::PlatformerEntityDeserializer()
{
	this->deserializers = std::map<std::string, std::function<SerializableObject*(ValueMap)>>();

	this->deserializers[Squally::MapKeySqually] = [=](ValueMap properties) { return (SerializableObject*)Squally::deserialize(properties); };
	
	////////////////////////////////////
	// BEGIN: THIS CODE IS GENERATED: //
	////X////X////X////X////X////X////X/

	this->deserializers[Cyrogen::MapKeyCyrogen] = [=](ValueMap properties) { return (SerializableObject*)Cyrogen::deserialize(properties); };
	this->deserializers[FrostFiend::MapKeyFrostFiend] = [=](ValueMap properties) { return (SerializableObject*)FrostFiend::deserialize(properties); };
	this->deserializers[GoblinElf::MapKeyGoblinElf] = [=](ValueMap properties) { return (SerializableObject*)GoblinElf::deserialize(properties); };
	this->deserializers[IceGolem::MapKeyIceGolem] = [=](ValueMap properties) { return (SerializableObject*)IceGolem::deserialize(properties); };
	this->deserializers[PenguinGrunt::MapKeyPenguinGrunt] = [=](ValueMap properties) { return (SerializableObject*)PenguinGrunt::deserialize(properties); };
	this->deserializers[PenguinWarrior::MapKeyPenguinWarrior] = [=](ValueMap properties) { return (SerializableObject*)PenguinWarrior::deserialize(properties); };
	this->deserializers[Santa::MapKeySanta] = [=](ValueMap properties) { return (SerializableObject*)Santa::deserialize(properties); };
	this->deserializers[SnowFiend::MapKeySnowFiend] = [=](ValueMap properties) { return (SerializableObject*)SnowFiend::deserialize(properties); };
	this->deserializers[ToySoldierGoblin::MapKeyToySoldierGoblin] = [=](ValueMap properties) { return (SerializableObject*)ToySoldierGoblin::deserialize(properties); };
	this->deserializers[Viking::MapKeyViking] = [=](ValueMap properties) { return (SerializableObject*)Viking::deserialize(properties); };
	this->deserializers[WaterElemental::MapKeyWaterElemental] = [=](ValueMap properties) { return (SerializableObject*)WaterElemental::deserialize(properties); };
	this->deserializers[Yeti::MapKeyYeti] = [=](ValueMap properties) { return (SerializableObject*)Yeti::deserialize(properties); };
	this->deserializers[Snowman::MapKeySnowman] = [=](ValueMap properties) { return (SerializableObject*)Snowman::deserialize(properties); };
	this->deserializers[YetiBaby::MapKeyYetiBaby] = [=](ValueMap properties) { return (SerializableObject*)YetiBaby::deserialize(properties); };
	this->deserializers[Aspen::MapKeyAspen] = [=](ValueMap properties) { return (SerializableObject*)Aspen::deserialize(properties); };
	this->deserializers[Aster::MapKeyAster] = [=](ValueMap properties) { return (SerializableObject*)Aster::deserialize(properties); };
	this->deserializers[Bodom::MapKeyBodom] = [=](ValueMap properties) { return (SerializableObject*)Bodom::deserialize(properties); };
	this->deserializers[Cookie::MapKeyCookie] = [=](ValueMap properties) { return (SerializableObject*)Cookie::deserialize(properties); };
	this->deserializers[Cooper::MapKeyCooper] = [=](ValueMap properties) { return (SerializableObject*)Cooper::deserialize(properties); };
	this->deserializers[Irmik::MapKeyIrmik] = [=](ValueMap properties) { return (SerializableObject*)Irmik::deserialize(properties); };
	this->deserializers[Jingles::MapKeyJingles] = [=](ValueMap properties) { return (SerializableObject*)Jingles::deserialize(properties); };
	this->deserializers[Juniper::MapKeyJuniper] = [=](ValueMap properties) { return (SerializableObject*)Juniper::deserialize(properties); };
	this->deserializers[Kringle::MapKeyKringle] = [=](ValueMap properties) { return (SerializableObject*)Kringle::deserialize(properties); };
	this->deserializers[Nessie::MapKeyNessie] = [=](ValueMap properties) { return (SerializableObject*)Nessie::deserialize(properties); };
	this->deserializers[PrincessPepper::MapKeyPrincessPepper] = [=](ValueMap properties) { return (SerializableObject*)PrincessPepper::deserialize(properties); };
	this->deserializers[Thatcher::MapKeyThatcher] = [=](ValueMap properties) { return (SerializableObject*)Thatcher::deserialize(properties); };
	this->deserializers[Theldar::MapKeyTheldar] = [=](ValueMap properties) { return (SerializableObject*)Theldar::deserialize(properties); };
	this->deserializers[Tinsel::MapKeyTinsel] = [=](ValueMap properties) { return (SerializableObject*)Tinsel::deserialize(properties); };
	this->deserializers[Agnes::MapKeyAgnes] = [=](ValueMap properties) { return (SerializableObject*)Agnes::deserialize(properties); };
	this->deserializers[Jack::MapKeyJack] = [=](ValueMap properties) { return (SerializableObject*)Jack::deserialize(properties); };
	this->deserializers[Reaper::MapKeyReaper] = [=](ValueMap properties) { return (SerializableObject*)Reaper::deserialize(properties); };
	this->deserializers[Scarecrow::MapKeyScarecrow] = [=](ValueMap properties) { return (SerializableObject*)Scarecrow::deserialize(properties); };
	this->deserializers[SkeletalPirate::MapKeySkeletalPirate] = [=](ValueMap properties) { return (SerializableObject*)SkeletalPirate::deserialize(properties); };
	this->deserializers[Thug::MapKeyThug] = [=](ValueMap properties) { return (SerializableObject*)Thug::deserialize(properties); };
	this->deserializers[VampireLord::MapKeyVampireLord] = [=](ValueMap properties) { return (SerializableObject*)VampireLord::deserialize(properties); };
	this->deserializers[Vampiress::MapKeyVampiress] = [=](ValueMap properties) { return (SerializableObject*)Vampiress::deserialize(properties); };
	this->deserializers[Werewolf::MapKeyWerewolf] = [=](ValueMap properties) { return (SerializableObject*)Werewolf::deserialize(properties); };
	this->deserializers[Wraith::MapKeyWraith] = [=](ValueMap properties) { return (SerializableObject*)Wraith::deserialize(properties); };
	this->deserializers[Zombie::MapKeyZombie] = [=](ValueMap properties) { return (SerializableObject*)Zombie::deserialize(properties); };
	this->deserializers[ZombieElric::MapKeyZombieElric] = [=](ValueMap properties) { return (SerializableObject*)ZombieElric::deserialize(properties); };
	this->deserializers[Knight::MapKeyKnight] = [=](ValueMap properties) { return (SerializableObject*)Knight::deserialize(properties); };
	this->deserializers[Princess::MapKeyPrincess] = [=](ValueMap properties) { return (SerializableObject*)Princess::deserialize(properties); };
	this->deserializers[Elric::MapKeyElric] = [=](ValueMap properties) { return (SerializableObject*)Elric::deserialize(properties); };
	this->deserializers[Garin::MapKeyGarin] = [=](ValueMap properties) { return (SerializableObject*)Garin::deserialize(properties); };
	this->deserializers[Gaunt::MapKeyGaunt] = [=](ValueMap properties) { return (SerializableObject*)Gaunt::deserialize(properties); };
	this->deserializers[KingRedsong::MapKeyKingRedsong] = [=](ValueMap properties) { return (SerializableObject*)KingRedsong::deserialize(properties); };
	this->deserializers[KingRedsongSlime::MapKeyKingRedsongSlime] = [=](ValueMap properties) { return (SerializableObject*)KingRedsongSlime::deserialize(properties); };
	this->deserializers[Leopold::MapKeyLeopold] = [=](ValueMap properties) { return (SerializableObject*)Leopold::deserialize(properties); };
	this->deserializers[Leroy::MapKeyLeroy] = [=](ValueMap properties) { return (SerializableObject*)Leroy::deserialize(properties); };
	this->deserializers[Mabel::MapKeyMabel] = [=](ValueMap properties) { return (SerializableObject*)Mabel::deserialize(properties); };
	this->deserializers[Merlin::MapKeyMerlin] = [=](ValueMap properties) { return (SerializableObject*)Merlin::deserialize(properties); };
	this->deserializers[PrincessOpal::MapKeyPrincessOpal] = [=](ValueMap properties) { return (SerializableObject*)PrincessOpal::deserialize(properties); };
	this->deserializers[Raven::MapKeyRaven] = [=](ValueMap properties) { return (SerializableObject*)Raven::deserialize(properties); };
	this->deserializers[Rogas::MapKeyRogas] = [=](ValueMap properties) { return (SerializableObject*)Rogas::deserialize(properties); };
	this->deserializers[Thurstan::MapKeyThurstan] = [=](ValueMap properties) { return (SerializableObject*)Thurstan::deserialize(properties); };
	this->deserializers[Tyracius::MapKeyTyracius] = [=](ValueMap properties) { return (SerializableObject*)Tyracius::deserialize(properties); };
	this->deserializers[Asmodeus::MapKeyAsmodeus] = [=](ValueMap properties) { return (SerializableObject*)Asmodeus::deserialize(properties); };
	this->deserializers[DemonDragon::MapKeyDemonDragon] = [=](ValueMap properties) { return (SerializableObject*)DemonDragon::deserialize(properties); };
	this->deserializers[DemonGhost::MapKeyDemonGhost] = [=](ValueMap properties) { return (SerializableObject*)DemonGhost::deserialize(properties); };
	this->deserializers[DemonGrunt::MapKeyDemonGrunt] = [=](ValueMap properties) { return (SerializableObject*)DemonGrunt::deserialize(properties); };
	this->deserializers[DemonRogue::MapKeyDemonRogue] = [=](ValueMap properties) { return (SerializableObject*)DemonRogue::deserialize(properties); };
	this->deserializers[DemonShaman::MapKeyDemonShaman] = [=](ValueMap properties) { return (SerializableObject*)DemonShaman::deserialize(properties); };
	this->deserializers[DemonSwordsman::MapKeyDemonSwordsman] = [=](ValueMap properties) { return (SerializableObject*)DemonSwordsman::deserialize(properties); };
	this->deserializers[DemonWarrior::MapKeyDemonWarrior] = [=](ValueMap properties) { return (SerializableObject*)DemonWarrior::deserialize(properties); };
	this->deserializers[FireElemental::MapKeyFireElemental] = [=](ValueMap properties) { return (SerializableObject*)FireElemental::deserialize(properties); };
	this->deserializers[FireTiger::MapKeyFireTiger] = [=](ValueMap properties) { return (SerializableObject*)FireTiger::deserialize(properties); };
	this->deserializers[Krampus::MapKeyKrampus] = [=](ValueMap properties) { return (SerializableObject*)Krampus::deserialize(properties); };
	this->deserializers[LavaGolem::MapKeyLavaGolem] = [=](ValueMap properties) { return (SerializableObject*)LavaGolem::deserialize(properties); };
	this->deserializers[Apple::MapKeyApple] = [=](ValueMap properties) { return (SerializableObject*)Apple::deserialize(properties); };
	this->deserializers[CritterDemon::MapKeyCritterDemon] = [=](ValueMap properties) { return (SerializableObject*)CritterDemon::deserialize(properties); };
	this->deserializers[FlyBot::MapKeyFlyBot] = [=](ValueMap properties) { return (SerializableObject*)FlyBot::deserialize(properties); };
	this->deserializers[Ash::MapKeyAsh] = [=](ValueMap properties) { return (SerializableObject*)Ash::deserialize(properties); };
	this->deserializers[Brine::MapKeyBrine] = [=](ValueMap properties) { return (SerializableObject*)Brine::deserialize(properties); };
	this->deserializers[Celeste::MapKeyCeleste] = [=](ValueMap properties) { return (SerializableObject*)Celeste::deserialize(properties); };
	this->deserializers[Cindra::MapKeyCindra] = [=](ValueMap properties) { return (SerializableObject*)Cindra::deserialize(properties); };
	this->deserializers[Drak::MapKeyDrak] = [=](ValueMap properties) { return (SerializableObject*)Drak::deserialize(properties); };
	this->deserializers[Igneus::MapKeyIgneus] = [=](ValueMap properties) { return (SerializableObject*)Igneus::deserialize(properties); };
	this->deserializers[Lucifer::MapKeyLucifer] = [=](ValueMap properties) { return (SerializableObject*)Lucifer::deserialize(properties); };
	this->deserializers[Magnus::MapKeyMagnus] = [=](ValueMap properties) { return (SerializableObject*)Magnus::deserialize(properties); };
	this->deserializers[Pan::MapKeyPan] = [=](ValueMap properties) { return (SerializableObject*)Pan::deserialize(properties); };
	this->deserializers[PrincessMittens::MapKeyPrincessMittens] = [=](ValueMap properties) { return (SerializableObject*)PrincessMittens::deserialize(properties); };
	this->deserializers[Ragnis::MapKeyRagnis] = [=](ValueMap properties) { return (SerializableObject*)Ragnis::deserialize(properties); };
	this->deserializers[Rupert::MapKeyRupert] = [=](ValueMap properties) { return (SerializableObject*)Rupert::deserialize(properties); };
	this->deserializers[Rusty::MapKeyRusty] = [=](ValueMap properties) { return (SerializableObject*)Rusty::deserialize(properties); };
	this->deserializers[Scaldor::MapKeyScaldor] = [=](ValueMap properties) { return (SerializableObject*)Scaldor::deserialize(properties); };
	this->deserializers[Centaur::MapKeyCentaur] = [=](ValueMap properties) { return (SerializableObject*)Centaur::deserialize(properties); };
	this->deserializers[Cyclops::MapKeyCyclops] = [=](ValueMap properties) { return (SerializableObject*)Cyclops::deserialize(properties); };
	this->deserializers[GoblinGruntBoar::MapKeyGoblinGruntBoar] = [=](ValueMap properties) { return (SerializableObject*)GoblinGruntBoar::deserialize(properties); };
	this->deserializers[GoblinShaman::MapKeyGoblinShaman] = [=](ValueMap properties) { return (SerializableObject*)GoblinShaman::deserialize(properties); };
	this->deserializers[GoblinWarriorPig::MapKeyGoblinWarriorPig] = [=](ValueMap properties) { return (SerializableObject*)GoblinWarriorPig::deserialize(properties); };
	this->deserializers[KingGrogg::MapKeyKingGrogg] = [=](ValueMap properties) { return (SerializableObject*)KingGrogg::deserialize(properties); };
	this->deserializers[Ogre::MapKeyOgre] = [=](ValueMap properties) { return (SerializableObject*)Ogre::deserialize(properties); };
	this->deserializers[OrcBomber::MapKeyOrcBomber] = [=](ValueMap properties) { return (SerializableObject*)OrcBomber::deserialize(properties); };
	this->deserializers[OrcGrunt::MapKeyOrcGrunt] = [=](ValueMap properties) { return (SerializableObject*)OrcGrunt::deserialize(properties); };
	this->deserializers[OrcSwordsman::MapKeyOrcSwordsman] = [=](ValueMap properties) { return (SerializableObject*)OrcSwordsman::deserialize(properties); };
	this->deserializers[OrcWarrior::MapKeyOrcWarrior] = [=](ValueMap properties) { return (SerializableObject*)OrcWarrior::deserialize(properties); };
	this->deserializers[Troll::MapKeyTroll] = [=](ValueMap properties) { return (SerializableObject*)Troll::deserialize(properties); };
	this->deserializers[Goblin::MapKeyGoblin] = [=](ValueMap properties) { return (SerializableObject*)Goblin::deserialize(properties); };
	this->deserializers[Turtle::MapKeyTurtle] = [=](ValueMap properties) { return (SerializableObject*)Turtle::deserialize(properties); };
	this->deserializers[Appolo::MapKeyAppolo] = [=](ValueMap properties) { return (SerializableObject*)Appolo::deserialize(properties); };
	this->deserializers[Ara::MapKeyAra] = [=](ValueMap properties) { return (SerializableObject*)Ara::deserialize(properties); };
	this->deserializers[Bard::MapKeyBard] = [=](ValueMap properties) { return (SerializableObject*)Bard::deserialize(properties); };
	this->deserializers[Blackbeard::MapKeyBlackbeard] = [=](ValueMap properties) { return (SerializableObject*)Blackbeard::deserialize(properties); };
	this->deserializers[Chiron::MapKeyChiron] = [=](ValueMap properties) { return (SerializableObject*)Chiron::deserialize(properties); };
	this->deserializers[Elriel::MapKeyElriel] = [=](ValueMap properties) { return (SerializableObject*)Elriel::deserialize(properties); };
	this->deserializers[Gramps::MapKeyGramps] = [=](ValueMap properties) { return (SerializableObject*)Gramps::deserialize(properties); };
	this->deserializers[Liana::MapKeyLiana] = [=](ValueMap properties) { return (SerializableObject*)Liana::deserialize(properties); };
	this->deserializers[Lycan::MapKeyLycan] = [=](ValueMap properties) { return (SerializableObject*)Lycan::deserialize(properties); };
	this->deserializers[Minos::MapKeyMinos] = [=](ValueMap properties) { return (SerializableObject*)Minos::deserialize(properties); };
	this->deserializers[Polyphemus::MapKeyPolyphemus] = [=](ValueMap properties) { return (SerializableObject*)Polyphemus::deserialize(properties); };
	this->deserializers[PrincessMatu::MapKeyPrincessMatu] = [=](ValueMap properties) { return (SerializableObject*)PrincessMatu::deserialize(properties); };
	this->deserializers[Robin::MapKeyRobin] = [=](ValueMap properties) { return (SerializableObject*)Robin::deserialize(properties); };
	this->deserializers[Toben::MapKeyToben] = [=](ValueMap properties) { return (SerializableObject*)Toben::deserialize(properties); };
	this->deserializers[BoneFiend::MapKeyBoneFiend] = [=](ValueMap properties) { return (SerializableObject*)BoneFiend::deserialize(properties); };
	this->deserializers[Hunter::MapKeyHunter] = [=](ValueMap properties) { return (SerializableObject*)Hunter::deserialize(properties); };
	this->deserializers[KingZul::MapKeyKingZul] = [=](ValueMap properties) { return (SerializableObject*)KingZul::deserialize(properties); };
	this->deserializers[Mystic::MapKeyMystic] = [=](ValueMap properties) { return (SerializableObject*)Mystic::deserialize(properties); };
	this->deserializers[ReanimatedFighter::MapKeyReanimatedFighter] = [=](ValueMap properties) { return (SerializableObject*)ReanimatedFighter::deserialize(properties); };
	this->deserializers[ReanimatedPig::MapKeyReanimatedPig] = [=](ValueMap properties) { return (SerializableObject*)ReanimatedPig::deserialize(properties); };
	this->deserializers[SkeletalBaron::MapKeySkeletalBaron] = [=](ValueMap properties) { return (SerializableObject*)SkeletalBaron::deserialize(properties); };
	this->deserializers[SkeletalCleaver::MapKeySkeletalCleaver] = [=](ValueMap properties) { return (SerializableObject*)SkeletalCleaver::deserialize(properties); };
	this->deserializers[SkeletalKnight::MapKeySkeletalKnight] = [=](ValueMap properties) { return (SerializableObject*)SkeletalKnight::deserialize(properties); };
	this->deserializers[SkeletalPriestess::MapKeySkeletalPriestess] = [=](ValueMap properties) { return (SerializableObject*)SkeletalPriestess::deserialize(properties); };
	this->deserializers[Undead::MapKeyUndead] = [=](ValueMap properties) { return (SerializableObject*)Undead::deserialize(properties); };
	this->deserializers[Ghost::MapKeyGhost] = [=](ValueMap properties) { return (SerializableObject*)Ghost::deserialize(properties); };
	this->deserializers[Grim::MapKeyGrim] = [=](ValueMap properties) { return (SerializableObject*)Grim::deserialize(properties); };
	this->deserializers[Amelia::MapKeyAmelia] = [=](ValueMap properties) { return (SerializableObject*)Amelia::deserialize(properties); };
	this->deserializers[Azmus::MapKeyAzmus] = [=](ValueMap properties) { return (SerializableObject*)Azmus::deserialize(properties); };
	this->deserializers[Dudly::MapKeyDudly] = [=](ValueMap properties) { return (SerializableObject*)Dudly::deserialize(properties); };
	this->deserializers[Garrick::MapKeyGarrick] = [=](ValueMap properties) { return (SerializableObject*)Garrick::deserialize(properties); };
	this->deserializers[Johann::MapKeyJohann] = [=](ValueMap properties) { return (SerializableObject*)Johann::deserialize(properties); };
	this->deserializers[Necron::MapKeyNecron] = [=](ValueMap properties) { return (SerializableObject*)Necron::deserialize(properties); };
	this->deserializers[PrincessNebea::MapKeyPrincessNebea] = [=](ValueMap properties) { return (SerializableObject*)PrincessNebea::deserialize(properties); };
	this->deserializers[Roger::MapKeyRoger] = [=](ValueMap properties) { return (SerializableObject*)Roger::deserialize(properties); };
	this->deserializers[Thion::MapKeyThion] = [=](ValueMap properties) { return (SerializableObject*)Thion::deserialize(properties); };
	this->deserializers[Ursula::MapKeyUrsula] = [=](ValueMap properties) { return (SerializableObject*)Ursula::deserialize(properties); };
	this->deserializers[Vesuvius::MapKeyVesuvius] = [=](ValueMap properties) { return (SerializableObject*)Vesuvius::deserialize(properties); };
	this->deserializers[Viper::MapKeyViper] = [=](ValueMap properties) { return (SerializableObject*)Viper::deserialize(properties); };
	this->deserializers[Zana::MapKeyZana] = [=](ValueMap properties) { return (SerializableObject*)Zana::deserialize(properties); };
	this->deserializers[Zelina::MapKeyZelina] = [=](ValueMap properties) { return (SerializableObject*)Zelina::deserialize(properties); };
	this->deserializers[Barbarian::MapKeyBarbarian] = [=](ValueMap properties) { return (SerializableObject*)Barbarian::deserialize(properties); };
	this->deserializers[EarthElemental::MapKeyEarthElemental] = [=](ValueMap properties) { return (SerializableObject*)EarthElemental::deserialize(properties); };
	this->deserializers[EarthGolem::MapKeyEarthGolem] = [=](ValueMap properties) { return (SerializableObject*)EarthGolem::deserialize(properties); };
	this->deserializers[ForestGolem::MapKeyForestGolem] = [=](ValueMap properties) { return (SerializableObject*)ForestGolem::deserialize(properties); };
	this->deserializers[Gorilla::MapKeyGorilla] = [=](ValueMap properties) { return (SerializableObject*)Gorilla::deserialize(properties); };
	this->deserializers[LightningGolem::MapKeyLightningGolem] = [=](ValueMap properties) { return (SerializableObject*)LightningGolem::deserialize(properties); };
	this->deserializers[Rhinoman::MapKeyRhinoman] = [=](ValueMap properties) { return (SerializableObject*)Rhinoman::deserialize(properties); };
	this->deserializers[Shaman::MapKeyShaman] = [=](ValueMap properties) { return (SerializableObject*)Shaman::deserialize(properties); };
	this->deserializers[SkeletalArcher::MapKeySkeletalArcher] = [=](ValueMap properties) { return (SerializableObject*)SkeletalArcher::deserialize(properties); };
	this->deserializers[SkeletalNecromancer::MapKeySkeletalNecromancer] = [=](ValueMap properties) { return (SerializableObject*)SkeletalNecromancer::deserialize(properties); };
	this->deserializers[SkeletalWarrior::MapKeySkeletalWarrior] = [=](ValueMap properties) { return (SerializableObject*)SkeletalWarrior::deserialize(properties); };
	this->deserializers[TikiGolem::MapKeyTikiGolem] = [=](ValueMap properties) { return (SerializableObject*)TikiGolem::deserialize(properties); };
	this->deserializers[Gecko::MapKeyGecko] = [=](ValueMap properties) { return (SerializableObject*)Gecko::deserialize(properties); };
	this->deserializers[Alder::MapKeyAlder] = [=](ValueMap properties) { return (SerializableObject*)Alder::deserialize(properties); };
	this->deserializers[Bonnie::MapKeyBonnie] = [=](ValueMap properties) { return (SerializableObject*)Bonnie::deserialize(properties); };
	this->deserializers[Brock::MapKeyBrock] = [=](ValueMap properties) { return (SerializableObject*)Brock::deserialize(properties); };
	this->deserializers[Burch::MapKeyBurch] = [=](ValueMap properties) { return (SerializableObject*)Burch::deserialize(properties); };
	this->deserializers[Cypress::MapKeyCypress] = [=](ValueMap properties) { return (SerializableObject*)Cypress::deserialize(properties); };
	this->deserializers[Finch::MapKeyFinch] = [=](ValueMap properties) { return (SerializableObject*)Finch::deserialize(properties); };
	this->deserializers[Fraya::MapKeyFraya] = [=](ValueMap properties) { return (SerializableObject*)Fraya::deserialize(properties); };
	this->deserializers[Jasper::MapKeyJasper] = [=](ValueMap properties) { return (SerializableObject*)Jasper::deserialize(properties); };
	this->deserializers[Mildred::MapKeyMildred] = [=](ValueMap properties) { return (SerializableObject*)Mildred::deserialize(properties); };
	this->deserializers[Olive::MapKeyOlive] = [=](ValueMap properties) { return (SerializableObject*)Olive::deserialize(properties); };
	this->deserializers[PrincessDawn::MapKeyPrincessDawn] = [=](ValueMap properties) { return (SerializableObject*)PrincessDawn::deserialize(properties); };
	this->deserializers[Raka::MapKeyRaka] = [=](ValueMap properties) { return (SerializableObject*)Raka::deserialize(properties); };
	this->deserializers[Sarude::MapKeySarude] = [=](ValueMap properties) { return (SerializableObject*)Sarude::deserialize(properties); };
	this->deserializers[Shen::MapKeyShen] = [=](ValueMap properties) { return (SerializableObject*)Shen::deserialize(properties); };
	this->deserializers[AnubisPup::MapKeyAnubisPup] = [=](ValueMap properties) { return (SerializableObject*)AnubisPup::deserialize(properties); };
	this->deserializers[AnubisWarrior::MapKeyAnubisWarrior] = [=](ValueMap properties) { return (SerializableObject*)AnubisWarrior::deserialize(properties); };
	this->deserializers[LionMan::MapKeyLionMan] = [=](ValueMap properties) { return (SerializableObject*)LionMan::deserialize(properties); };
	this->deserializers[Lioness::MapKeyLioness] = [=](ValueMap properties) { return (SerializableObject*)Lioness::deserialize(properties); };
	this->deserializers[Medusa::MapKeyMedusa] = [=](ValueMap properties) { return (SerializableObject*)Medusa::deserialize(properties); };
	this->deserializers[Mermaid::MapKeyMermaid] = [=](ValueMap properties) { return (SerializableObject*)Mermaid::deserialize(properties); };
	this->deserializers[Minotaur::MapKeyMinotaur] = [=](ValueMap properties) { return (SerializableObject*)Minotaur::deserialize(properties); };
	this->deserializers[MummyPriest::MapKeyMummyPriest] = [=](ValueMap properties) { return (SerializableObject*)MummyPriest::deserialize(properties); };
	this->deserializers[MummyWarrior::MapKeyMummyWarrior] = [=](ValueMap properties) { return (SerializableObject*)MummyWarrior::deserialize(properties); };
	this->deserializers[Osiris::MapKeyOsiris] = [=](ValueMap properties) { return (SerializableObject*)Osiris::deserialize(properties); };
	this->deserializers[TigerMan::MapKeyTigerMan] = [=](ValueMap properties) { return (SerializableObject*)TigerMan::deserialize(properties); };
	this->deserializers[Tigress::MapKeyTigress] = [=](ValueMap properties) { return (SerializableObject*)Tigress::deserialize(properties); };
	this->deserializers[Mummy::MapKeyMummy] = [=](ValueMap properties) { return (SerializableObject*)Mummy::deserialize(properties); };
	this->deserializers[Ajax::MapKeyAjax] = [=](ValueMap properties) { return (SerializableObject*)Ajax::deserialize(properties); };
	this->deserializers[Angel::MapKeyAngel] = [=](ValueMap properties) { return (SerializableObject*)Angel::deserialize(properties); };
	this->deserializers[Aphrodite::MapKeyAphrodite] = [=](ValueMap properties) { return (SerializableObject*)Aphrodite::deserialize(properties); };
	this->deserializers[Ares::MapKeyAres] = [=](ValueMap properties) { return (SerializableObject*)Ares::deserialize(properties); };
	this->deserializers[Athena::MapKeyAthena] = [=](ValueMap properties) { return (SerializableObject*)Athena::deserialize(properties); };
	this->deserializers[Cleopatra::MapKeyCleopatra] = [=](ValueMap properties) { return (SerializableObject*)Cleopatra::deserialize(properties); };
	this->deserializers[Geryon::MapKeyGeryon] = [=](ValueMap properties) { return (SerializableObject*)Geryon::deserialize(properties); };
	this->deserializers[Griffin::MapKeyGriffin] = [=](ValueMap properties) { return (SerializableObject*)Griffin::deserialize(properties); };
	this->deserializers[Hades::MapKeyHades] = [=](ValueMap properties) { return (SerializableObject*)Hades::deserialize(properties); };
	this->deserializers[Hera::MapKeyHera] = [=](ValueMap properties) { return (SerializableObject*)Hera::deserialize(properties); };
	this->deserializers[Horus::MapKeyHorus] = [=](ValueMap properties) { return (SerializableObject*)Horus::deserialize(properties); };
	this->deserializers[Poseidon::MapKeyPoseidon] = [=](ValueMap properties) { return (SerializableObject*)Poseidon::deserialize(properties); };
	this->deserializers[Thor::MapKeyThor] = [=](ValueMap properties) { return (SerializableObject*)Thor::deserialize(properties); };
	this->deserializers[Zeus::MapKeyZeus] = [=](ValueMap properties) { return (SerializableObject*)Zeus::deserialize(properties); };
	this->deserializers[Abomination::MapKeyAbomination] = [=](ValueMap properties) { return (SerializableObject*)Abomination::deserialize(properties); };
	this->deserializers[Assassin::MapKeyAssassin] = [=](ValueMap properties) { return (SerializableObject*)Assassin::deserialize(properties); };
	this->deserializers[BoneKnight::MapKeyBoneKnight] = [=](ValueMap properties) { return (SerializableObject*)BoneKnight::deserialize(properties); };
	this->deserializers[DarkTiger::MapKeyDarkTiger] = [=](ValueMap properties) { return (SerializableObject*)DarkTiger::deserialize(properties); };
	this->deserializers[EvilEye::MapKeyEvilEye] = [=](ValueMap properties) { return (SerializableObject*)EvilEye::deserialize(properties); };
	this->deserializers[Exterminator::MapKeyExterminator] = [=](ValueMap properties) { return (SerializableObject*)Exterminator::deserialize(properties); };
	this->deserializers[Gargoyle::MapKeyGargoyle] = [=](ValueMap properties) { return (SerializableObject*)Gargoyle::deserialize(properties); };
	this->deserializers[Shade::MapKeyShade] = [=](ValueMap properties) { return (SerializableObject*)Shade::deserialize(properties); };
	this->deserializers[VoidArcher::MapKeyVoidArcher] = [=](ValueMap properties) { return (SerializableObject*)VoidArcher::deserialize(properties); };
	this->deserializers[VoidDemon::MapKeyVoidDemon] = [=](ValueMap properties) { return (SerializableObject*)VoidDemon::deserialize(properties); };
	this->deserializers[Warlock::MapKeyWarlock] = [=](ValueMap properties) { return (SerializableObject*)Warlock::deserialize(properties); };
	this->deserializers[Professor::MapKeyProfessor] = [=](ValueMap properties) { return (SerializableObject*)Professor::deserialize(properties); };
	this->deserializers[Robot::MapKeyRobot] = [=](ValueMap properties) { return (SerializableObject*)Robot::deserialize(properties); };
	this->deserializers[Atreus::MapKeyAtreus] = [=](ValueMap properties) { return (SerializableObject*)Atreus::deserialize(properties); };
	this->deserializers[Bancroft::MapKeyBancroft] = [=](ValueMap properties) { return (SerializableObject*)Bancroft::deserialize(properties); };
	this->deserializers[Godiva::MapKeyGodiva] = [=](ValueMap properties) { return (SerializableObject*)Godiva::deserialize(properties); };
	this->deserializers[Illia::MapKeyIllia] = [=](ValueMap properties) { return (SerializableObject*)Illia::deserialize(properties); };
	this->deserializers[Leon::MapKeyLeon] = [=](ValueMap properties) { return (SerializableObject*)Leon::deserialize(properties); };
	this->deserializers[Mara::MapKeyMara] = [=](ValueMap properties) { return (SerializableObject*)Mara::deserialize(properties); };
	this->deserializers[Marcel::MapKeyMarcel] = [=](ValueMap properties) { return (SerializableObject*)Marcel::deserialize(properties); };
	this->deserializers[Piper::MapKeyPiper] = [=](ValueMap properties) { return (SerializableObject*)Piper::deserialize(properties); };
	this->deserializers[QueenElise::MapKeyQueenElise] = [=](ValueMap properties) { return (SerializableObject*)QueenElise::deserialize(properties); };
	this->deserializers[Radon::MapKeyRadon] = [=](ValueMap properties) { return (SerializableObject*)Radon::deserialize(properties); };
	this->deserializers[Ralston::MapKeyRalston] = [=](ValueMap properties) { return (SerializableObject*)Ralston::deserialize(properties); };
	this->deserializers[Xenon::MapKeyXenon] = [=](ValueMap properties) { return (SerializableObject*)Xenon::deserialize(properties); };
	this->deserializers[Ysara::MapKeyYsara] = [=](ValueMap properties) { return (SerializableObject*)Ysara::deserialize(properties); };

	////O////O////O////O////O////O////O/
	// END: THIS CODE IS GENERATED    //
	////////////////////////////////////
}

PlatformerEntityDeserializer::~PlatformerEntityDeserializer()
{
}

void PlatformerEntityDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::ObjectDeserializationRequestArgs* args = static_cast<DeserializationEvents::ObjectDeserializationRequestArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PlatformerEntityDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerEntityDeserializer::KeyTypeEntity)
	{
		std::string name = args->properties.at(SerializableObject::MapKeyName).asString();

		if (this->deserializers.find(name) != this->deserializers.end())
		{
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(this->deserializers[name](args->properties)));
		}
		else
		{
			CCLOG("Unknown entity encountered: %s", name.c_str());
		}
	}
}
