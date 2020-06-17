#include "StatsTables.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

StatsTables* StatsTables::instance = nullptr;
std::map<std::string, StatsTables::StatsIncrements> StatsTables::StatsTable = std::map<std::string, StatsTables::StatsIncrements>();

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
	// These are the standard stat increment gains from leveling up
	// HP | MP | ATK | M.ATT | ARMOR | SPEED | REQ. EXP
	std::vector<Stats> increments = {
		// 2x (1-5)
		Stats(2, 1, 1, 1, 0, 0.01f, 64),
		Stats(2, 1, 1, 1, 0, 0.01f, 128),
		Stats(2, 1, 1, 1, 0, 0.01f, 256),
		Stats(2, 1, 1, 1, 0, 0.01f, 512),
		Stats(2, 1, 1, 1, 0, 0.01f, 1024),

		// 1.25x (6-10)
		Stats(2, 1, 1, 1, 0, 0.01f, 1280),
		Stats(3, 2, 1, 1, 0, 0.01f, 1600),
		Stats(3, 2, 1, 1, 0, 0.01f, 2000),
		Stats(3, 2, 1, 1, 0, 0.01f, 2500),
		Stats(3, 2, 1, 1, 0, 0.01f, 3125),
		
		// 1.1x (11-15)
		Stats(3, 2, 1, 1, 0, 0.01f, 3437),
		Stats(4, 3, 1, 1, 0, 0.01f, 3781),
		Stats(4, 3, 1, 1, 0, 0.01f, 4159),
		Stats(4, 3, 1, 1, 0, 0.01f, 4575),
		Stats(4, 3, 1, 1, 0, 0.01f, 5032),

		// 1.1x (16-20)
		Stats(4, 3, 1, 1, 0, 0.01f, 5535),
		Stats(4, 3, 1, 1, 0, 0.01f, 6088),
		Stats(4, 3, 1, 1, 0, 0.01f, 6697),
		Stats(4, 3, 1, 1, 0, 0.01f, 7367),
		Stats(4, 3, 1, 1, 0, 0.01f, 8104),

		// 1.1x, no stat gain
		Stats(4, 3, 1, 1, 0, 0.00f, 8914),
		Stats(4, 3, 1, 1, 0, 0.00f, 9805),
		Stats(0, 0, 0, 0, 0, 0.0f, 10786),
		Stats(0, 0, 0, 0, 0, 0.0f, 11865),
		Stats(0, 0, 0, 0, 0, 0.0f, 13051),
		Stats(0, 0, 0, 0, 0, 0.0f, 14356),
		Stats(0, 0, 0, 0, 0, 0.0f, 15792),
		Stats(0, 0, 0, 0, 0, 0.0f, 17371),
		Stats(0, 0, 0, 0, 0, 0.0f, 19109),
		Stats(0, 0, 0, 0, 0, 0.0f, 21019),
		Stats(0, 0, 0, 0, 0, 0.0f, 23121),
		Stats(0, 0, 0, 0, 0, 0.0f, 25434),
		Stats(0, 0, 0, 0, 0, 0.0f, 27977),
	};
	
	// SQUALLY
	StatsTables::StatsTable[Squally::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);

	// HELPERS
	StatsTables::StatsTable[Guano::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[GuanoPetrified::MapKey] = StatsIncrements(Stats(20, 0, 10000));
	StatsTables::StatsTable[Turtle::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	StatsTables::StatsTable[Snowman::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	StatsTables::StatsTable[YetiBaby::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	StatsTables::StatsTable[Mummy::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	
	StatsTables::StatsTable[Scrappy::MapKey] = StatsIncrements(Stats(420, 666, 32));

	/***********
		EF
	************/
	StatsTables::StatsTable[TrainingDummy::MapKey] = StatsIncrements(Stats(1000, 500, 16));
	StatsTables::StatsTable[Centaur::MapKey] = StatsIncrements(Stats(300, 200, 24));
	StatsTables::StatsTable[Cyclops::MapKey] = StatsIncrements(Stats(58, 8, 22));
	StatsTables::StatsTable[GoblinGruntBoar::MapKey] = StatsIncrements(Stats(16, 8, 20));
	StatsTables::StatsTable[GoblinShaman::MapKey] = StatsIncrements(Stats(17, 37, 24));
	StatsTables::StatsTable[GoblinWarriorPig::MapKey] = StatsIncrements(Stats(17, 8, 20));
	StatsTables::StatsTable[Ogre::MapKey] = StatsIncrements(Stats(20, 9, 18));
	StatsTables::StatsTable[OrcBomber::MapKey] = StatsIncrements(Stats(21, 22, 26));
	StatsTables::StatsTable[OrcGrunt::MapKey] = StatsIncrements(Stats(11, 8, 16));
	StatsTables::StatsTable[OrcSwordsman::MapKey] = StatsIncrements(Stats(18, 8, 24));
	StatsTables::StatsTable[OrcWarrior::MapKey] = StatsIncrements(Stats(23, 5, 24));
	StatsTables::StatsTable[Troll::MapKey] = StatsIncrements(Stats(38, 12, 20));
	StatsTables::StatsTable[KingGrogg::MapKey] = StatsIncrements(Stats(58, 60, 64));
	StatsTables::StatsTable[Gorgon::MapKey] = StatsIncrements(Stats(220, 48, 88));
	StatsTables::StatsTable[Orthrus::MapKey] = StatsIncrements(Stats(175, 48, 88));

	StatsTables::StatsTable[Ara::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Bard::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Blackbeard::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Chiron::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Elriel::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Gramps::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[QueenLiana::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Lycan::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Minos::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Polyphemus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Matu::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Robin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Toben::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		UR
	************/

	StatsTables::StatsTable[AnubisPup::MapKey] = StatsIncrements(Stats(56, 35, 87));
	StatsTables::StatsTable[AnubisWarrior::MapKey] = StatsIncrements(Stats(121, 16, 94));
	StatsTables::StatsTable[LionMan::MapKey] = StatsIncrements(Stats(42, 7, 67));
	StatsTables::StatsTable[Lioness::MapKey] = StatsIncrements(Stats(33, 9, 64));
	StatsTables::StatsTable[Medusa::MapKey] = StatsIncrements(Stats(51, 8, 95));
	StatsTables::StatsTable[Mermaid::MapKey] = StatsIncrements(Stats(31, 8, 74));
	StatsTables::StatsTable[Minotaur::MapKey] = StatsIncrements(Stats(42, 8, 68));
	StatsTables::StatsTable[MummyPriest::MapKey] = StatsIncrements(Stats(44, 30, 80));
	StatsTables::StatsTable[MummyWarrior::MapKey] = StatsIncrements(Stats(43, 8, 84));
	StatsTables::StatsTable[Osiris::MapKey] = StatsIncrements(Stats(133, 58, 224));
	StatsTables::StatsTable[TigerMan::MapKey] = StatsIncrements(Stats(68, 7, 62));
	StatsTables::StatsTable[Tigress::MapKey] = StatsIncrements(Stats(21, 11, 58));
	
	StatsTables::StatsTable[Appolo::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ajax::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Angel::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Aphrodite::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ares::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Athena::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Cleopatra::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Geryon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Griffin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Hades::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Hera::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Horus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Poseidon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Thor::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Zeus::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		SSC
	************/

	StatsTables::StatsTable[Barbarian::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[EarthElemental::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[EarthGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[ForestGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Gorilla::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[LightningGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Rhinoman::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Shaman::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalArcher::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalNecromancer::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalWarrior::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[TikiGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Krampus::MapKey] = StatsIncrements(Stats(16, 8, 32));

	StatsTables::StatsTable[Gecko::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Alder::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Bonnie::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Brock::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Burch::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Finch::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Fraya::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Jasper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Mildred::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Olive::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PrincessDawn::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Raka::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Sarude::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Shen::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		CV
	************/

	StatsTables::StatsTable[Agnes::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Jack::MapKey] =StatsIncrements(Stats(16, 8, 32)); 
	StatsTables::StatsTable[Reaper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Scarecrow::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalPirate::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Thug::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[VampireLord::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Vampiress::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Werewolf::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Wraith::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Zombie::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[ZombieElric::MapKey] = StatsIncrements(Stats(16, 8, 32));
	
	StatsTables::StatsTable[Knight::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Princess::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Elric::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Garin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Gaunt::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[KingRedsong::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[KingRedsongSlime::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Leopold::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Leroy::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Mabel::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Merlin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PrincessOpal::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Raven::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Rogas::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Thurstan::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Tyracius::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		BP
	************/

	StatsTables::StatsTable[Cryogen::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[FrostFiend::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[GoblinElf::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[IceGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PenguinGrunt::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PenguinWarrior::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Santa::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SnowFiend::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[ToySoldierGoblin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[WaterElemental::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Yeti::MapKey] = StatsIncrements(Stats(16, 8, 32));
	
	StatsTables::StatsTable[Viking::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Snowman::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Aspen::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Aster::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Bodom::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Cookie::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Cooper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Irmik::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Jingles::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Juniper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Kringle::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Nessie::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PrincessPepper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Thatcher::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Theldar::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Tinsel::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		DH
	************/

	StatsTables::StatsTable[Asmodeus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonDragon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonGhost::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonGrunt::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonRogue::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonShaman::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonSwordsman::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DemonWarrior::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[FireElemental::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[FireTiger::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[LavaGolem::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[CritterDemon::MapKey] = StatsIncrements(Stats(16, 8, 32));

	StatsTables::StatsTable[Ash::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Brine::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Celeste::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Cindra::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Drak::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Igneus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Lucifer::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Magnus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Pan::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ragnis::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Rupert::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Rusty::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Scaldor::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PrincessMittens::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		LC
	************/

	StatsTables::StatsTable[BoneFiend::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Hunter::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[KingZul::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Lazarus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Mystic::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[ReanimatedFighter::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[ReanimatedPig::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalBaron::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalCleaver::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalKnight::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[SkeletalPriestess::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Undead::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ghost::MapKey] = StatsIncrements(Stats(16, 8, 32));

	StatsTables::StatsTable[Grim::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Amelia::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Azmus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Dudly::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Garrick::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Johann::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Necron::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[PrincessNebea::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Roger::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Thion::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ursula::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Vesuvius::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Viper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Zana::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Zelina::MapKey] = StatsIncrements(Stats(16, 8, 32));

	/***********
		VS
	************/
	
	StatsTables::StatsTable[Abomination::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Assassin::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[BoneKnight::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[DarkTiger::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[EvilEye::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Exterminator::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Gargoyle::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Shade::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[VoidArcher::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[VoidDemon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Warlock::MapKey] = StatsIncrements(Stats(16, 8, 32));
	
	StatsTables::StatsTable[Professor::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Robot::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Atreus::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Bancroft::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Godiva::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Illia::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Leon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Mara::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Marcel::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Piper::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[QueenElise::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Radon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ralston::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Xenon::MapKey] = StatsIncrements(Stats(16, 8, 32));
	StatsTables::StatsTable[Ysara::MapKey] = StatsIncrements(Stats(16, 8, 32));
}

StatsTables::~StatsTables()
{
}

int StatsTables::getExpRequiredAtLevel(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		StatsIncrements stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int exp = stats.baseStats.exp;
		int levelIndex = std::min(platformerEntity->getRuntimeStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			exp += stats.increments[index].exp;	
		}

		return exp;
	}

	return StatsTables::FallbackExp;
}

int StatsTables::getKillExp(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		return StatsTables::StatsTable[platformerEntity->getEntityKey()].baseStats.exp;
	}

	return StatsTables::FallbackExp;
}

int StatsTables::getBaseMana(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		StatsIncrements stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int mana = stats.baseStats.mana;
		int levelIndex = std::min(platformerEntity->getRuntimeStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			mana += stats.increments[index].mana;	
		}

		return mana;
	}

	return StatsTables::FallbackMana;
}

int StatsTables::getBaseHealth(PlatformerEntity* platformerEntity)
{
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		StatsIncrements stats = StatsTables::StatsTable[platformerEntity->getEntityKey()];
		int health = stats.baseStats.health;
		int levelIndex = std::min(platformerEntity->getRuntimeStateOrDefaultInt(StateKeys::Eq, 1), int(stats.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			health += stats.increments[index].health;	
		}

		return health;
	}

	return StatsTables::FallbackHealth;
}

StatsTables::Stats StatsTables::getBonusStats(PlatformerEntity* platformerEntity)
{
	Stats stats = Stats();
	
	if (platformerEntity != nullptr && StatsTables::StatsTable.find(platformerEntity->getEntityKey()) != StatsTables::StatsTable.end())
	{
		StatsIncrements statsIncrements = StatsTables::StatsTable[platformerEntity->getEntityKey()];

		int levelIndex = std::min(platformerEntity->getRuntimeStateOrDefaultInt(StateKeys::Eq, 1), int(statsIncrements.increments.size())) - 1;

		for (int index = 0; index < levelIndex; index++)
		{
			stats.health += statsIncrements.increments[index].health;
			stats.mana += statsIncrements.increments[index].mana;
			stats.attack += statsIncrements.increments[index].attack;
			stats.magicAttack += statsIncrements.increments[index].magicAttack;
			stats.armor += statsIncrements.increments[index].armor;
			stats.speed += statsIncrements.increments[index].speed;
			stats.exp += statsIncrements.increments[index].exp;
		}
	}

	return stats;
}
