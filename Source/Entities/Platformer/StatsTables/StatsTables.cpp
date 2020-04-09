#include "StatsTables.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

StatsTables* StatsTables::instance = nullptr;
std::map<std::string, StatsTables::Stats> StatsTables::StatsTable = std::map<std::string, StatsTables::Stats>();

const int StatsTables::FallbackExp = 666;
const int StatsTables::FallbackMana = 69;
const int StatsTables::FallbackHealth = 420;

void StatsTables::registerGlobalNode()
{
	GlobalDirector::getInstance()->registerGlobalNode(StatsTables::getInstance());
}

StatsTables* StatsTables::getInstance()
{
	if (StatsTables::instance == nullptr)
	{
		StatsTables::instance = new StatsTables();
	}

	return StatsTables::instance;
}

StatsTables::StatsTables()
{
	// SQUALLY
	StatsTables::StatsTable[Squally::MapKey] = Stats(16, 8, 48, 
	{
		// 2x
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 256 },
		{ 2, 1, 512 },
		{ 2, 1, 1024 },
		{ 2, 1, 2048 },
		// 1.25x
		{ 3, 2, 2560 },
		{ 3, 2, 3200 },
		{ 3, 2, 4000 },
		{ 3, 2, 5000 },
		{ 3, 2, 6250 },
		// 1.1x
		{ 4, 3, 6875 },
		{ 4, 3, 7562 },
		{ 4, 3, 8318 },
		{ 4, 3, 9150 },
		{ 5, 4, 10065 },
		{ 5, 4, 11072 },
		{ 5, 4, 12179 },
		{ 5, 4, 13397 },
		{ 5, 4, 14737 },
		{ 5, 4, 16210 },
		{ 5, 4, 17831 },
		// 1.1x, no stat gain
		{ 0, 0, 19615 },
		{ 0, 0, 21576 },
		{ 0, 0, 23734 },
		{ 0, 0, 26107 },
		{ 0, 0, 28718 },
		{ 0, 0, 31590 },
		{ 0, 0, 34749 },
		{ 0, 0, 38224 },
		{ 0, 0, 42046 },
		{ 0, 0, 46251 },
		{ 0, 0, 50876 },
	});

	// HELPERS
	StatsTables::StatsTable[Guano::MapKey] = Stats(14, 4, 48, 
	{
		// 2x
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 256 },
		{ 2, 1, 512 },
		{ 2, 1, 1024 },
		{ 2, 1, 2048 },
		// 1.25x
		{ 3, 2, 2560 },
		{ 3, 2, 3200 },
		{ 3, 2, 4000 },
		{ 3, 2, 5000 },
		{ 3, 2, 6250 },
		// 1.1x
		{ 4, 3, 6875 },
		{ 4, 3, 7562 },
		{ 4, 3, 8318 },
		{ 4, 3, 9150 },
		{ 5, 4, 10065 },
		{ 5, 4, 11072 },
		{ 5, 4, 12179 },
		{ 5, 4, 13397 },
		{ 5, 4, 14737 },
		{ 5, 4, 16210 },
		{ 5, 4, 17831 },
		// 1.1x, no stat gain
		{ 0, 0, 19615 },
		{ 0, 0, 21576 },
		{ 0, 0, 23734 },
		{ 0, 0, 26107 },
		{ 0, 0, 28718 },
		{ 0, 0, 31590 },
		{ 0, 0, 34749 },
		{ 0, 0, 38224 },
		{ 0, 0, 42046 },
		{ 0, 0, 46251 },
		{ 0, 0, 50876 },
	});

	StatsTables::StatsTable[Turtle::MapKey] = Stats(16, 8, 32, 
	{
		// 2x
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 256 },
		{ 2, 1, 512 },
		{ 2, 1, 1024 },
		{ 2, 1, 2048 },
		// 1.25x
		{ 3, 2, 2560 },
		{ 3, 2, 3200 },
		{ 3, 2, 4000 },
		{ 3, 2, 5000 },
		{ 3, 2, 6250 },
		// 1.1x
		{ 4, 3, 6875 },
		{ 4, 3, 7562 },
		{ 4, 3, 8318 },
		{ 4, 3, 9150 },
		{ 5, 4, 10065 },
		{ 5, 4, 11072 },
		{ 5, 4, 12179 },
		{ 5, 4, 13397 },
		{ 5, 4, 14737 },
		{ 5, 4, 16210 },
		{ 5, 4, 17831 },
		// 1.1x, no stat gain
		{ 0, 0, 19615 },
		{ 0, 0, 21576 },
		{ 0, 0, 23734 },
		{ 0, 0, 26107 },
		{ 0, 0, 28718 },
		{ 0, 0, 31590 },
		{ 0, 0, 34749 },
		{ 0, 0, 38224 },
		{ 0, 0, 42046 },
		{ 0, 0, 46251 },
		{ 0, 0, 50876 },
	});

	StatsTables::StatsTable[Snowman::MapKey] = Stats(16, 8, 48, 
	{
		// 2x
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 256 },
		{ 2, 1, 512 },
		{ 2, 1, 1024 },
		{ 2, 1, 2048 },
		// 1.25x
		{ 3, 2, 2560 },
		{ 3, 2, 3200 },
		{ 3, 2, 4000 },
		{ 3, 2, 5000 },
		{ 3, 2, 6250 },
		// 1.1x
		{ 4, 3, 6875 },
		{ 4, 3, 7562 },
		{ 4, 3, 8318 },
		{ 4, 3, 9150 },
		{ 5, 4, 10065 },
		{ 5, 4, 11072 },
		{ 5, 4, 12179 },
		{ 5, 4, 13397 },
		{ 5, 4, 14737 },
		{ 5, 4, 16210 },
		{ 5, 4, 17831 },
		// 1.1x, no stat gain
		{ 0, 0, 19615 },
		{ 0, 0, 21576 },
		{ 0, 0, 23734 },
		{ 0, 0, 26107 },
		{ 0, 0, 28718 },
		{ 0, 0, 31590 },
		{ 0, 0, 34749 },
		{ 0, 0, 38224 },
		{ 0, 0, 42046 },
		{ 0, 0, 46251 },
		{ 0, 0, 50876 },
	});

	StatsTables::StatsTable[YetiBaby::MapKey] = Stats(16, 8, 48, 
	{
		// 2x
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 256 },
		{ 2, 1, 512 },
		{ 2, 1, 1024 },
		{ 2, 1, 2048 },
		// 1.25x
		{ 3, 2, 2560 },
		{ 3, 2, 3200 },
		{ 3, 2, 4000 },
		{ 3, 2, 5000 },
		{ 3, 2, 6250 },
		// 1.1x
		{ 4, 3, 6875 },
		{ 4, 3, 7562 },
		{ 4, 3, 8318 },
		{ 4, 3, 9150 },
		{ 5, 4, 10065 },
		{ 5, 4, 11072 },
		{ 5, 4, 12179 },
		{ 5, 4, 13397 },
		{ 5, 4, 14737 },
		{ 5, 4, 16210 },
		{ 5, 4, 17831 },
		// 1.1x, no stat gain
		{ 0, 0, 19615 },
		{ 0, 0, 21576 },
		{ 0, 0, 23734 },
		{ 0, 0, 26107 },
		{ 0, 0, 28718 },
		{ 0, 0, 31590 },
		{ 0, 0, 34749 },
		{ 0, 0, 38224 },
		{ 0, 0, 42046 },
		{ 0, 0, 46251 },
		{ 0, 0, 50876 },
	});
	
	StatsTables::StatsTable[Scrappy::MapKey] = Stats(420, 666, 32);

	/***********
		EF
	************/
	StatsTables::StatsTable[TrainingDummy::MapKey] = Stats(1000, 500, 16);
	StatsTables::StatsTable[Centaur::MapKey] = Stats(300, 200, 24);
	StatsTables::StatsTable[Cyclops::MapKey] = Stats(58, 8, 22);
	StatsTables::StatsTable[GoblinGruntBoar::MapKey] = Stats(16, 8, 20);
	StatsTables::StatsTable[GoblinShaman::MapKey] = Stats(30, 37, 24);
	StatsTables::StatsTable[GoblinWarriorPig::MapKey] = Stats(16, 8, 20);
	StatsTables::StatsTable[Ogre::MapKey] = Stats(24, 9, 18);
	StatsTables::StatsTable[OrcBomber::MapKey] = Stats(24, 22, 26);
	StatsTables::StatsTable[OrcGrunt::MapKey] = Stats(11, 8, 16);
	StatsTables::StatsTable[OrcSwordsman::MapKey] = Stats(21, 8, 24);
	StatsTables::StatsTable[OrcWarrior::MapKey] = Stats(23, 5, 24);
	StatsTables::StatsTable[Troll::MapKey] = Stats(34, 12, 20);
	StatsTables::StatsTable[KingGrogg::MapKey] = Stats(58, 36, 64);
	StatsTables::StatsTable[Gorgon::MapKey] = Stats(220, 48, 88);
	StatsTables::StatsTable[Orthrus::MapKey] = Stats(175, 48, 88);

	StatsTables::StatsTable[Ara::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bard::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Blackbeard::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Chiron::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Elriel::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gramps::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[QueenLiana::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lycan::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Minos::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Polyphemus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Matu::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Robin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Toben::MapKey] = Stats(16, 8, 32);

	/***********
		UR
	************/

	StatsTables::StatsTable[AnubisPup::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[AnubisWarrior::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[LionMan::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lioness::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Medusa::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mermaid::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Minotaur::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[MummyPriest::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[MummyWarrior::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Osiris::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[TigerMan::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tigress::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mummy::MapKey] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Appolo::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ajax::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Angel::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aphrodite::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ares::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Athena::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cleopatra::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Geryon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Griffin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hades::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hera::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Horus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Poseidon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thor::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zeus::MapKey] = Stats(16, 8, 32);

	/***********
		SSC
	************/

	StatsTables::StatsTable[Barbarian::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[EarthElemental::MapKey] = Stats(16, 8, 32);;
	StatsTables::StatsTable[EarthGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[ForestGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gorilla::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[LightningGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rhinoman::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shaman::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalArcher::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalNecromancer::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalWarrior::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[TikiGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Krampus::MapKey] = Stats(16, 8, 32);

	StatsTables::StatsTable[Gecko::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Alder::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bonnie::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Brock::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Burch::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Finch::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Fraya::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jasper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mildred::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Olive::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessDawn::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Raka::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Sarude::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shen::MapKey] = Stats(16, 8, 32);

	/***********
		CV
	************/

	StatsTables::StatsTable[Agnes::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jack::MapKey] =Stats(16, 8, 32); 
	StatsTables::StatsTable[Reaper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scarecrow::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalPirate::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thug::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[VampireLord::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Vampiress::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Werewolf::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Wraith::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zombie::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[ZombieElric::MapKey] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Knight::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Princess::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Elric::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Garin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gaunt::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingRedsong::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingRedsongSlime::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leopold::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leroy::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mabel::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Merlin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessOpal::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Raven::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rogas::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thurstan::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tyracius::MapKey] = Stats(16, 8, 32);

	/***********
		BP
	************/

	StatsTables::StatsTable[Cryogen::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[FrostFiend::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinElf::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[IceGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinGrunt::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinWarrior::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Santa::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SnowFiend::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[ToySoldierGoblin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[WaterElemental::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Yeti::MapKey] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Viking::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Snowman::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aspen::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aster::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bodom::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cookie::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cooper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Irmik::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jingles::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Juniper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Kringle::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Nessie::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessPepper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thatcher::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Theldar::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tinsel::MapKey] = Stats(16, 8, 32);

	/***********
		DH
	************/

	StatsTables::StatsTable[Asmodeus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonDragon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonGhost::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonGrunt::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonRogue::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonShaman::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonSwordsman::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonWarrior::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[FireElemental::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[FireTiger::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[LavaGolem::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[CritterDemon::MapKey] = Stats(16, 8, 32);

	StatsTables::StatsTable[Ash::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Brine::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Celeste::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cindra::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Drak::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Igneus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lucifer::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Magnus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Pan::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ragnis::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rupert::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rusty::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scaldor::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessMittens::MapKey] = Stats(16, 8, 32);

	/***********
		LC
	************/

	StatsTables::StatsTable[BoneFiend::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hunter::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingZul::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lazarus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mystic::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[ReanimatedFighter::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[ReanimatedPig::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalBaron::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalCleaver::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalKnight::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalPriestess::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Undead::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ghost::MapKey] = Stats(16, 8, 32);

	StatsTables::StatsTable[Grim::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Amelia::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Azmus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Dudly::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Garrick::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Johann::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Necron::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessNebea::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Roger::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thion::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ursula::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Vesuvius::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Viper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zana::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zelina::MapKey] = Stats(16, 8, 32);

	/***********
		VS
	************/
	
	StatsTables::StatsTable[Abomination::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Assassin::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[BoneKnight::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[DarkTiger::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[EvilEye::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Exterminator::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gargoyle::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shade::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[VoidArcher::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[VoidDemon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Warlock::MapKey] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Professor::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Robot::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Atreus::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bancroft::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Godiva::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Illia::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mara::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Marcel::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Piper::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[QueenElise::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Radon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ralston::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Xenon::MapKey] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ysara::MapKey] = Stats(16, 8, 32);
}

StatsTables::~StatsTables()
{
}

int StatsTables::getExpRequiredAtLevel(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		Stats stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int exp = stats.exp;
		int levelIndex = std::min(platformerEntity->getStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			exp += std::get<2>(stats.increments[index]);	
		}

		return exp;
	}

	return StatsTables::FallbackExp;
}

int StatsTables::getKillExp(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		return StatsTables::StatsTable[platformerEntity->getEntityKey()].exp;
	}

	return StatsTables::FallbackExp;
}

int StatsTables::getBaseMana(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		Stats stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int mana = stats.mana;
		int levelIndex = std::min(platformerEntity->getStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			mana += std::get<0>(stats.increments[index]);	
		}

		return mana;
	}

	return StatsTables::FallbackMana;
}

int StatsTables::getBaseHealth(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		Stats stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int health = stats.health;
		int levelIndex = std::min(platformerEntity->getStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			health += std::get<0>(stats.increments[index]);	
		}

		return health;
	}

	return StatsTables::FallbackHealth;
}
