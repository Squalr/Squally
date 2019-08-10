#include "StatsTables.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntities.h"

#include "Resources/UIResources.h"

StatsTables* StatsTables::instance = nullptr;
const std::map<int, int> StatsTables::HealthGain =
{
	{ 1, 2 },
	{ 2, 2 },
	{ 3, 2 },
	{ 4, 2 },
	{ 5, 2 },
	{ 6, 3 },
	{ 7, 3 },
	{ 8, 3 },
	{ 9, 3 },
	{ 10, 3 },
	{ 11, 4 },
	{ 12, 4 },
	{ 13, 4 },
	{ 14, 4 },
	{ 15, 5 },
	{ 16, 5 },
	{ 17, 5 },
	{ 18, 5 },
	{ 19, 5 },
	{ 20, 5 }
};

const std::map<int, int> StatsTables::ManaGain =
{
	{ 1, 1 },
	{ 2, 1 },
	{ 3, 1 },
	{ 4, 1 },
	{ 5, 1 },
	{ 6, 1 },
	{ 7, 1 },
	{ 8, 1 },
	{ 9, 1 },
	{ 10, 1 },
	{ 11, 2 },
	{ 12, 2 },
	{ 13, 2 },
	{ 14, 2 },
	{ 15, 2 },
	{ 16, 2 },
	{ 17, 2 },
	{ 18, 2 },
	{ 19, 2 },
	{ 20, 2 }
};

const std::map<int, int> StatsTables::ExpRequired =
{
	{ 1, 64 },
	{ 2, 640 },
	{ 3, 1024 },
	{ 4, 1528 },
	{ 5, 2048 },
	{ 6, 3072 },
	{ 7, 3584 },
	{ 8, 4096 },
	{ 9, 4608 },
	{ 10, 5120 },
	{ 11, 5632 },
	{ 12, 6144 },
	{ 13, 6656 },
	{ 14, 7168 },
	{ 15, 7680 },
	{ 16, 8192 },
	{ 17, 8704 },
	{ 18, 9216 },
	{ 19, 9728 },
	{ 20, 10240 }
};

std::map<std::string, StatsTables::Stats> StatsTables::StatsTable = std::map<std::string, StatsTables::Stats>();

const int StatsTables::FallbackExp = 666;
const int StatsTables::FallbackMana = 666;
const int StatsTables::FallbackHealth = 666;

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
	StatsTables::StatsTable[Squally::MapKeySqually] = Stats(16, 8, 32);
	
	StatsTables::StatsTable[Cyrogen::MapKeyCyrogen] = Stats(16, 8, 32);
	StatsTables::StatsTable[FrostFiend::MapKeyFrostFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinElf::MapKeyGoblinElf] = Stats(16, 8, 32);
	StatsTables::StatsTable[IceGolem::MapKeyIceGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinGrunt::MapKeyPenguinGrunt] = Stats(16, 8, 32);
	StatsTables::StatsTable[PenguinWarrior::MapKeyPenguinWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[Santa::MapKeySanta] = Stats(16, 8, 32);
	StatsTables::StatsTable[SnowFiend::MapKeySnowFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[ToySoldierGoblin::MapKeyToySoldierGoblin] = Stats(16, 8, 32);
	StatsTables::StatsTable[Viking::MapKeyViking] = Stats(16, 8, 32);
	StatsTables::StatsTable[WaterElemental::MapKeyWaterElemental] = Stats(16, 8, 32);
	StatsTables::StatsTable[Yeti::MapKeyYeti] = Stats(16, 8, 32);
	StatsTables::StatsTable[Snowman::MapKeySnowman] = Stats(16, 8, 32);
	StatsTables::StatsTable[YetiBaby::MapKeyYetiBaby] = Stats(16, 8, 32);
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
	StatsTables::StatsTable[Krampus::MapKeyKrampus] = Stats(16, 8, 32);
	StatsTables::StatsTable[LavaGolem::MapKeyLavaGolem] = Stats(16, 8, 32);
	StatsTables::StatsTable[Apple::MapKeyApple] = Stats(16, 8, 32);
	StatsTables::StatsTable[CritterDemon::MapKeyCritterDemon] = Stats(16, 8, 32);
	StatsTables::StatsTable[FlyBot::MapKeyFlyBot] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ash::MapKeyAsh] = Stats(16, 8, 32);
	StatsTables::StatsTable[Brine::MapKeyBrine] = Stats(16, 8, 32);
	StatsTables::StatsTable[Celeste::MapKeyCeleste] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cindra::MapKeyCindra] = Stats(16, 8, 32);
	StatsTables::StatsTable[Drak::MapKeyDrak] = Stats(16, 8, 32);
	StatsTables::StatsTable[Igneus::MapKeyIgneus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Lucifer::MapKeyLucifer] = Stats(16, 8, 32);
	StatsTables::StatsTable[Magnus::MapKeyMagnus] = Stats(16, 8, 32);
	StatsTables::StatsTable[Pan::MapKeyPan] = Stats(16, 8, 32);
	StatsTables::StatsTable[PrincessMittens::MapKeyPrincessMittens] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ragnis::MapKeyRagnis] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rupert::MapKeyRupert] = Stats(16, 8, 32);
	StatsTables::StatsTable[Rusty::MapKeyRusty] = Stats(16, 8, 32);
	StatsTables::StatsTable[Scaldor::MapKeyScaldor] = Stats(16, 8, 32);
	StatsTables::StatsTable[Centaur::MapKeyCentaur] = Stats(16, 8, 32);
	StatsTables::StatsTable[Cyclops::MapKeyCyclops] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinGruntBoar::MapKeyGoblinGruntBoar] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinShaman::MapKeyGoblinShaman] = Stats(16, 8, 32);
	StatsTables::StatsTable[GoblinWarriorPig::MapKeyGoblinWarriorPig] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingGrogg::MapKeyKingGrogg] = Stats(16, 8, 32);
	StatsTables::StatsTable[Ogre::MapKeyOgre] = Stats(16, 8, 32);
	StatsTables::StatsTable[OrcBomber::MapKeyOrcBomber] = Stats(16, 8, 32);
	StatsTables::StatsTable[OrcGrunt::MapKeyOrcGrunt] = Stats(10, 8, 32);
	StatsTables::StatsTable[OrcSwordsman::MapKeyOrcSwordsman] = Stats(16, 8, 32);
	StatsTables::StatsTable[OrcWarrior::MapKeyOrcWarrior] = Stats(16, 8, 32);
	StatsTables::StatsTable[Troll::MapKeyTroll] = Stats(16, 8, 32);
	StatsTables::StatsTable[Goblin::MapKeyGoblin] = Stats(16, 8, 32);
	StatsTables::StatsTable[Turtle::MapKeyTurtle] = Stats(16, 8, 32);
	StatsTables::StatsTable[Appolo::MapKeyAppolo] = Stats(16, 8, 32);
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
	StatsTables::StatsTable[BoneFiend::MapKeyBoneFiend] = Stats(16, 8, 32);
	StatsTables::StatsTable[Hunter::MapKeyHunter] = Stats(16, 8, 32);
	StatsTables::StatsTable[KingZul::MapKeyKingZul] = Stats(16, 8, 32);
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

int StatsTables::getHealthGainAtLevel(int level)
{
	if (StatsTables::HealthGain.find(level) != StatsTables::HealthGain.end())
	{
		return StatsTables::HealthGain.at(level);
	}
	
	return 0;
}

int StatsTables::getHealthGainAtNewLevel(int newLevel)
{
	return StatsTables::getHealthGainAtLevel(newLevel - 1);
}

int StatsTables::getManaGainAtLevel(int level)
{
	if (StatsTables::ManaGain.find(level) != StatsTables::ManaGain.end())
	{
		return StatsTables::ManaGain.at(level);
	}
	
	return 0;
}

int StatsTables::getManaGainAtNewLevel(int newLevel)
{
	return StatsTables::getManaGainAtLevel(newLevel - 1);
}

int StatsTables::getExpRequiredAtLevel(int level)
{
	if (StatsTables::ExpRequired.find(level) != StatsTables::ExpRequired.end())
	{
		return StatsTables::ExpRequired.at(level);
	}
	
	return 0;
}

int StatsTables::getExpNeededUntilLevel(int currentLevel, int currentExp, int level)
{
	currentLevel = MathUtils::clamp(currentLevel, 0, currentLevel);
	level = MathUtils::clamp(level, 0, StatsTables::ExpRequired.size());

	if (currentLevel >= level)
	{
		return 0;
	}

	int expRequired = 0;

	while (currentLevel < level)
	{
		expRequired += StatsTables::getExpRequiredAtLevel(currentLevel++);
	}

	return expRequired;
}

int StatsTables::getKillExp(PlatformerEntity* platformerEntity)
{
	if (StatsTables::StatsTable.find(platformerEntity->getName()) != StatsTables::StatsTable.end())
	{
		return StatsTables::StatsTable[platformerEntity->getName()].exp;
	}

	return StatsTables::FallbackExp;
}

int StatsTables::getBaseMana(PlatformerEntity* platformerEntity)
{
	if (StatsTables::StatsTable.find(platformerEntity->getName()) != StatsTables::StatsTable.end())
	{
		return StatsTables::StatsTable[platformerEntity->getName()].mana;
	}

	return StatsTables::FallbackMana;
}

int StatsTables::getBaseHealth(PlatformerEntity* platformerEntity)
{
	if (StatsTables::StatsTable.find(platformerEntity->getName()) != StatsTables::StatsTable.end())
	{
		return StatsTables::StatsTable[platformerEntity->getName()].health;
	}

	return StatsTables::FallbackHealth;
}
