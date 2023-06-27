#include "StatsTables.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

StatsTables* StatsTables::Instance = nullptr;
std::map<std::string, StatsTables::StatsIncrements> StatsTables::StatsTable = std::map<std::string, StatsTables::StatsIncrements>();

const int StatsTables::FallbackExp = 666;
const int StatsTables::FallbackMana = 69;
const int StatsTables::FallbackHealth = 420;

void StatsTables::RegisterGlobalNode()
{
	GlobalDirector::getInstance()->RegisterGlobalNode(StatsTables::getInstance());
}

StatsTables* StatsTables::getInstance()
{
	if (StatsTables::Instance == nullptr)
	{
		StatsTables::Instance = new StatsTables();
	}

	return StatsTables::Instance;
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
	
	StatsIncrements NpcStats = StatsIncrements(Stats(10, 10, 10));

	// SQUALLY
	StatsTables::StatsTable[Squally::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);

	// HELPERS
	StatsTables::StatsTable[CritterDemon::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[Gecky::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[Grim::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[Ghost::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[Guano::MapKey] = StatsIncrements(Stats(14, 4, 48), increments);
	StatsTables::StatsTable[GuanoPetrified::MapKey] = StatsIncrements(Stats(20, 0, 10000));
	StatsTables::StatsTable[Robot::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	StatsTables::StatsTable[Snowman::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	StatsTables::StatsTable[YetiBaby::MapKey] = StatsIncrements(Stats(16, 8, 48), increments);
	
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

	StatsTables::StatsTable[Ara::MapKey] = NpcStats;
	StatsTables::StatsTable[Bard::MapKey] = NpcStats;
	StatsTables::StatsTable[Blackbeard::MapKey] = NpcStats;
	StatsTables::StatsTable[Chiron::MapKey] = NpcStats;
	StatsTables::StatsTable[Elriel::MapKey] = NpcStats;
	StatsTables::StatsTable[Gramps::MapKey] = NpcStats;
	StatsTables::StatsTable[QueenLiana::MapKey] = NpcStats;
	StatsTables::StatsTable[Lycan::MapKey] = NpcStats;
	StatsTables::StatsTable[Mara::MapKey] = NpcStats;
	StatsTables::StatsTable[Minos::MapKey] = NpcStats;
	StatsTables::StatsTable[Polyphemus::MapKey] = NpcStats;
	StatsTables::StatsTable[Matu::MapKey] = NpcStats;
	StatsTables::StatsTable[Robin::MapKey] = NpcStats;
	StatsTables::StatsTable[Toben::MapKey] = NpcStats;

	/***********
		UR
	************/

	StatsTables::StatsTable[AnubisPup::MapKey] = StatsIncrements(Stats(36, 35, 87));
	StatsTables::StatsTable[AnubisWarrior::MapKey] = StatsIncrements(Stats(52, 16, 94));
	StatsTables::StatsTable[LionMan::MapKey] = StatsIncrements(Stats(42, 12, 67));
	StatsTables::StatsTable[Lioness::MapKey] = StatsIncrements(Stats(33, 9, 64));
	StatsTables::StatsTable[DarkTiger::MapKey] = StatsIncrements(Stats(48, 15, 32));
	StatsTables::StatsTable[Medusa::MapKey] = StatsIncrements(Stats(51, 8, 95));
	StatsTables::StatsTable[Mermaid::MapKey] = StatsIncrements(Stats(31, 8, 74));
	StatsTables::StatsTable[Minotaur::MapKey] = StatsIncrements(Stats(42, 8, 68));
	StatsTables::StatsTable[MummyPriest::MapKey] = StatsIncrements(Stats(44, 30, 80));
	StatsTables::StatsTable[MummyWarrior::MapKey] = StatsIncrements(Stats(43, 8, 84));
	StatsTables::StatsTable[Osiris::MapKey] = StatsIncrements(Stats(105, 12, 224));
	StatsTables::StatsTable[TigerMan::MapKey] = StatsIncrements(Stats(63, 15, 62));
	StatsTables::StatsTable[Tigress::MapKey] = StatsIncrements(Stats(38, 11, 58));
	
	StatsTables::StatsTable[Appolo::MapKey] = NpcStats;
	StatsTables::StatsTable[Ajax::MapKey] = NpcStats;
	StatsTables::StatsTable[Angel::MapKey] = NpcStats;
	StatsTables::StatsTable[Aphrodite::MapKey] = NpcStats;
	StatsTables::StatsTable[Ares::MapKey] = NpcStats;
	StatsTables::StatsTable[Athena::MapKey] = NpcStats;
	StatsTables::StatsTable[Cleopatra::MapKey] = NpcStats;
	StatsTables::StatsTable[Geryon::MapKey] = NpcStats;
	StatsTables::StatsTable[Griffin::MapKey] = NpcStats;
	StatsTables::StatsTable[Hades::MapKey] = NpcStats;
	StatsTables::StatsTable[Hera::MapKey] = NpcStats;
	StatsTables::StatsTable[Horus::MapKey] = NpcStats;
	StatsTables::StatsTable[Poseidon::MapKey] = NpcStats;
	StatsTables::StatsTable[Thor::MapKey] = NpcStats;
	StatsTables::StatsTable[Zeus::MapKey] = NpcStats;

	/***********
		DM
	************/

	StatsTables::StatsTable[EarthElemental::MapKey] = StatsIncrements(Stats(55, 12, 80));
	StatsTables::StatsTable[EarthGolem::MapKey] = StatsIncrements(Stats(55, 12, 80));
	StatsTables::StatsTable[ForestGolem::MapKey] = StatsIncrements(Stats(55, 12, 80));
	StatsTables::StatsTable[Rhinoman::MapKey] = StatsIncrements(Stats(224, 12, 240));
	StatsTables::StatsTable[Shaman::MapKey] = StatsIncrements(Stats(40, 24, 80));
	StatsTables::StatsTable[SkeletalArcher::MapKey] = StatsIncrements(Stats(55, 12, 96));
	StatsTables::StatsTable[SkeletalNecromancer::MapKey] = StatsIncrements(Stats(55, 12, 99));
	StatsTables::StatsTable[SkeletalWarrior::MapKey] = StatsIncrements(Stats(55, 12, 98));
	StatsTables::StatsTable[SkeletalPirate::MapKey] = StatsIncrements(Stats(56, 16, 97));
	StatsTables::StatsTable[TikiGolem::MapKey] = StatsIncrements(Stats(60, 12, 80));
	StatsTables::StatsTable[Krampus::MapKey] = StatsIncrements(Stats(224, 12, 260));

	StatsTables::StatsTable[Bancroft::MapKey] = NpcStats;
	StatsTables::StatsTable[Alder::MapKey] = NpcStats;
	StatsTables::StatsTable[Bonnie::MapKey] = NpcStats;
	StatsTables::StatsTable[Brock::MapKey] = NpcStats;
	StatsTables::StatsTable[Burch::MapKey] = NpcStats;
	StatsTables::StatsTable[Finch::MapKey] = NpcStats;
	StatsTables::StatsTable[Fraya::MapKey] = NpcStats;
	StatsTables::StatsTable[Godiva::MapKey] = NpcStats;
	StatsTables::StatsTable[Jasper::MapKey] = NpcStats;
	StatsTables::StatsTable[Mildred::MapKey] = NpcStats;
	StatsTables::StatsTable[Olive::MapKey] = NpcStats;
	StatsTables::StatsTable[PrincessDawn::MapKey] = NpcStats;
	StatsTables::StatsTable[Raka::MapKey] = NpcStats;
	StatsTables::StatsTable[Ralston::MapKey] = NpcStats;
	StatsTables::StatsTable[Sarude::MapKey] = NpcStats;
	StatsTables::StatsTable[Shen::MapKey] = NpcStats;

	/***********
		CV
	************/

	StatsTables::StatsTable[Abomination::MapKey] = StatsIncrements(Stats(53, 8, 116));
	StatsTables::StatsTable[Agnes::MapKey] = StatsIncrements(Stats(135, 20, 320));
	StatsTables::StatsTable[Barbarian::MapKey] = StatsIncrements(Stats(65, 12, 95));
	StatsTables::StatsTable[Jack::MapKey] = StatsIncrements(Stats(85, 10, 160)); 
	StatsTables::StatsTable[ReanimatedFighter::MapKey] = StatsIncrements(Stats(68, 10, 105));
	StatsTables::StatsTable[Reaper::MapKey] = StatsIncrements(Stats(15, 26, 125));
	StatsTables::StatsTable[SkeletalBaron::MapKey] = StatsIncrements(Stats(84, 12, 130));
	StatsTables::StatsTable[Thug::MapKey] = StatsIncrements(Stats(48, 4, 90));
	StatsTables::StatsTable[VampireLord::MapKey] = StatsIncrements(Stats(77, 8, 121));
	StatsTables::StatsTable[Vampiress::MapKey] = StatsIncrements(Stats(46, 24, 118));
	StatsTables::StatsTable[Undead::MapKey] = StatsIncrements(Stats(49, 6, 109));
	StatsTables::StatsTable[Werewolf::MapKey] = StatsIncrements(Stats(52, 13, 115));
	StatsTables::StatsTable[Wraith::MapKey] = StatsIncrements(Stats(64, 22, 116));
	
	StatsTables::StatsTable[Atreus::MapKey] = NpcStats;
	StatsTables::StatsTable[Knight::MapKey] = NpcStats;
	StatsTables::StatsTable[Elric::MapKey] = NpcStats;
	StatsTables::StatsTable[Garin::MapKey] = NpcStats;
	StatsTables::StatsTable[Gaunt::MapKey] = NpcStats;
	StatsTables::StatsTable[Illia::MapKey] = NpcStats;
	StatsTables::StatsTable[KingRedsong::MapKey] = NpcStats;
	StatsTables::StatsTable[KingRedsongSlime::MapKey] = NpcStats;
	StatsTables::StatsTable[Leon::MapKey] = NpcStats;
	StatsTables::StatsTable[Leopold::MapKey] = NpcStats;
	StatsTables::StatsTable[Leroy::MapKey] = NpcStats;
	StatsTables::StatsTable[Mabel::MapKey] = NpcStats;
	StatsTables::StatsTable[Merlin::MapKey] = NpcStats;
	StatsTables::StatsTable[PrincessOpal::MapKey] = NpcStats;
	StatsTables::StatsTable[Raven::MapKey] = NpcStats;
	StatsTables::StatsTable[Rogas::MapKey] = NpcStats;
	StatsTables::StatsTable[Thurstan::MapKey] = NpcStats;
	StatsTables::StatsTable[Tyracius::MapKey] = NpcStats;

	/***********
		LC
	************/
	
	StatsTables::StatsTable[Assassin::MapKey] = StatsIncrements(Stats(49, 8, 118));
	StatsTables::StatsTable[BoneKnight::MapKey] = StatsIncrements(Stats(80, 12, 121));
	StatsTables::StatsTable[BoneFiend::MapKey] = StatsIncrements(Stats(70, 8, 119));
	StatsTables::StatsTable[Hunter::MapKey] = StatsIncrements(Stats(55, 14, 117));
	StatsTables::StatsTable[KingZul::MapKey] = StatsIncrements(Stats(160, 18, 236));
	StatsTables::StatsTable[Lazarus::MapKey] = StatsIncrements(Stats(124, 38, 214));
	StatsTables::StatsTable[Mystic::MapKey] = StatsIncrements(Stats(72, 22, 110));
	StatsTables::StatsTable[ReanimatedPig::MapKey] = StatsIncrements(Stats(75, 10, 105));
	StatsTables::StatsTable[SkeletalCleaver::MapKey] = StatsIncrements(Stats(84, 8, 123));
	StatsTables::StatsTable[SkeletalKnight::MapKey] = StatsIncrements(Stats(85, 10, 122));
	StatsTables::StatsTable[SkeletalPriestess::MapKey] = StatsIncrements(Stats(81, 20, 125));
	StatsTables::StatsTable[Warlock::MapKey] = StatsIncrements(Stats(62, 24, 113));
	StatsTables::StatsTable[Zombie::MapKey] = StatsIncrements(Stats(78, 5, 110));
	StatsTables::StatsTable[ZombieElric::MapKey] = StatsIncrements(Stats(82, 13, 140));

	StatsTables::StatsTable[Amelia::MapKey] = NpcStats;
	StatsTables::StatsTable[Azmus::MapKey] = NpcStats;
	StatsTables::StatsTable[Dudly::MapKey] = NpcStats;
	StatsTables::StatsTable[Garrick::MapKey] = NpcStats;
	StatsTables::StatsTable[Johann::MapKey] = NpcStats;
	StatsTables::StatsTable[Necron::MapKey] = NpcStats;
	StatsTables::StatsTable[PrincessNebea::MapKey] = NpcStats;
	StatsTables::StatsTable[Roger::MapKey] = NpcStats;
	StatsTables::StatsTable[Thion::MapKey] = NpcStats;
	StatsTables::StatsTable[Ursula::MapKey] = NpcStats;
	StatsTables::StatsTable[Vesuvius::MapKey] = NpcStats;
	StatsTables::StatsTable[Viper::MapKey] = NpcStats;
	StatsTables::StatsTable[Zana::MapKey] = NpcStats;
	StatsTables::StatsTable[Zelina::MapKey] = NpcStats;

	/***********
		FF
	************/

	StatsTables::StatsTable[Asmodeus::MapKey] = StatsIncrements(Stats(165, 30, 315));
	StatsTables::StatsTable[DemonArcher::MapKey] = StatsIncrements(Stats(93, 14, 133));
	StatsTables::StatsTable[DemonDragon::MapKey] = StatsIncrements(Stats(92, 12, 131));
	StatsTables::StatsTable[DemonGhost::MapKey] = StatsIncrements(Stats(90, 10, 129));
	StatsTables::StatsTable[DemonGrunt::MapKey] = StatsIncrements(Stats(94, 8, 133));
	StatsTables::StatsTable[DemonRogue::MapKey] = StatsIncrements(Stats(88, 8, 127));
	StatsTables::StatsTable[DemonShaman::MapKey] = StatsIncrements(Stats(82, 20, 130));
	StatsTables::StatsTable[DemonSwordsman::MapKey] = StatsIncrements(Stats(97, 8, 125));
	StatsTables::StatsTable[DemonWarrior::MapKey] = StatsIncrements(Stats(80, 8, 136));
	StatsTables::StatsTable[FireElemental::MapKey] = StatsIncrements(Stats(89, 8, 127));
	StatsTables::StatsTable[FireTiger::MapKey] = StatsIncrements(Stats(91, 8, 138));
	StatsTables::StatsTable[LavaGolem::MapKey] = StatsIncrements(Stats(87, 11, 130));

	StatsTables::StatsTable[Ash::MapKey] = NpcStats;
	StatsTables::StatsTable[Brine::MapKey] = NpcStats;
	StatsTables::StatsTable[Celeste::MapKey] = NpcStats;
	StatsTables::StatsTable[Cindra::MapKey] = NpcStats;
	StatsTables::StatsTable[Drak::MapKey] = NpcStats;
	StatsTables::StatsTable[Igneus::MapKey] = NpcStats;
	StatsTables::StatsTable[Lucifer::MapKey] = NpcStats;
	StatsTables::StatsTable[Magnus::MapKey] = NpcStats;
	StatsTables::StatsTable[Pan::MapKey] = NpcStats;
	StatsTables::StatsTable[QueenElise::MapKey] = NpcStats;
	StatsTables::StatsTable[Ragnis::MapKey] = NpcStats;
	StatsTables::StatsTable[Rupert::MapKey] = NpcStats;
	StatsTables::StatsTable[Rusty::MapKey] = NpcStats;
	StatsTables::StatsTable[Scaldor::MapKey] = NpcStats;
	StatsTables::StatsTable[Mittens::MapKey] = NpcStats;

	/***********
		BP
	************/

	StatsTables::StatsTable[Cryogen::MapKey] = StatsIncrements(Stats(248, 8, 420));
	StatsTables::StatsTable[FrostFiend::MapKey] = StatsIncrements(Stats(96, 8, 136));
	StatsTables::StatsTable[GoblinElf::MapKey] = StatsIncrements(Stats(90, 8, 130));
	StatsTables::StatsTable[IceGolem::MapKey] = StatsIncrements(Stats(95, 8, 135));
	StatsTables::StatsTable[PenguinGrunt::MapKey] = StatsIncrements(Stats(92, 8, 132));
	StatsTables::StatsTable[PenguinWarrior::MapKey] = StatsIncrements(Stats(94, 8, 134));
	StatsTables::StatsTable[Santa::MapKey] = StatsIncrements(Stats(224, 8, 392));
	StatsTables::StatsTable[SnowFiend::MapKey] = StatsIncrements(Stats(100, 8, 140));
	StatsTables::StatsTable[ToySoldierGoblin::MapKey] = StatsIncrements(Stats(93, 8, 133));
	StatsTables::StatsTable[WaterElemental::MapKey] = StatsIncrements(Stats(94, 8, 134));
	StatsTables::StatsTable[Yeti::MapKey] = StatsIncrements(Stats(98, 8, 138));
	
	StatsTables::StatsTable[Viking::MapKey] = NpcStats;
	StatsTables::StatsTable[Snowman::MapKey] = NpcStats;
	StatsTables::StatsTable[Aspen::MapKey] = NpcStats;
	StatsTables::StatsTable[Aster::MapKey] = NpcStats;
	StatsTables::StatsTable[Bodom::MapKey] = NpcStats;
	StatsTables::StatsTable[Cookie::MapKey] = NpcStats;
	StatsTables::StatsTable[Cooper::MapKey] = NpcStats;
	StatsTables::StatsTable[Irmik::MapKey] = NpcStats;
	StatsTables::StatsTable[Jingles::MapKey] = NpcStats;
	StatsTables::StatsTable[Juniper::MapKey] = NpcStats;
	StatsTables::StatsTable[Kringle::MapKey] = NpcStats;
	StatsTables::StatsTable[Nessie::MapKey] = NpcStats;
	StatsTables::StatsTable[PrincessPepper::MapKey] = NpcStats;
	StatsTables::StatsTable[Thatcher::MapKey] = NpcStats;
	StatsTables::StatsTable[Theldar::MapKey] = NpcStats;
	StatsTables::StatsTable[Tinsel::MapKey] = NpcStats;
	StatsTables::StatsTable[Ysara::MapKey] = NpcStats;

	/***********
		VS
	************/
	
	StatsTables::StatsTable[Exterminator::MapKey] = StatsIncrements(Stats(95, 32, 140));
	StatsTables::StatsTable[Perceptron::MapKey] = StatsIncrements(Stats(999, 999, 1024));
	StatsTables::StatsTable[VoidDemon::MapKey] = StatsIncrements(Stats(90, 64, 145));
	
	StatsTables::StatsTable[Boron::MapKey] = NpcStats;
	StatsTables::StatsTable[Radon::MapKey] = NpcStats;
	StatsTables::StatsTable[Xenon::MapKey] = NpcStats;

	/***********
		MAGES
	************/
	StatsTables::StatsTable[Marcel::MapKey] = NpcStats;
	StatsTables::StatsTable[Piper::MapKey] = NpcStats;

	/***********
		MISC
	************/
	StatsTables::StatsTable[KillingMachine1::MapKey] = StatsIncrements(Stats(75, 0, 0));
	StatsTables::StatsTable[KillingMachine2::MapKey] = StatsIncrements(Stats(75, 0, 0));
	StatsTables::StatsTable[KillingMachine3::MapKey] = StatsIncrements(Stats(75, 0, 0));
	StatsTables::StatsTable[KillingMachine4::MapKey] = StatsIncrements(Stats(75, 0, 0));
	StatsTables::StatsTable[KillingMachine5::MapKey] = StatsIncrements(Stats(75, 0, 0));
	StatsTables::StatsTable[KillingMachine6::MapKey] = StatsIncrements(Stats(75, 0, 0));
	
	/***********
		DEPRECATED
	************/
	StatsTables::StatsTable[Gargoyle::MapKey] = StatsIncrements(Stats(72, 8, 105));
	StatsTables::StatsTable[Gorilla::MapKey] = StatsIncrements(Stats(55, 12, 80));
	StatsTables::StatsTable[LightningGolem::MapKey] = StatsIncrements(Stats(95, 8, 105));
	StatsTables::StatsTable[Scarecrow::MapKey] = StatsIncrements(Stats(66, 8, 105));
	StatsTables::StatsTable[Shade::MapKey] = StatsIncrements(Stats(66, 8, 105));
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
