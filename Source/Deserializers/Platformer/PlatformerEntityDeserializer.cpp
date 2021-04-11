#include "PlatformerEntityDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Quests/QuestTask.h"
#include "Entities/Platformer/PlatformerEntities.h"

using namespace cocos2d;

const std::string PlatformerEntityDeserializer::MapKeyTypeEntity = "entity";

PlatformerEntityDeserializer* PlatformerEntityDeserializer::create()
{
	PlatformerEntityDeserializer* instance = new PlatformerEntityDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerEntityDeserializer::PlatformerEntityDeserializer() : super(PlatformerEntityDeserializer::MapKeyTypeEntity, { (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	// Player
	this->deserializers[Squally::MapKey] = [=](ValueMap properties) { return (GameObject*)Squally::deserialize(properties); };

	// Critters
	this->deserializers[Horse::MapKey] = [=](ValueMap properties) { return (GameObject*)Horse::deserialize(properties); };
	this->deserializers[Seagull::MapKey] = [=](ValueMap properties) { return (GameObject*)Seagull::deserialize(properties); };
	this->deserializers[TrainingDummy::MapKey] = [=](ValueMap properties) { return (GameObject*)TrainingDummy::deserialize(properties); };
	
	// Npcs, helpers, and enemies
	this->deserializers[Cryogen::MapKey] = [=](ValueMap properties) { return (GameObject*)Cryogen::deserialize(properties); };
	this->deserializers[FrostFiend::MapKey] = [=](ValueMap properties) { return (GameObject*)FrostFiend::deserialize(properties); };
	this->deserializers[GoblinElf::MapKey] = [=](ValueMap properties) { return (GameObject*)GoblinElf::deserialize(properties); };
	this->deserializers[IceGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)IceGolem::deserialize(properties); };
	this->deserializers[PenguinGrunt::MapKey] = [=](ValueMap properties) { return (GameObject*)PenguinGrunt::deserialize(properties); };
	this->deserializers[PenguinWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)PenguinWarrior::deserialize(properties); };
	this->deserializers[Santa::MapKey] = [=](ValueMap properties) { return (GameObject*)Santa::deserialize(properties); };
	this->deserializers[SnowFiend::MapKey] = [=](ValueMap properties) { return (GameObject*)SnowFiend::deserialize(properties); };
	this->deserializers[ToySoldierGoblin::MapKey] = [=](ValueMap properties) { return (GameObject*)ToySoldierGoblin::deserialize(properties); };
	this->deserializers[Viking::MapKey] = [=](ValueMap properties) { return (GameObject*)Viking::deserialize(properties); };
	this->deserializers[WaterElemental::MapKey] = [=](ValueMap properties) { return (GameObject*)WaterElemental::deserialize(properties); };
	this->deserializers[Yeti::MapKey] = [=](ValueMap properties) { return (GameObject*)Yeti::deserialize(properties); };
	this->deserializers[Snowman::MapKey] = [=](ValueMap properties) { return (GameObject*)Snowman::deserialize(properties); };
	this->deserializers[YetiBaby::MapKey] = [=](ValueMap properties) { return (GameObject*)YetiBaby::deserialize(properties); };
	this->deserializers[Aspen::MapKey] = [=](ValueMap properties) { return (GameObject*)Aspen::deserialize(properties); };
	this->deserializers[Aster::MapKey] = [=](ValueMap properties) { return (GameObject*)Aster::deserialize(properties); };
	this->deserializers[Bodom::MapKey] = [=](ValueMap properties) { return (GameObject*)Bodom::deserialize(properties); };
	this->deserializers[Cookie::MapKey] = [=](ValueMap properties) { return (GameObject*)Cookie::deserialize(properties); };
	this->deserializers[Cooper::MapKey] = [=](ValueMap properties) { return (GameObject*)Cooper::deserialize(properties); };
	this->deserializers[Irmik::MapKey] = [=](ValueMap properties) { return (GameObject*)Irmik::deserialize(properties); };
	this->deserializers[Jingles::MapKey] = [=](ValueMap properties) { return (GameObject*)Jingles::deserialize(properties); };
	this->deserializers[Juniper::MapKey] = [=](ValueMap properties) { return (GameObject*)Juniper::deserialize(properties); };
	this->deserializers[Kringle::MapKey] = [=](ValueMap properties) { return (GameObject*)Kringle::deserialize(properties); };
	this->deserializers[Luna::MapKey] = [=](ValueMap properties) { return (GameObject*)Luna::deserialize(properties); };
	this->deserializers[Nessie::MapKey] = [=](ValueMap properties) { return (GameObject*)Nessie::deserialize(properties); };
	this->deserializers[PrincessPepper::MapKey] = [=](ValueMap properties) { return (GameObject*)PrincessPepper::deserialize(properties); };
	this->deserializers[Thatcher::MapKey] = [=](ValueMap properties) { return (GameObject*)Thatcher::deserialize(properties); };
	this->deserializers[Theldar::MapKey] = [=](ValueMap properties) { return (GameObject*)Theldar::deserialize(properties); };
	this->deserializers[Tinsel::MapKey] = [=](ValueMap properties) { return (GameObject*)Tinsel::deserialize(properties); };
	this->deserializers[Agnes::MapKey] = [=](ValueMap properties) { return (GameObject*)Agnes::deserialize(properties); };
	this->deserializers[Jack::MapKey] = [=](ValueMap properties) { return (GameObject*)Jack::deserialize(properties); };
	this->deserializers[Reaper::MapKey] = [=](ValueMap properties) { return (GameObject*)Reaper::deserialize(properties); };
	this->deserializers[Scarecrow::MapKey] = [=](ValueMap properties) { return (GameObject*)Scarecrow::deserialize(properties); };
	this->deserializers[SkeletalPirate::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalPirate::deserialize(properties); };
	this->deserializers[Thug::MapKey] = [=](ValueMap properties) { return (GameObject*)Thug::deserialize(properties); };
	this->deserializers[VampireLord::MapKey] = [=](ValueMap properties) { return (GameObject*)VampireLord::deserialize(properties); };
	this->deserializers[Vampiress::MapKey] = [=](ValueMap properties) { return (GameObject*)Vampiress::deserialize(properties); };
	this->deserializers[Werewolf::MapKey] = [=](ValueMap properties) { return (GameObject*)Werewolf::deserialize(properties); };
	this->deserializers[Wraith::MapKey] = [=](ValueMap properties) { return (GameObject*)Wraith::deserialize(properties); };
	this->deserializers[Zombie::MapKey] = [=](ValueMap properties) { return (GameObject*)Zombie::deserialize(properties); };
	this->deserializers[ZombieElric::MapKey] = [=](ValueMap properties) { return (GameObject*)ZombieElric::deserialize(properties); };
	this->deserializers[Knight::MapKey] = [=](ValueMap properties) { return (GameObject*)Knight::deserialize(properties); };
	this->deserializers[Elric::MapKey] = [=](ValueMap properties) { return (GameObject*)Elric::deserialize(properties); };
	this->deserializers[Garin::MapKey] = [=](ValueMap properties) { return (GameObject*)Garin::deserialize(properties); };
	this->deserializers[Gaunt::MapKey] = [=](ValueMap properties) { return (GameObject*)Gaunt::deserialize(properties); };
	this->deserializers[KingRedsong::MapKey] = [=](ValueMap properties) { return (GameObject*)KingRedsong::deserialize(properties); };
	this->deserializers[KingRedsongSlime::MapKey] = [=](ValueMap properties) { return (GameObject*)KingRedsongSlime::deserialize(properties); };
	this->deserializers[Leopold::MapKey] = [=](ValueMap properties) { return (GameObject*)Leopold::deserialize(properties); };
	this->deserializers[Leroy::MapKey] = [=](ValueMap properties) { return (GameObject*)Leroy::deserialize(properties); };
	this->deserializers[Mabel::MapKey] = [=](ValueMap properties) { return (GameObject*)Mabel::deserialize(properties); };
	this->deserializers[Merlin::MapKey] = [=](ValueMap properties) { return (GameObject*)Merlin::deserialize(properties); };
	this->deserializers[PrincessOpal::MapKey] = [=](ValueMap properties) { return (GameObject*)PrincessOpal::deserialize(properties); };
	this->deserializers[Raven::MapKey] = [=](ValueMap properties) { return (GameObject*)Raven::deserialize(properties); };
	this->deserializers[Rogas::MapKey] = [=](ValueMap properties) { return (GameObject*)Rogas::deserialize(properties); };
	this->deserializers[Thurstan::MapKey] = [=](ValueMap properties) { return (GameObject*)Thurstan::deserialize(properties); };
	this->deserializers[Tyracius::MapKey] = [=](ValueMap properties) { return (GameObject*)Tyracius::deserialize(properties); };
	this->deserializers[Asmodeus::MapKey] = [=](ValueMap properties) { return (GameObject*)Asmodeus::deserialize(properties); };
	this->deserializers[DemonDragon::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonDragon::deserialize(properties); };
	this->deserializers[DemonGhost::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonGhost::deserialize(properties); };
	this->deserializers[DemonGrunt::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonGrunt::deserialize(properties); };
	this->deserializers[DemonRogue::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonRogue::deserialize(properties); };
	this->deserializers[DemonShaman::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonShaman::deserialize(properties); };
	this->deserializers[DemonSwordsman::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonSwordsman::deserialize(properties); };
	this->deserializers[DemonWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)DemonWarrior::deserialize(properties); };
	this->deserializers[FireElemental::MapKey] = [=](ValueMap properties) { return (GameObject*)FireElemental::deserialize(properties); };
	this->deserializers[FireTiger::MapKey] = [=](ValueMap properties) { return (GameObject*)FireTiger::deserialize(properties); };
	this->deserializers[Krampus::MapKey] = [=](ValueMap properties) { return (GameObject*)Krampus::deserialize(properties); };
	this->deserializers[LavaGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)LavaGolem::deserialize(properties); };
	this->deserializers[CritterDemon::MapKey] = [=](ValueMap properties) { return (GameObject*)CritterDemon::deserialize(properties); };
	this->deserializers[Scrappy::MapKey] = [=](ValueMap properties) { return (GameObject*)Scrappy::deserialize(properties); };
	this->deserializers[Ash::MapKey] = [=](ValueMap properties) { return (GameObject*)Ash::deserialize(properties); };
	this->deserializers[Brine::MapKey] = [=](ValueMap properties) { return (GameObject*)Brine::deserialize(properties); };
	this->deserializers[Celeste::MapKey] = [=](ValueMap properties) { return (GameObject*)Celeste::deserialize(properties); };
	this->deserializers[Cindra::MapKey] = [=](ValueMap properties) { return (GameObject*)Cindra::deserialize(properties); };
	this->deserializers[Drak::MapKey] = [=](ValueMap properties) { return (GameObject*)Drak::deserialize(properties); };
	this->deserializers[Igneus::MapKey] = [=](ValueMap properties) { return (GameObject*)Igneus::deserialize(properties); };
	this->deserializers[Lucifer::MapKey] = [=](ValueMap properties) { return (GameObject*)Lucifer::deserialize(properties); };
	this->deserializers[Magnus::MapKey] = [=](ValueMap properties) { return (GameObject*)Magnus::deserialize(properties); };
	this->deserializers[Pan::MapKey] = [=](ValueMap properties) { return (GameObject*)Pan::deserialize(properties); };
	this->deserializers[PrincessMittens::MapKey] = [=](ValueMap properties) { return (GameObject*)PrincessMittens::deserialize(properties); };
	this->deserializers[Ragnis::MapKey] = [=](ValueMap properties) { return (GameObject*)Ragnis::deserialize(properties); };
	this->deserializers[Rupert::MapKey] = [=](ValueMap properties) { return (GameObject*)Rupert::deserialize(properties); };
	this->deserializers[Rusty::MapKey] = [=](ValueMap properties) { return (GameObject*)Rusty::deserialize(properties); };
	this->deserializers[Scaldor::MapKey] = [=](ValueMap properties) { return (GameObject*)Scaldor::deserialize(properties); };
	this->deserializers[Centaur::MapKey] = [=](ValueMap properties) { return (GameObject*)Centaur::deserialize(properties); };
	this->deserializers[Cyclops::MapKey] = [=](ValueMap properties) { return (GameObject*)Cyclops::deserialize(properties); };
	this->deserializers[GoblinGruntBoar::MapKey] = [=](ValueMap properties) { return (GameObject*)GoblinGruntBoar::deserialize(properties); };
	this->deserializers[GoblinShaman::MapKey] = [=](ValueMap properties) { return (GameObject*)GoblinShaman::deserialize(properties); };
	this->deserializers[GoblinWarriorPig::MapKey] = [=](ValueMap properties) { return (GameObject*)GoblinWarriorPig::deserialize(properties); };
	this->deserializers[Gorgon::MapKey] = [=](ValueMap properties) { return (GameObject*)Gorgon::deserialize(properties); };
	this->deserializers[KingGrogg::MapKey] = [=](ValueMap properties) { return (GameObject*)KingGrogg::deserialize(properties); };
	this->deserializers[Ogre::MapKey] = [=](ValueMap properties) { return (GameObject*)Ogre::deserialize(properties); };
	this->deserializers[OrcBomber::MapKey] = [=](ValueMap properties) { return (GameObject*)OrcBomber::deserialize(properties); };
	this->deserializers[OrcGrunt::MapKey] = [=](ValueMap properties) { return (GameObject*)OrcGrunt::deserialize(properties); };
	this->deserializers[OrcSwordsman::MapKey] = [=](ValueMap properties) { return (GameObject*)OrcSwordsman::deserialize(properties); };
	this->deserializers[OrcWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)OrcWarrior::deserialize(properties); };
	this->deserializers[Orthrus::MapKey] = [=](ValueMap properties) { return (GameObject*)Orthrus::deserialize(properties); };
	this->deserializers[Troll::MapKey] = [=](ValueMap properties) { return (GameObject*)Troll::deserialize(properties); };
	this->deserializers[Guano::MapKey] = [=](ValueMap properties) { return (GameObject*)Guano::deserialize(properties); };
	this->deserializers[GuanoPetrified::MapKey] = [=](ValueMap properties) { return (GameObject*)GuanoPetrified::deserialize(properties); };
	this->deserializers[Appolo::MapKey] = [=](ValueMap properties) { return (GameObject*)Appolo::deserialize(properties); };
	this->deserializers[Ara::MapKey] = [=](ValueMap properties) { return (GameObject*)Ara::deserialize(properties); };
	this->deserializers[Bard::MapKey] = [=](ValueMap properties) { return (GameObject*)Bard::deserialize(properties); };
	this->deserializers[Blackbeard::MapKey] = [=](ValueMap properties) { return (GameObject*)Blackbeard::deserialize(properties); };
	this->deserializers[Chiron::MapKey] = [=](ValueMap properties) { return (GameObject*)Chiron::deserialize(properties); };
	this->deserializers[Elriel::MapKey] = [=](ValueMap properties) { return (GameObject*)Elriel::deserialize(properties); };
	this->deserializers[Gramps::MapKey] = [=](ValueMap properties) { return (GameObject*)Gramps::deserialize(properties); };
	this->deserializers[QueenLiana::MapKey] = [=](ValueMap properties) { return (GameObject*)QueenLiana::deserialize(properties); };
	this->deserializers[Lycan::MapKey] = [=](ValueMap properties) { return (GameObject*)Lycan::deserialize(properties); };
	this->deserializers[Minos::MapKey] = [=](ValueMap properties) { return (GameObject*)Minos::deserialize(properties); };
	this->deserializers[Polyphemus::MapKey] = [=](ValueMap properties) { return (GameObject*)Polyphemus::deserialize(properties); };
	this->deserializers[Matu::MapKey] = [=](ValueMap properties) { return (GameObject*)Matu::deserialize(properties); };
	this->deserializers[Robin::MapKey] = [=](ValueMap properties) { return (GameObject*)Robin::deserialize(properties); };
	this->deserializers[Toben::MapKey] = [=](ValueMap properties) { return (GameObject*)Toben::deserialize(properties); };
	this->deserializers[BoneFiend::MapKey] = [=](ValueMap properties) { return (GameObject*)BoneFiend::deserialize(properties); };
	this->deserializers[Hunter::MapKey] = [=](ValueMap properties) { return (GameObject*)Hunter::deserialize(properties); };
	this->deserializers[KingZul::MapKey] = [=](ValueMap properties) { return (GameObject*)KingZul::deserialize(properties); };
	this->deserializers[Lazarus::MapKey] = [=](ValueMap properties) { return (GameObject*)Lazarus::deserialize(properties); };
	this->deserializers[Mystic::MapKey] = [=](ValueMap properties) { return (GameObject*)Mystic::deserialize(properties); };
	this->deserializers[ReanimatedFighter::MapKey] = [=](ValueMap properties) { return (GameObject*)ReanimatedFighter::deserialize(properties); };
	this->deserializers[ReanimatedPig::MapKey] = [=](ValueMap properties) { return (GameObject*)ReanimatedPig::deserialize(properties); };
	this->deserializers[SkeletalBaron::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalBaron::deserialize(properties); };
	this->deserializers[SkeletalCleaver::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalCleaver::deserialize(properties); };
	this->deserializers[SkeletalKnight::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalKnight::deserialize(properties); };
	this->deserializers[SkeletalPriestess::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalPriestess::deserialize(properties); };
	this->deserializers[Undead::MapKey] = [=](ValueMap properties) { return (GameObject*)Undead::deserialize(properties); };
	this->deserializers[Ghost::MapKey] = [=](ValueMap properties) { return (GameObject*)Ghost::deserialize(properties); };
	this->deserializers[Grim::MapKey] = [=](ValueMap properties) { return (GameObject*)Grim::deserialize(properties); };
	this->deserializers[Amelia::MapKey] = [=](ValueMap properties) { return (GameObject*)Amelia::deserialize(properties); };
	this->deserializers[Azmus::MapKey] = [=](ValueMap properties) { return (GameObject*)Azmus::deserialize(properties); };
	this->deserializers[Dudly::MapKey] = [=](ValueMap properties) { return (GameObject*)Dudly::deserialize(properties); };
	this->deserializers[Garrick::MapKey] = [=](ValueMap properties) { return (GameObject*)Garrick::deserialize(properties); };
	this->deserializers[Johann::MapKey] = [=](ValueMap properties) { return (GameObject*)Johann::deserialize(properties); };
	this->deserializers[Necron::MapKey] = [=](ValueMap properties) { return (GameObject*)Necron::deserialize(properties); };
	this->deserializers[PrincessNebea::MapKey] = [=](ValueMap properties) { return (GameObject*)PrincessNebea::deserialize(properties); };
	this->deserializers[Roger::MapKey] = [=](ValueMap properties) { return (GameObject*)Roger::deserialize(properties); };
	this->deserializers[Thion::MapKey] = [=](ValueMap properties) { return (GameObject*)Thion::deserialize(properties); };
	this->deserializers[Ursula::MapKey] = [=](ValueMap properties) { return (GameObject*)Ursula::deserialize(properties); };
	this->deserializers[Vesuvius::MapKey] = [=](ValueMap properties) { return (GameObject*)Vesuvius::deserialize(properties); };
	this->deserializers[Viper::MapKey] = [=](ValueMap properties) { return (GameObject*)Viper::deserialize(properties); };
	this->deserializers[Zana::MapKey] = [=](ValueMap properties) { return (GameObject*)Zana::deserialize(properties); };
	this->deserializers[Zelina::MapKey] = [=](ValueMap properties) { return (GameObject*)Zelina::deserialize(properties); };
	this->deserializers[Barbarian::MapKey] = [=](ValueMap properties) { return (GameObject*)Barbarian::deserialize(properties); };
	this->deserializers[EarthElemental::MapKey] = [=](ValueMap properties) { return (GameObject*)EarthElemental::deserialize(properties); };
	this->deserializers[EarthGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)EarthGolem::deserialize(properties); };
	this->deserializers[ForestGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)ForestGolem::deserialize(properties); };
	this->deserializers[Gorilla::MapKey] = [=](ValueMap properties) { return (GameObject*)Gorilla::deserialize(properties); };
	this->deserializers[LightningGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)LightningGolem::deserialize(properties); };
	this->deserializers[Rhinoman::MapKey] = [=](ValueMap properties) { return (GameObject*)Rhinoman::deserialize(properties); };
	this->deserializers[Shaman::MapKey] = [=](ValueMap properties) { return (GameObject*)Shaman::deserialize(properties); };
	this->deserializers[SkeletalArcher::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalArcher::deserialize(properties); };
	this->deserializers[SkeletalNecromancer::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalNecromancer::deserialize(properties); };
	this->deserializers[SkeletalWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)SkeletalWarrior::deserialize(properties); };
	this->deserializers[TikiGolem::MapKey] = [=](ValueMap properties) { return (GameObject*)TikiGolem::deserialize(properties); };
	this->deserializers[Gecky::MapKey] = [=](ValueMap properties) { return (GameObject*)Gecky::deserialize(properties); };
	this->deserializers[Alder::MapKey] = [=](ValueMap properties) { return (GameObject*)Alder::deserialize(properties); };
	this->deserializers[Bonnie::MapKey] = [=](ValueMap properties) { return (GameObject*)Bonnie::deserialize(properties); };
	this->deserializers[Brock::MapKey] = [=](ValueMap properties) { return (GameObject*)Brock::deserialize(properties); };
	this->deserializers[Burch::MapKey] = [=](ValueMap properties) { return (GameObject*)Burch::deserialize(properties); };
	this->deserializers[Cypress::MapKey] = [=](ValueMap properties) { return (GameObject*)Cypress::deserialize(properties); };
	this->deserializers[Finch::MapKey] = [=](ValueMap properties) { return (GameObject*)Finch::deserialize(properties); };
	this->deserializers[Fraya::MapKey] = [=](ValueMap properties) { return (GameObject*)Fraya::deserialize(properties); };
	this->deserializers[Jasper::MapKey] = [=](ValueMap properties) { return (GameObject*)Jasper::deserialize(properties); };
	this->deserializers[Mildred::MapKey] = [=](ValueMap properties) { return (GameObject*)Mildred::deserialize(properties); };
	this->deserializers[Olive::MapKey] = [=](ValueMap properties) { return (GameObject*)Olive::deserialize(properties); };
	this->deserializers[PrincessDawn::MapKey] = [=](ValueMap properties) { return (GameObject*)PrincessDawn::deserialize(properties); };
	this->deserializers[Raka::MapKey] = [=](ValueMap properties) { return (GameObject*)Raka::deserialize(properties); };
	this->deserializers[Sarude::MapKey] = [=](ValueMap properties) { return (GameObject*)Sarude::deserialize(properties); };
	this->deserializers[Shen::MapKey] = [=](ValueMap properties) { return (GameObject*)Shen::deserialize(properties); };
	this->deserializers[AnubisPup::MapKey] = [=](ValueMap properties) { return (GameObject*)AnubisPup::deserialize(properties); };
	this->deserializers[AnubisWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)AnubisWarrior::deserialize(properties); };
	this->deserializers[LionMan::MapKey] = [=](ValueMap properties) { return (GameObject*)LionMan::deserialize(properties); };
	this->deserializers[Lioness::MapKey] = [=](ValueMap properties) { return (GameObject*)Lioness::deserialize(properties); };
	this->deserializers[Medusa::MapKey] = [=](ValueMap properties) { return (GameObject*)Medusa::deserialize(properties); };
	this->deserializers[Mermaid::MapKey] = [=](ValueMap properties) { return (GameObject*)Mermaid::deserialize(properties); };
	this->deserializers[Minotaur::MapKey] = [=](ValueMap properties) { return (GameObject*)Minotaur::deserialize(properties); };
	this->deserializers[MummyPriest::MapKey] = [=](ValueMap properties) { return (GameObject*)MummyPriest::deserialize(properties); };
	this->deserializers[MummyWarrior::MapKey] = [=](ValueMap properties) { return (GameObject*)MummyWarrior::deserialize(properties); };
	this->deserializers[Osiris::MapKey] = [=](ValueMap properties) { return (GameObject*)Osiris::deserialize(properties); };
	this->deserializers[TigerMan::MapKey] = [=](ValueMap properties) { return (GameObject*)TigerMan::deserialize(properties); };
	this->deserializers[Tigress::MapKey] = [=](ValueMap properties) { return (GameObject*)Tigress::deserialize(properties); };
	this->deserializers[Ajax::MapKey] = [=](ValueMap properties) { return (GameObject*)Ajax::deserialize(properties); };
	this->deserializers[Angel::MapKey] = [=](ValueMap properties) { return (GameObject*)Angel::deserialize(properties); };
	this->deserializers[Aphrodite::MapKey] = [=](ValueMap properties) { return (GameObject*)Aphrodite::deserialize(properties); };
	this->deserializers[Ares::MapKey] = [=](ValueMap properties) { return (GameObject*)Ares::deserialize(properties); };
	this->deserializers[Athena::MapKey] = [=](ValueMap properties) { return (GameObject*)Athena::deserialize(properties); };
	this->deserializers[Cleopatra::MapKey] = [=](ValueMap properties) { return (GameObject*)Cleopatra::deserialize(properties); };
	this->deserializers[Geryon::MapKey] = [=](ValueMap properties) { return (GameObject*)Geryon::deserialize(properties); };
	this->deserializers[Griffin::MapKey] = [=](ValueMap properties) { return (GameObject*)Griffin::deserialize(properties); };
	this->deserializers[Hades::MapKey] = [=](ValueMap properties) { return (GameObject*)Hades::deserialize(properties); };
	this->deserializers[Hera::MapKey] = [=](ValueMap properties) { return (GameObject*)Hera::deserialize(properties); };
	this->deserializers[Horus::MapKey] = [=](ValueMap properties) { return (GameObject*)Horus::deserialize(properties); };
	this->deserializers[Poseidon::MapKey] = [=](ValueMap properties) { return (GameObject*)Poseidon::deserialize(properties); };
	this->deserializers[Thor::MapKey] = [=](ValueMap properties) { return (GameObject*)Thor::deserialize(properties); };
	this->deserializers[Zeus::MapKey] = [=](ValueMap properties) { return (GameObject*)Zeus::deserialize(properties); };
	this->deserializers[Abomination::MapKey] = [=](ValueMap properties) { return (GameObject*)Abomination::deserialize(properties); };
	this->deserializers[Assassin::MapKey] = [=](ValueMap properties) { return (GameObject*)Assassin::deserialize(properties); };
	this->deserializers[BoneKnight::MapKey] = [=](ValueMap properties) { return (GameObject*)BoneKnight::deserialize(properties); };
	this->deserializers[DarkTiger::MapKey] = [=](ValueMap properties) { return (GameObject*)DarkTiger::deserialize(properties); };
	this->deserializers[EvilEye::MapKey] = [=](ValueMap properties) { return (GameObject*)EvilEye::deserialize(properties); };
	this->deserializers[Exterminator::MapKey] = [=](ValueMap properties) { return (GameObject*)Exterminator::deserialize(properties); };
	this->deserializers[Gargoyle::MapKey] = [=](ValueMap properties) { return (GameObject*)Gargoyle::deserialize(properties); };
	this->deserializers[Shade::MapKey] = [=](ValueMap properties) { return (GameObject*)Shade::deserialize(properties); };
	this->deserializers[VoidArcher::MapKey] = [=](ValueMap properties) { return (GameObject*)VoidArcher::deserialize(properties); };
	this->deserializers[VoidDemon::MapKey] = [=](ValueMap properties) { return (GameObject*)VoidDemon::deserialize(properties); };
	this->deserializers[Warlock::MapKey] = [=](ValueMap properties) { return (GameObject*)Warlock::deserialize(properties); };
	this->deserializers[Professor::MapKey] = [=](ValueMap properties) { return (GameObject*)Professor::deserialize(properties); };
	this->deserializers[Robot::MapKey] = [=](ValueMap properties) { return (GameObject*)Robot::deserialize(properties); };
	this->deserializers[Atreus::MapKey] = [=](ValueMap properties) { return (GameObject*)Atreus::deserialize(properties); };
	this->deserializers[Bancroft::MapKey] = [=](ValueMap properties) { return (GameObject*)Bancroft::deserialize(properties); };
	this->deserializers[Godiva::MapKey] = [=](ValueMap properties) { return (GameObject*)Godiva::deserialize(properties); };
	this->deserializers[Illia::MapKey] = [=](ValueMap properties) { return (GameObject*)Illia::deserialize(properties); };
	this->deserializers[Leon::MapKey] = [=](ValueMap properties) { return (GameObject*)Leon::deserialize(properties); };
	this->deserializers[Mara::MapKey] = [=](ValueMap properties) { return (GameObject*)Mara::deserialize(properties); };
	this->deserializers[Marcel::MapKey] = [=](ValueMap properties) { return (GameObject*)Marcel::deserialize(properties); };
	this->deserializers[Piper::MapKey] = [=](ValueMap properties) { return (GameObject*)Piper::deserialize(properties); };
	this->deserializers[QueenElise::MapKey] = [=](ValueMap properties) { return (GameObject*)QueenElise::deserialize(properties); };
	this->deserializers[Radon::MapKey] = [=](ValueMap properties) { return (GameObject*)Radon::deserialize(properties); };
	this->deserializers[Ralston::MapKey] = [=](ValueMap properties) { return (GameObject*)Ralston::deserialize(properties); };
	this->deserializers[Xenon::MapKey] = [=](ValueMap properties) { return (GameObject*)Xenon::deserialize(properties); };
	this->deserializers[Ysara::MapKey] = [=](ValueMap properties) { return (GameObject*)Ysara::deserialize(properties); };
}

PlatformerEntityDeserializer::~PlatformerEntityDeserializer()
{
}
