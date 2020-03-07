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
	StatsTables::StatsTable[Squally::MapKeySqually] = Stats(16, 8, 48, 
	{
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 192 },
		{ 2, 1, 368 },
		{ 2, 1, 368 },
		{ 2, 1, 512 },
		{ 3, 2, 768 },
		{ 3, 2, 1024 },
		{ 3, 2, 1536 },
		{ 3, 2, 2048 },
		{ 3, 2, 3072 },
		{ 4, 3, 4096 },
		{ 4, 3, 5120 },
		{ 4, 3, 6144 },
		{ 4, 3, 6656 },
		{ 5, 4, 7168 },
		{ 5, 4, 7680 },
		{ 5, 4, 8192 },
		{ 5, 4, 8704 },
		{ 5, 4, 9216 },
		{ 5, 4, 9728 },
		{ 5, 4, 10240 }
	});

	// HELPERS
	StatsTables::StatsTable[Guano::MapKeyGuano] = Stats(16, 8, 48, 
	{
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 192 },
		{ 2, 1, 368 },
		{ 2, 1, 368 },
		{ 2, 1, 512 },
		{ 3, 2, 768 },
		{ 3, 2, 1024 },
		{ 3, 2, 1536 },
		{ 3, 2, 2048 },
		{ 3, 2, 3072 },
		{ 4, 3, 4096 },
		{ 4, 3, 5120 },
		{ 4, 3, 6144 },
		{ 4, 3, 6656 },
		{ 5, 4, 7168 },
		{ 5, 4, 7680 },
		{ 5, 4, 8192 },
		{ 5, 4, 8704 },
		{ 5, 4, 9216 },
		{ 5, 4, 9728 },
		{ 5, 4, 10240 }
	});

	StatsTables::StatsTable[Turtle::MapKeyTurtle] = Stats(16, 8, 32, 
	{
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 192 },
		{ 2, 1, 368 },
		{ 2, 1, 368 },
		{ 2, 1, 512 },
		{ 3, 2, 768 },
		{ 3, 2, 1024 },
		{ 3, 2, 1536 },
		{ 3, 2, 2048 },
		{ 3, 2, 3072 },
		{ 4, 3, 4096 },
		{ 4, 3, 5120 },
		{ 4, 3, 6144 },
		{ 4, 3, 6656 },
		{ 5, 4, 7168 },
		{ 5, 4, 7680 },
		{ 5, 4, 8192 },
		{ 5, 4, 8704 },
		{ 5, 4, 9216 },
		{ 5, 4, 9728 },
		{ 5, 4, 10240 }
	});

	StatsTables::StatsTable[Snowman::MapKeySnowman] = Stats(16, 8, 48, 
	{
		{ 2, 1, 64 },
		{ 2, 1, 128 },
		{ 2, 1, 192 },
		{ 2, 1, 368 },
		{ 2, 1, 368 },
		{ 2, 1, 512 },
		{ 3, 2, 768 },
		{ 3, 2, 1024 },
		{ 3, 2, 1536 },
		{ 3, 2, 2048 },
		{ 3, 2, 3072 },
		{ 4, 3, 4096 },
		{ 4, 3, 5120 },
		{ 4, 3, 6144 },
		{ 4, 3, 6656 },
		{ 5, 4, 7168 },
		{ 5, 4, 7680 },
		{ 5, 4, 8192 },
		{ 5, 4, 8704 },
		{ 5, 4, 9216 },
		{ 5, 4, 9728 },
		{ 5, 4, 10240 }
	});

	StatsTables::StatsTable[YetiBaby::MapKeyYetiBaby] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scrappy::MapKeyScrappy] = Stats(16, 8, 32);

	/***********
		EF
	************/
	StatsTables::StatsTable[TrainingDummy::MapKeyTrainingDummy] = Stats(1000, 500, 32);
	StatsTables::StatsTable[Centaur::MapKeyCentaur] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cyclops::MapKeyCyclops] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinGruntBoar::MapKeyGoblinGruntBoar] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinShaman::MapKeyGoblinShaman] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinWarriorPig::MapKeyGoblinWarriorPig] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ogre::MapKeyOgre] = Stats(16, 8, 32);
	StatsTables::StatsTable[OrcBomber::MapKeyOrcBomber] = Stats(16, 8, 32);
	StatsTables::StatsTable[OrcGrunt::MapKeyOrcGrunt] = Stats(11, 8, 32);
	StatsTables::StatsTable[OrcSwordsman::MapKeyOrcSwordsman] = Stats(21, 8, 32);
	StatsTables::StatsTable[OrcWarrior::MapKeyOrcWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[Troll::MapKeyTroll] = Stats(12, 8, 32);
	StatsTables::StatsTable[KingGrogg::MapKeyKingGrogg] = Stats(40, 36, 128);
	StatsTables::StatsTable[Gorgon::MapKeyGorgon] = Stats(380, 48, 224);
	StatsTables::StatsTable[Orthrus::MapKeyOrthrus] = Stats(380, 48, 224);

	StatsTables::StatsTable[Ara::MapKeyAra] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bard::MapKeyBard] = Stats(16, 8, 32);
	StatsTables::StatsTable[Blackbeard::MapKeyBlackbeard] = Stats(16, 8, 32);
	StatsTables::StatsTable[Chiron::MapKeyChiron] = Stats(16, 8, 32);
	StatsTables::StatsTable[Elriel::MapKeyElriel] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gramps::MapKeyGramps] = Stats(16, 8, 32);
	StatsTables::StatsTable[QueenLiana::MapKeyQueenLiana] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lycan::MapKeyLycan] = Stats(16, 8, 32);
	StatsTables::StatsTable[Minos::MapKeyMinos] = Stats(16, 8, 32);
	StatsTables::StatsTable[Polyphemus::MapKeyPolyphemus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Matu::MapKeyMatu] = Stats(16, 8, 32);
	StatsTables::StatsTable[Robin::MapKeyRobin] = Stats(16, 8, 32);
	StatsTables::StatsTable[Toben::MapKeyToben] = Stats(16, 8, 32);

	/***********
		UR
	************/

	StatsTables::StatsTable[AnubisPup::MapKeyAnubisPup] = Stats(16, 8, 32);
	StatsTables::StatsTable[AnubisWarrior::MapKeyAnubisWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[LionMan::MapKeyLionMan] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lioness::MapKeyLioness] = Stats(16, 8, 32);
	StatsTables::StatsTable[Medusa::MapKeyMedusa] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mermaid::MapKeyMermaid] = Stats(16, 8, 32);
	StatsTables::StatsTable[Minotaur::MapKeyMinotaur] = Stats(16, 8, 32);
	StatsTables::StatsTable[MummyPriest::MapKeyMummyPriest] = Stats(16, 8, 32);
	StatsTables::StatsTable[MummyWarrior::MapKeyMummyWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[Osiris::MapKeyOsiris] = Stats(16, 8, 32);
	StatsTables::StatsTable[TigerMan::MapKeyTigerMan] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tigress::MapKeyTigress] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mummy::MapKeyMummy] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Appolo::MapKeyAppolo] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ajax::MapKeyAjax] = Stats(16, 8, 32);
	StatsTables::StatsTable[Angel::MapKeyAngel] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aphrodite::MapKeyAphrodite] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ares::MapKeyAres] = Stats(16, 8, 32);
	StatsTables::StatsTable[Athena::MapKeyAthena] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cleopatra::MapKeyCleopatra] = Stats(16, 8, 32);
	StatsTables::StatsTable[Geryon::MapKeyGeryon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Griffin::MapKeyGriffin] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hades::MapKeyHades] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hera::MapKeyHera] = Stats(16, 8, 32);
	StatsTables::StatsTable[Horus::MapKeyHorus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Poseidon::MapKeyPoseidon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thor::MapKeyThor] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zeus::MapKeyZeus] = Stats(16, 8, 32);

	/***********
		SSC
	************/

	StatsTables::StatsTable[Barbarian::MapKeyBarbarian] = Stats(16, 8, 32);
	StatsTables::StatsTable[EarthElemental::MapKeyEarthElemental] = Stats(16, 8, 32);;
	StatsTables::StatsTable[EarthGolem::MapKeyEarthGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[ForestGolem::MapKeyForestGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gorilla::MapKeyGorilla] = Stats(16, 8, 32);
	StatsTables::StatsTable[LightningGolem::MapKeyLightningGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rhinoman::MapKeyRhinoman] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shaman::MapKeyShaman] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalArcher::MapKeySkeletalArcher] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalNecromancer::MapKeySkeletalNecromancer] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalWarrior::MapKeySkeletalWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[TikiGolem::MapKeyTikiGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[Krampus::MapKeyKrampus] = Stats(16, 8, 32);

	StatsTables::StatsTable[Gecko::MapKeyGecko] = Stats(16, 8, 32);
	StatsTables::StatsTable[Alder::MapKeyAlder] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bonnie::MapKeyBonnie] = Stats(16, 8, 32);
	StatsTables::StatsTable[Brock::MapKeyBrock] = Stats(16, 8, 32);
	StatsTables::StatsTable[Burch::MapKeyBurch] = Stats(16, 8, 32);
	StatsTables::StatsTable[Finch::MapKeyFinch] = Stats(16, 8, 32);
	StatsTables::StatsTable[Fraya::MapKeyFraya] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jasper::MapKeyJasper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mildred::MapKeyMildred] = Stats(16, 8, 32);
	StatsTables::StatsTable[Olive::MapKeyOlive] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessDawn::MapKeyPrincessDawn] = Stats(16, 8, 32);
	StatsTables::StatsTable[Raka::MapKeyRaka] = Stats(16, 8, 32);
	StatsTables::StatsTable[Sarude::MapKeySarude] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shen::MapKeyShen] = Stats(16, 8, 32);

	/***********
		CV
	************/

	StatsTables::StatsTable[Agnes::MapKeyAgnes] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jack::MapKeyJack] =Stats(16, 8, 32); 
	StatsTables::StatsTable[Reaper::MapKeyReaper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scarecrow::MapKeyScarecrow] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalPirate::MapKeySkeletalPirate] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thug::MapKeyThug] = Stats(16, 8, 32);
	StatsTables::StatsTable[VampireLord::MapKeyVampireLord] = Stats(16, 8, 32);
	StatsTables::StatsTable[Vampiress::MapKeyVampiress] = Stats(16, 8, 32);
	StatsTables::StatsTable[Werewolf::MapKeyWerewolf] = Stats(16, 8, 32);
	StatsTables::StatsTable[Wraith::MapKeyWraith] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zombie::MapKeyZombie] = Stats(16, 8, 32);
	StatsTables::StatsTable[ZombieElric::MapKeyZombieElric] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Knight::MapKeyKnight] = Stats(16, 8, 32);
	StatsTables::StatsTable[Princess::MapKeyPrincess] = Stats(16, 8, 32);
	StatsTables::StatsTable[Elric::MapKeyElric] = Stats(16, 8, 32);
	StatsTables::StatsTable[Garin::MapKeyGarin] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gaunt::MapKeyGaunt] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingRedsong::MapKeyKingRedsong] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingRedsongSlime::MapKeyKingRedsongSlime] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leopold::MapKeyLeopold] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leroy::MapKeyLeroy] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mabel::MapKeyMabel] = Stats(16, 8, 32);
	StatsTables::StatsTable[Merlin::MapKeyMerlin] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessOpal::MapKeyPrincessOpal] = Stats(16, 8, 32);
	StatsTables::StatsTable[Raven::MapKeyRaven] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rogas::MapKeyRogas] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thurstan::MapKeyThurstan] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tyracius::MapKeyTyracius] = Stats(16, 8, 32);

	/***********
		BP
	************/

	StatsTables::StatsTable[Cryogen::MapKeyCryogen] = Stats(16, 8, 32);
	StatsTables::StatsTable[FrostFiend::MapKeyFrostFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinElf::MapKeyGoblinElf] = Stats(16, 8, 32);
	StatsTables::StatsTable[IceGolem::MapKeyIceGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinGrunt::MapKeyPenguinGrunt] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinWarrior::MapKeyPenguinWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[Santa::MapKeySanta] = Stats(16, 8, 32);
	StatsTables::StatsTable[SnowFiend::MapKeySnowFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[ToySoldierGoblin::MapKeyToySoldierGoblin] = Stats(16, 8, 32);
	StatsTables::StatsTable[WaterElemental::MapKeyWaterElemental] = Stats(16, 8, 32);
	StatsTables::StatsTable[Yeti::MapKeyYeti] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Viking::MapKeyViking] = Stats(16, 8, 32);
	StatsTables::StatsTable[Snowman::MapKeySnowman] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aspen::MapKeyAspen] = Stats(16, 8, 32);
	StatsTables::StatsTable[Aster::MapKeyAster] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bodom::MapKeyBodom] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cookie::MapKeyCookie] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cooper::MapKeyCooper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Irmik::MapKeyIrmik] = Stats(16, 8, 32);
	StatsTables::StatsTable[Jingles::MapKeyJingles] = Stats(16, 8, 32);
	StatsTables::StatsTable[Juniper::MapKeyJuniper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Kringle::MapKeyKringle] = Stats(16, 8, 32);
	StatsTables::StatsTable[Nessie::MapKeyNessie] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessPepper::MapKeyPrincessPepper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thatcher::MapKeyThatcher] = Stats(16, 8, 32);
	StatsTables::StatsTable[Theldar::MapKeyTheldar] = Stats(16, 8, 32);
	StatsTables::StatsTable[Tinsel::MapKeyTinsel] = Stats(16, 8, 32);

	/***********
		DH
	************/

	StatsTables::StatsTable[Asmodeus::MapKeyAsmodeus] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonDragon::MapKeyDemonDragon] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonGhost::MapKeyDemonGhost] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonGrunt::MapKeyDemonGrunt] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonRogue::MapKeyDemonRogue] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonShaman::MapKeyDemonShaman] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonSwordsman::MapKeyDemonSwordsman] = Stats(16, 8, 32);
	StatsTables::StatsTable[DemonWarrior::MapKeyDemonWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[FireElemental::MapKeyFireElemental] = Stats(16, 8, 32);
	StatsTables::StatsTable[FireTiger::MapKeyFireTiger] = Stats(16, 8, 32);
	StatsTables::StatsTable[LavaGolem::MapKeyLavaGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[CritterDemon::MapKeyCritterDemon] = Stats(16, 8, 32);

	StatsTables::StatsTable[Ash::MapKeyAsh] = Stats(16, 8, 32);
	StatsTables::StatsTable[Brine::MapKeyBrine] = Stats(16, 8, 32);
	StatsTables::StatsTable[Celeste::MapKeyCeleste] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cindra::MapKeyCindra] = Stats(16, 8, 32);
	StatsTables::StatsTable[Drak::MapKeyDrak] = Stats(16, 8, 32);
	StatsTables::StatsTable[Igneus::MapKeyIgneus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lucifer::MapKeyLucifer] = Stats(16, 8, 32);
	StatsTables::StatsTable[Magnus::MapKeyMagnus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Pan::MapKeyPan] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ragnis::MapKeyRagnis] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rupert::MapKeyRupert] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rusty::MapKeyRusty] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scaldor::MapKeyScaldor] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessMittens::MapKeyPrincessMittens] = Stats(16, 8, 32);

	/***********
		LC
	************/

	StatsTables::StatsTable[BoneFiend::MapKeyBoneFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hunter::MapKeyHunter] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingZul::MapKeyKingZul] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lazarus::MapKeyLazarus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mystic::MapKeyMystic] = Stats(16, 8, 32);
	StatsTables::StatsTable[ReanimatedFighter::MapKeyReanimatedFighter] = Stats(16, 8, 32);
	StatsTables::StatsTable[ReanimatedPig::MapKeyReanimatedPig] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalBaron::MapKeySkeletalBaron] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalCleaver::MapKeySkeletalCleaver] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalKnight::MapKeySkeletalKnight] = Stats(16, 8, 32);
	StatsTables::StatsTable[SkeletalPriestess::MapKeySkeletalPriestess] = Stats(16, 8, 32);
	StatsTables::StatsTable[Undead::MapKeyUndead] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ghost::MapKeyGhost] = Stats(16, 8, 32);

	StatsTables::StatsTable[Grim::MapKeyGrim] = Stats(16, 8, 32);
	StatsTables::StatsTable[Amelia::MapKeyAmelia] = Stats(16, 8, 32);
	StatsTables::StatsTable[Azmus::MapKeyAzmus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Dudly::MapKeyDudly] = Stats(16, 8, 32);
	StatsTables::StatsTable[Garrick::MapKeyGarrick] = Stats(16, 8, 32);
	StatsTables::StatsTable[Johann::MapKeyJohann] = Stats(16, 8, 32);
	StatsTables::StatsTable[Necron::MapKeyNecron] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessNebea::MapKeyPrincessNebea] = Stats(16, 8, 32);
	StatsTables::StatsTable[Roger::MapKeyRoger] = Stats(16, 8, 32);
	StatsTables::StatsTable[Thion::MapKeyThion] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ursula::MapKeyUrsula] = Stats(16, 8, 32);
	StatsTables::StatsTable[Vesuvius::MapKeyVesuvius] = Stats(16, 8, 32);
	StatsTables::StatsTable[Viper::MapKeyViper] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zana::MapKeyZana] = Stats(16, 8, 32);
	StatsTables::StatsTable[Zelina::MapKeyZelina] = Stats(16, 8, 32);

	/***********
		VS
	************/
	
	StatsTables::StatsTable[Abomination::MapKeyAbomination] = Stats(16, 8, 32);
	StatsTables::StatsTable[Assassin::MapKeyAssassin] = Stats(16, 8, 32);
	StatsTables::StatsTable[BoneKnight::MapKeyBoneKnight] = Stats(16, 8, 32);
	StatsTables::StatsTable[DarkTiger::MapKeyDarkTiger] = Stats(16, 8, 32);
	StatsTables::StatsTable[EvilEye::MapKeyEvilEye] = Stats(16, 8, 32);
	StatsTables::StatsTable[Exterminator::MapKeyExterminator] = Stats(16, 8, 32);
	StatsTables::StatsTable[Gargoyle::MapKeyGargoyle] = Stats(16, 8, 32);
	StatsTables::StatsTable[Shade::MapKeyShade] = Stats(16, 8, 32);
	StatsTables::StatsTable[VoidArcher::MapKeyVoidArcher] = Stats(16, 8, 32);
	StatsTables::StatsTable[VoidDemon::MapKeyVoidDemon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Warlock::MapKeyWarlock] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Professor::MapKeyProfessor] = Stats(16, 8, 32);
	StatsTables::StatsTable[Robot::MapKeyRobot] = Stats(16, 8, 32);
	StatsTables::StatsTable[Atreus::MapKeyAtreus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Bancroft::MapKeyBancroft] = Stats(16, 8, 32);
	StatsTables::StatsTable[Godiva::MapKeyGodiva] = Stats(16, 8, 32);
	StatsTables::StatsTable[Illia::MapKeyIllia] = Stats(16, 8, 32);
	StatsTables::StatsTable[Leon::MapKeyLeon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Mara::MapKeyMara] = Stats(16, 8, 32);
	StatsTables::StatsTable[Marcel::MapKeyMarcel] = Stats(16, 8, 32);
	StatsTables::StatsTable[Piper::MapKeyPiper] = Stats(16, 8, 32);
	StatsTables::StatsTable[QueenElise::MapKeyQueenElise] = Stats(16, 8, 32);
	StatsTables::StatsTable[Radon::MapKeyRadon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ralston::MapKeyRalston] = Stats(16, 8, 32);
	StatsTables::StatsTable[Xenon::MapKeyXenon] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ysara::MapKeyYsara] = Stats(16, 8, 32);
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
			exp += std::get<0>(stats.increments[index]);	
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
