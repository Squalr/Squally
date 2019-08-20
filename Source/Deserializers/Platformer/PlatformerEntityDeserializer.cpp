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

	this->deserializers[Squally::MapKeySqually] = [=](ValueMap properties) { return (GameObject*)Squally::deserialize(properties); };
	
	this->deserializers[Cryogen::MapKeyCryogen] = [=](ValueMap properties) { return (GameObject*)Cryogen::deserialize(properties); };
	this->deserializers[FrostFiend::MapKeyFrostFiend] = [=](ValueMap properties) { return (GameObject*)FrostFiend::deserialize(properties); };
	this->deserializers[GoblinElf::MapKeyGoblinElf] = [=](ValueMap properties) { return (GameObject*)GoblinElf::deserialize(properties); };
	this->deserializers[IceGolem::MapKeyIceGolem] = [=](ValueMap properties) { return (GameObject*)IceGolem::deserialize(properties); };
	this->deserializers[PenguinGrunt::MapKeyPenguinGrunt] = [=](ValueMap properties) { return (GameObject*)PenguinGrunt::deserialize(properties); };
	this->deserializers[PenguinWarrior::MapKeyPenguinWarrior] = [=](ValueMap properties) { return (GameObject*)PenguinWarrior::deserialize(properties); };
	this->deserializers[Santa::MapKeySanta] = [=](ValueMap properties) { return (GameObject*)Santa::deserialize(properties); };
	this->deserializers[SnowFiend::MapKeySnowFiend] = [=](ValueMap properties) { return (GameObject*)SnowFiend::deserialize(properties); };
	this->deserializers[ToySoldierGoblin::MapKeyToySoldierGoblin] = [=](ValueMap properties) { return (GameObject*)ToySoldierGoblin::deserialize(properties); };
	this->deserializers[Viking::MapKeyViking] = [=](ValueMap properties) { return (GameObject*)Viking::deserialize(properties); };
	this->deserializers[WaterElemental::MapKeyWaterElemental] = [=](ValueMap properties) { return (GameObject*)WaterElemental::deserialize(properties); };
	this->deserializers[Yeti::MapKeyYeti] = [=](ValueMap properties) { return (GameObject*)Yeti::deserialize(properties); };
	this->deserializers[Snowman::MapKeySnowman] = [=](ValueMap properties) { return (GameObject*)Snowman::deserialize(properties); };
	this->deserializers[YetiBaby::MapKeyYetiBaby] = [=](ValueMap properties) { return (GameObject*)YetiBaby::deserialize(properties); };
	this->deserializers[Aspen::MapKeyAspen] = [=](ValueMap properties) { return (GameObject*)Aspen::deserialize(properties); };
	this->deserializers[Aster::MapKeyAster] = [=](ValueMap properties) { return (GameObject*)Aster::deserialize(properties); };
	this->deserializers[Bodom::MapKeyBodom] = [=](ValueMap properties) { return (GameObject*)Bodom::deserialize(properties); };
	this->deserializers[Cookie::MapKeyCookie] = [=](ValueMap properties) { return (GameObject*)Cookie::deserialize(properties); };
	this->deserializers[Cooper::MapKeyCooper] = [=](ValueMap properties) { return (GameObject*)Cooper::deserialize(properties); };
	this->deserializers[Irmik::MapKeyIrmik] = [=](ValueMap properties) { return (GameObject*)Irmik::deserialize(properties); };
	this->deserializers[Jingles::MapKeyJingles] = [=](ValueMap properties) { return (GameObject*)Jingles::deserialize(properties); };
	this->deserializers[Juniper::MapKeyJuniper] = [=](ValueMap properties) { return (GameObject*)Juniper::deserialize(properties); };
	this->deserializers[Kringle::MapKeyKringle] = [=](ValueMap properties) { return (GameObject*)Kringle::deserialize(properties); };
	this->deserializers[Nessie::MapKeyNessie] = [=](ValueMap properties) { return (GameObject*)Nessie::deserialize(properties); };
	this->deserializers[PrincessPepper::MapKeyPrincessPepper] = [=](ValueMap properties) { return (GameObject*)PrincessPepper::deserialize(properties); };
	this->deserializers[Thatcher::MapKeyThatcher] = [=](ValueMap properties) { return (GameObject*)Thatcher::deserialize(properties); };
	this->deserializers[Theldar::MapKeyTheldar] = [=](ValueMap properties) { return (GameObject*)Theldar::deserialize(properties); };
	this->deserializers[Tinsel::MapKeyTinsel] = [=](ValueMap properties) { return (GameObject*)Tinsel::deserialize(properties); };
	this->deserializers[Agnes::MapKeyAgnes] = [=](ValueMap properties) { return (GameObject*)Agnes::deserialize(properties); };
	this->deserializers[Jack::MapKeyJack] = [=](ValueMap properties) { return (GameObject*)Jack::deserialize(properties); };
	this->deserializers[Reaper::MapKeyReaper] = [=](ValueMap properties) { return (GameObject*)Reaper::deserialize(properties); };
	this->deserializers[Scarecrow::MapKeyScarecrow] = [=](ValueMap properties) { return (GameObject*)Scarecrow::deserialize(properties); };
	this->deserializers[SkeletalPirate::MapKeySkeletalPirate] = [=](ValueMap properties) { return (GameObject*)SkeletalPirate::deserialize(properties); };
	this->deserializers[Thug::MapKeyThug] = [=](ValueMap properties) { return (GameObject*)Thug::deserialize(properties); };
	this->deserializers[VampireLord::MapKeyVampireLord] = [=](ValueMap properties) { return (GameObject*)VampireLord::deserialize(properties); };
	this->deserializers[Vampiress::MapKeyVampiress] = [=](ValueMap properties) { return (GameObject*)Vampiress::deserialize(properties); };
	this->deserializers[Werewolf::MapKeyWerewolf] = [=](ValueMap properties) { return (GameObject*)Werewolf::deserialize(properties); };
	this->deserializers[Wraith::MapKeyWraith] = [=](ValueMap properties) { return (GameObject*)Wraith::deserialize(properties); };
	this->deserializers[Zombie::MapKeyZombie] = [=](ValueMap properties) { return (GameObject*)Zombie::deserialize(properties); };
	this->deserializers[ZombieElric::MapKeyZombieElric] = [=](ValueMap properties) { return (GameObject*)ZombieElric::deserialize(properties); };
	this->deserializers[Knight::MapKeyKnight] = [=](ValueMap properties) { return (GameObject*)Knight::deserialize(properties); };
	this->deserializers[Princess::MapKeyPrincess] = [=](ValueMap properties) { return (GameObject*)Princess::deserialize(properties); };
	this->deserializers[Elric::MapKeyElric] = [=](ValueMap properties) { return (GameObject*)Elric::deserialize(properties); };
	this->deserializers[Garin::MapKeyGarin] = [=](ValueMap properties) { return (GameObject*)Garin::deserialize(properties); };
	this->deserializers[Gaunt::MapKeyGaunt] = [=](ValueMap properties) { return (GameObject*)Gaunt::deserialize(properties); };
	this->deserializers[KingRedsong::MapKeyKingRedsong] = [=](ValueMap properties) { return (GameObject*)KingRedsong::deserialize(properties); };
	this->deserializers[KingRedsongSlime::MapKeyKingRedsongSlime] = [=](ValueMap properties) { return (GameObject*)KingRedsongSlime::deserialize(properties); };
	this->deserializers[Leopold::MapKeyLeopold] = [=](ValueMap properties) { return (GameObject*)Leopold::deserialize(properties); };
	this->deserializers[Leroy::MapKeyLeroy] = [=](ValueMap properties) { return (GameObject*)Leroy::deserialize(properties); };
	this->deserializers[Mabel::MapKeyMabel] = [=](ValueMap properties) { return (GameObject*)Mabel::deserialize(properties); };
	this->deserializers[Merlin::MapKeyMerlin] = [=](ValueMap properties) { return (GameObject*)Merlin::deserialize(properties); };
	this->deserializers[PrincessOpal::MapKeyPrincessOpal] = [=](ValueMap properties) { return (GameObject*)PrincessOpal::deserialize(properties); };
	this->deserializers[Raven::MapKeyRaven] = [=](ValueMap properties) { return (GameObject*)Raven::deserialize(properties); };
	this->deserializers[Rogas::MapKeyRogas] = [=](ValueMap properties) { return (GameObject*)Rogas::deserialize(properties); };
	this->deserializers[Thurstan::MapKeyThurstan] = [=](ValueMap properties) { return (GameObject*)Thurstan::deserialize(properties); };
	this->deserializers[Tyracius::MapKeyTyracius] = [=](ValueMap properties) { return (GameObject*)Tyracius::deserialize(properties); };
	this->deserializers[Asmodeus::MapKeyAsmodeus] = [=](ValueMap properties) { return (GameObject*)Asmodeus::deserialize(properties); };
	this->deserializers[DemonDragon::MapKeyDemonDragon] = [=](ValueMap properties) { return (GameObject*)DemonDragon::deserialize(properties); };
	this->deserializers[DemonGhost::MapKeyDemonGhost] = [=](ValueMap properties) { return (GameObject*)DemonGhost::deserialize(properties); };
	this->deserializers[DemonGrunt::MapKeyDemonGrunt] = [=](ValueMap properties) { return (GameObject*)DemonGrunt::deserialize(properties); };
	this->deserializers[DemonRogue::MapKeyDemonRogue] = [=](ValueMap properties) { return (GameObject*)DemonRogue::deserialize(properties); };
	this->deserializers[DemonShaman::MapKeyDemonShaman] = [=](ValueMap properties) { return (GameObject*)DemonShaman::deserialize(properties); };
	this->deserializers[DemonSwordsman::MapKeyDemonSwordsman] = [=](ValueMap properties) { return (GameObject*)DemonSwordsman::deserialize(properties); };
	this->deserializers[DemonWarrior::MapKeyDemonWarrior] = [=](ValueMap properties) { return (GameObject*)DemonWarrior::deserialize(properties); };
	this->deserializers[FireElemental::MapKeyFireElemental] = [=](ValueMap properties) { return (GameObject*)FireElemental::deserialize(properties); };
	this->deserializers[FireTiger::MapKeyFireTiger] = [=](ValueMap properties) { return (GameObject*)FireTiger::deserialize(properties); };
	this->deserializers[Krampus::MapKeyKrampus] = [=](ValueMap properties) { return (GameObject*)Krampus::deserialize(properties); };
	this->deserializers[LavaGolem::MapKeyLavaGolem] = [=](ValueMap properties) { return (GameObject*)LavaGolem::deserialize(properties); };
	this->deserializers[Apple::MapKeyApple] = [=](ValueMap properties) { return (GameObject*)Apple::deserialize(properties); };
	this->deserializers[CritterDemon::MapKeyCritterDemon] = [=](ValueMap properties) { return (GameObject*)CritterDemon::deserialize(properties); };
	this->deserializers[Scrappy::MapKeyScrappy] = [=](ValueMap properties) { return (GameObject*)Scrappy::deserialize(properties); };
	this->deserializers[Ash::MapKeyAsh] = [=](ValueMap properties) { return (GameObject*)Ash::deserialize(properties); };
	this->deserializers[Brine::MapKeyBrine] = [=](ValueMap properties) { return (GameObject*)Brine::deserialize(properties); };
	this->deserializers[Celeste::MapKeyCeleste] = [=](ValueMap properties) { return (GameObject*)Celeste::deserialize(properties); };
	this->deserializers[Cindra::MapKeyCindra] = [=](ValueMap properties) { return (GameObject*)Cindra::deserialize(properties); };
	this->deserializers[Drak::MapKeyDrak] = [=](ValueMap properties) { return (GameObject*)Drak::deserialize(properties); };
	this->deserializers[Igneus::MapKeyIgneus] = [=](ValueMap properties) { return (GameObject*)Igneus::deserialize(properties); };
	this->deserializers[Lucifer::MapKeyLucifer] = [=](ValueMap properties) { return (GameObject*)Lucifer::deserialize(properties); };
	this->deserializers[Magnus::MapKeyMagnus] = [=](ValueMap properties) { return (GameObject*)Magnus::deserialize(properties); };
	this->deserializers[Pan::MapKeyPan] = [=](ValueMap properties) { return (GameObject*)Pan::deserialize(properties); };
	this->deserializers[PrincessMittens::MapKeyPrincessMittens] = [=](ValueMap properties) { return (GameObject*)PrincessMittens::deserialize(properties); };
	this->deserializers[Ragnis::MapKeyRagnis] = [=](ValueMap properties) { return (GameObject*)Ragnis::deserialize(properties); };
	this->deserializers[Rupert::MapKeyRupert] = [=](ValueMap properties) { return (GameObject*)Rupert::deserialize(properties); };
	this->deserializers[Rusty::MapKeyRusty] = [=](ValueMap properties) { return (GameObject*)Rusty::deserialize(properties); };
	this->deserializers[Scaldor::MapKeyScaldor] = [=](ValueMap properties) { return (GameObject*)Scaldor::deserialize(properties); };
	this->deserializers[Centaur::MapKeyCentaur] = [=](ValueMap properties) { return (GameObject*)Centaur::deserialize(properties); };
	this->deserializers[Cyclops::MapKeyCyclops] = [=](ValueMap properties) { return (GameObject*)Cyclops::deserialize(properties); };
	this->deserializers[GoblinGruntBoar::MapKeyGoblinGruntBoar] = [=](ValueMap properties) { return (GameObject*)GoblinGruntBoar::deserialize(properties); };
	this->deserializers[GoblinShaman::MapKeyGoblinShaman] = [=](ValueMap properties) { return (GameObject*)GoblinShaman::deserialize(properties); };
	this->deserializers[GoblinWarriorPig::MapKeyGoblinWarriorPig] = [=](ValueMap properties) { return (GameObject*)GoblinWarriorPig::deserialize(properties); };
	this->deserializers[KingGrogg::MapKeyKingGrogg] = [=](ValueMap properties) { return (GameObject*)KingGrogg::deserialize(properties); };
	this->deserializers[Ogre::MapKeyOgre] = [=](ValueMap properties) { return (GameObject*)Ogre::deserialize(properties); };
	this->deserializers[OrcBomber::MapKeyOrcBomber] = [=](ValueMap properties) { return (GameObject*)OrcBomber::deserialize(properties); };
	this->deserializers[OrcGrunt::MapKeyOrcGrunt] = [=](ValueMap properties) { return (GameObject*)OrcGrunt::deserialize(properties); };
	this->deserializers[OrcSwordsman::MapKeyOrcSwordsman] = [=](ValueMap properties) { return (GameObject*)OrcSwordsman::deserialize(properties); };
	this->deserializers[OrcWarrior::MapKeyOrcWarrior] = [=](ValueMap properties) { return (GameObject*)OrcWarrior::deserialize(properties); };
	this->deserializers[Troll::MapKeyTroll] = [=](ValueMap properties) { return (GameObject*)Troll::deserialize(properties); };
	this->deserializers[Goblin::MapKeyGoblin] = [=](ValueMap properties) { return (GameObject*)Goblin::deserialize(properties); };
	this->deserializers[Turtle::MapKeyTurtle] = [=](ValueMap properties) { return (GameObject*)Turtle::deserialize(properties); };
	this->deserializers[Appolo::MapKeyAppolo] = [=](ValueMap properties) { return (GameObject*)Appolo::deserialize(properties); };
	this->deserializers[Ara::MapKeyAra] = [=](ValueMap properties) { return (GameObject*)Ara::deserialize(properties); };
	this->deserializers[Bard::MapKeyBard] = [=](ValueMap properties) { return (GameObject*)Bard::deserialize(properties); };
	this->deserializers[Blackbeard::MapKeyBlackbeard] = [=](ValueMap properties) { return (GameObject*)Blackbeard::deserialize(properties); };
	this->deserializers[Chiron::MapKeyChiron] = [=](ValueMap properties) { return (GameObject*)Chiron::deserialize(properties); };
	this->deserializers[Elriel::MapKeyElriel] = [=](ValueMap properties) { return (GameObject*)Elriel::deserialize(properties); };
	this->deserializers[Gramps::MapKeyGramps] = [=](ValueMap properties) { return (GameObject*)Gramps::deserialize(properties); };
	this->deserializers[QueenLiana::MapKeyQueenLiana] = [=](ValueMap properties) { return (GameObject*)QueenLiana::deserialize(properties); };
	this->deserializers[Lycan::MapKeyLycan] = [=](ValueMap properties) { return (GameObject*)Lycan::deserialize(properties); };
	this->deserializers[Minos::MapKeyMinos] = [=](ValueMap properties) { return (GameObject*)Minos::deserialize(properties); };
	this->deserializers[Polyphemus::MapKeyPolyphemus] = [=](ValueMap properties) { return (GameObject*)Polyphemus::deserialize(properties); };
	this->deserializers[Matu::MapKeyMatu] = [=](ValueMap properties) { return (GameObject*)Matu::deserialize(properties); };
	this->deserializers[Robin::MapKeyRobin] = [=](ValueMap properties) { return (GameObject*)Robin::deserialize(properties); };
	this->deserializers[Toben::MapKeyToben] = [=](ValueMap properties) { return (GameObject*)Toben::deserialize(properties); };
	this->deserializers[BoneFiend::MapKeyBoneFiend] = [=](ValueMap properties) { return (GameObject*)BoneFiend::deserialize(properties); };
	this->deserializers[Hunter::MapKeyHunter] = [=](ValueMap properties) { return (GameObject*)Hunter::deserialize(properties); };
	this->deserializers[KingZul::MapKeyKingZul] = [=](ValueMap properties) { return (GameObject*)KingZul::deserialize(properties); };
	this->deserializers[Mystic::MapKeyMystic] = [=](ValueMap properties) { return (GameObject*)Mystic::deserialize(properties); };
	this->deserializers[ReanimatedFighter::MapKeyReanimatedFighter] = [=](ValueMap properties) { return (GameObject*)ReanimatedFighter::deserialize(properties); };
	this->deserializers[ReanimatedPig::MapKeyReanimatedPig] = [=](ValueMap properties) { return (GameObject*)ReanimatedPig::deserialize(properties); };
	this->deserializers[SkeletalBaron::MapKeySkeletalBaron] = [=](ValueMap properties) { return (GameObject*)SkeletalBaron::deserialize(properties); };
	this->deserializers[SkeletalCleaver::MapKeySkeletalCleaver] = [=](ValueMap properties) { return (GameObject*)SkeletalCleaver::deserialize(properties); };
	this->deserializers[SkeletalKnight::MapKeySkeletalKnight] = [=](ValueMap properties) { return (GameObject*)SkeletalKnight::deserialize(properties); };
	this->deserializers[SkeletalPriestess::MapKeySkeletalPriestess] = [=](ValueMap properties) { return (GameObject*)SkeletalPriestess::deserialize(properties); };
	this->deserializers[Undead::MapKeyUndead] = [=](ValueMap properties) { return (GameObject*)Undead::deserialize(properties); };
	this->deserializers[Ghost::MapKeyGhost] = [=](ValueMap properties) { return (GameObject*)Ghost::deserialize(properties); };
	this->deserializers[Grim::MapKeyGrim] = [=](ValueMap properties) { return (GameObject*)Grim::deserialize(properties); };
	this->deserializers[Amelia::MapKeyAmelia] = [=](ValueMap properties) { return (GameObject*)Amelia::deserialize(properties); };
	this->deserializers[Azmus::MapKeyAzmus] = [=](ValueMap properties) { return (GameObject*)Azmus::deserialize(properties); };
	this->deserializers[Dudly::MapKeyDudly] = [=](ValueMap properties) { return (GameObject*)Dudly::deserialize(properties); };
	this->deserializers[Garrick::MapKeyGarrick] = [=](ValueMap properties) { return (GameObject*)Garrick::deserialize(properties); };
	this->deserializers[Johann::MapKeyJohann] = [=](ValueMap properties) { return (GameObject*)Johann::deserialize(properties); };
	this->deserializers[Necron::MapKeyNecron] = [=](ValueMap properties) { return (GameObject*)Necron::deserialize(properties); };
	this->deserializers[PrincessNebea::MapKeyPrincessNebea] = [=](ValueMap properties) { return (GameObject*)PrincessNebea::deserialize(properties); };
	this->deserializers[Roger::MapKeyRoger] = [=](ValueMap properties) { return (GameObject*)Roger::deserialize(properties); };
	this->deserializers[Thion::MapKeyThion] = [=](ValueMap properties) { return (GameObject*)Thion::deserialize(properties); };
	this->deserializers[Ursula::MapKeyUrsula] = [=](ValueMap properties) { return (GameObject*)Ursula::deserialize(properties); };
	this->deserializers[Vesuvius::MapKeyVesuvius] = [=](ValueMap properties) { return (GameObject*)Vesuvius::deserialize(properties); };
	this->deserializers[Viper::MapKeyViper] = [=](ValueMap properties) { return (GameObject*)Viper::deserialize(properties); };
	this->deserializers[Zana::MapKeyZana] = [=](ValueMap properties) { return (GameObject*)Zana::deserialize(properties); };
	this->deserializers[Zelina::MapKeyZelina] = [=](ValueMap properties) { return (GameObject*)Zelina::deserialize(properties); };
	this->deserializers[Barbarian::MapKeyBarbarian] = [=](ValueMap properties) { return (GameObject*)Barbarian::deserialize(properties); };
	this->deserializers[EarthElemental::MapKeyEarthElemental] = [=](ValueMap properties) { return (GameObject*)EarthElemental::deserialize(properties); };
	this->deserializers[EarthGolem::MapKeyEarthGolem] = [=](ValueMap properties) { return (GameObject*)EarthGolem::deserialize(properties); };
	this->deserializers[ForestGolem::MapKeyForestGolem] = [=](ValueMap properties) { return (GameObject*)ForestGolem::deserialize(properties); };
	this->deserializers[Gorilla::MapKeyGorilla] = [=](ValueMap properties) { return (GameObject*)Gorilla::deserialize(properties); };
	this->deserializers[LightningGolem::MapKeyLightningGolem] = [=](ValueMap properties) { return (GameObject*)LightningGolem::deserialize(properties); };
	this->deserializers[Rhinoman::MapKeyRhinoman] = [=](ValueMap properties) { return (GameObject*)Rhinoman::deserialize(properties); };
	this->deserializers[Shaman::MapKeyShaman] = [=](ValueMap properties) { return (GameObject*)Shaman::deserialize(properties); };
	this->deserializers[SkeletalArcher::MapKeySkeletalArcher] = [=](ValueMap properties) { return (GameObject*)SkeletalArcher::deserialize(properties); };
	this->deserializers[SkeletalNecromancer::MapKeySkeletalNecromancer] = [=](ValueMap properties) { return (GameObject*)SkeletalNecromancer::deserialize(properties); };
	this->deserializers[SkeletalWarrior::MapKeySkeletalWarrior] = [=](ValueMap properties) { return (GameObject*)SkeletalWarrior::deserialize(properties); };
	this->deserializers[TikiGolem::MapKeyTikiGolem] = [=](ValueMap properties) { return (GameObject*)TikiGolem::deserialize(properties); };
	this->deserializers[Gecko::MapKeyGecko] = [=](ValueMap properties) { return (GameObject*)Gecko::deserialize(properties); };
	this->deserializers[Alder::MapKeyAlder] = [=](ValueMap properties) { return (GameObject*)Alder::deserialize(properties); };
	this->deserializers[Bonnie::MapKeyBonnie] = [=](ValueMap properties) { return (GameObject*)Bonnie::deserialize(properties); };
	this->deserializers[Brock::MapKeyBrock] = [=](ValueMap properties) { return (GameObject*)Brock::deserialize(properties); };
	this->deserializers[Burch::MapKeyBurch] = [=](ValueMap properties) { return (GameObject*)Burch::deserialize(properties); };
	this->deserializers[Cypress::MapKeyCypress] = [=](ValueMap properties) { return (GameObject*)Cypress::deserialize(properties); };
	this->deserializers[Finch::MapKeyFinch] = [=](ValueMap properties) { return (GameObject*)Finch::deserialize(properties); };
	this->deserializers[Fraya::MapKeyFraya] = [=](ValueMap properties) { return (GameObject*)Fraya::deserialize(properties); };
	this->deserializers[Jasper::MapKeyJasper] = [=](ValueMap properties) { return (GameObject*)Jasper::deserialize(properties); };
	this->deserializers[Mildred::MapKeyMildred] = [=](ValueMap properties) { return (GameObject*)Mildred::deserialize(properties); };
	this->deserializers[Olive::MapKeyOlive] = [=](ValueMap properties) { return (GameObject*)Olive::deserialize(properties); };
	this->deserializers[PrincessDawn::MapKeyPrincessDawn] = [=](ValueMap properties) { return (GameObject*)PrincessDawn::deserialize(properties); };
	this->deserializers[Raka::MapKeyRaka] = [=](ValueMap properties) { return (GameObject*)Raka::deserialize(properties); };
	this->deserializers[Sarude::MapKeySarude] = [=](ValueMap properties) { return (GameObject*)Sarude::deserialize(properties); };
	this->deserializers[Shen::MapKeyShen] = [=](ValueMap properties) { return (GameObject*)Shen::deserialize(properties); };
	this->deserializers[AnubisPup::MapKeyAnubisPup] = [=](ValueMap properties) { return (GameObject*)AnubisPup::deserialize(properties); };
	this->deserializers[AnubisWarrior::MapKeyAnubisWarrior] = [=](ValueMap properties) { return (GameObject*)AnubisWarrior::deserialize(properties); };
	this->deserializers[LionMan::MapKeyLionMan] = [=](ValueMap properties) { return (GameObject*)LionMan::deserialize(properties); };
	this->deserializers[Lioness::MapKeyLioness] = [=](ValueMap properties) { return (GameObject*)Lioness::deserialize(properties); };
	this->deserializers[Medusa::MapKeyMedusa] = [=](ValueMap properties) { return (GameObject*)Medusa::deserialize(properties); };
	this->deserializers[Mermaid::MapKeyMermaid] = [=](ValueMap properties) { return (GameObject*)Mermaid::deserialize(properties); };
	this->deserializers[Minotaur::MapKeyMinotaur] = [=](ValueMap properties) { return (GameObject*)Minotaur::deserialize(properties); };
	this->deserializers[MummyPriest::MapKeyMummyPriest] = [=](ValueMap properties) { return (GameObject*)MummyPriest::deserialize(properties); };
	this->deserializers[MummyWarrior::MapKeyMummyWarrior] = [=](ValueMap properties) { return (GameObject*)MummyWarrior::deserialize(properties); };
	this->deserializers[Osiris::MapKeyOsiris] = [=](ValueMap properties) { return (GameObject*)Osiris::deserialize(properties); };
	this->deserializers[TigerMan::MapKeyTigerMan] = [=](ValueMap properties) { return (GameObject*)TigerMan::deserialize(properties); };
	this->deserializers[Tigress::MapKeyTigress] = [=](ValueMap properties) { return (GameObject*)Tigress::deserialize(properties); };
	this->deserializers[Mummy::MapKeyMummy] = [=](ValueMap properties) { return (GameObject*)Mummy::deserialize(properties); };
	this->deserializers[Ajax::MapKeyAjax] = [=](ValueMap properties) { return (GameObject*)Ajax::deserialize(properties); };
	this->deserializers[Angel::MapKeyAngel] = [=](ValueMap properties) { return (GameObject*)Angel::deserialize(properties); };
	this->deserializers[Aphrodite::MapKeyAphrodite] = [=](ValueMap properties) { return (GameObject*)Aphrodite::deserialize(properties); };
	this->deserializers[Ares::MapKeyAres] = [=](ValueMap properties) { return (GameObject*)Ares::deserialize(properties); };
	this->deserializers[Athena::MapKeyAthena] = [=](ValueMap properties) { return (GameObject*)Athena::deserialize(properties); };
	this->deserializers[Cleopatra::MapKeyCleopatra] = [=](ValueMap properties) { return (GameObject*)Cleopatra::deserialize(properties); };
	this->deserializers[Geryon::MapKeyGeryon] = [=](ValueMap properties) { return (GameObject*)Geryon::deserialize(properties); };
	this->deserializers[Griffin::MapKeyGriffin] = [=](ValueMap properties) { return (GameObject*)Griffin::deserialize(properties); };
	this->deserializers[Hades::MapKeyHades] = [=](ValueMap properties) { return (GameObject*)Hades::deserialize(properties); };
	this->deserializers[Hera::MapKeyHera] = [=](ValueMap properties) { return (GameObject*)Hera::deserialize(properties); };
	this->deserializers[Horus::MapKeyHorus] = [=](ValueMap properties) { return (GameObject*)Horus::deserialize(properties); };
	this->deserializers[Poseidon::MapKeyPoseidon] = [=](ValueMap properties) { return (GameObject*)Poseidon::deserialize(properties); };
	this->deserializers[Thor::MapKeyThor] = [=](ValueMap properties) { return (GameObject*)Thor::deserialize(properties); };
	this->deserializers[Zeus::MapKeyZeus] = [=](ValueMap properties) { return (GameObject*)Zeus::deserialize(properties); };
	this->deserializers[Abomination::MapKeyAbomination] = [=](ValueMap properties) { return (GameObject*)Abomination::deserialize(properties); };
	this->deserializers[Assassin::MapKeyAssassin] = [=](ValueMap properties) { return (GameObject*)Assassin::deserialize(properties); };
	this->deserializers[BoneKnight::MapKeyBoneKnight] = [=](ValueMap properties) { return (GameObject*)BoneKnight::deserialize(properties); };
	this->deserializers[DarkTiger::MapKeyDarkTiger] = [=](ValueMap properties) { return (GameObject*)DarkTiger::deserialize(properties); };
	this->deserializers[EvilEye::MapKeyEvilEye] = [=](ValueMap properties) { return (GameObject*)EvilEye::deserialize(properties); };
	this->deserializers[Exterminator::MapKeyExterminator] = [=](ValueMap properties) { return (GameObject*)Exterminator::deserialize(properties); };
	this->deserializers[Gargoyle::MapKeyGargoyle] = [=](ValueMap properties) { return (GameObject*)Gargoyle::deserialize(properties); };
	this->deserializers[Shade::MapKeyShade] = [=](ValueMap properties) { return (GameObject*)Shade::deserialize(properties); };
	this->deserializers[VoidArcher::MapKeyVoidArcher] = [=](ValueMap properties) { return (GameObject*)VoidArcher::deserialize(properties); };
	this->deserializers[VoidDemon::MapKeyVoidDemon] = [=](ValueMap properties) { return (GameObject*)VoidDemon::deserialize(properties); };
	this->deserializers[Warlock::MapKeyWarlock] = [=](ValueMap properties) { return (GameObject*)Warlock::deserialize(properties); };
	this->deserializers[Professor::MapKeyProfessor] = [=](ValueMap properties) { return (GameObject*)Professor::deserialize(properties); };
	this->deserializers[Robot::MapKeyRobot] = [=](ValueMap properties) { return (GameObject*)Robot::deserialize(properties); };
	this->deserializers[Atreus::MapKeyAtreus] = [=](ValueMap properties) { return (GameObject*)Atreus::deserialize(properties); };
	this->deserializers[Bancroft::MapKeyBancroft] = [=](ValueMap properties) { return (GameObject*)Bancroft::deserialize(properties); };
	this->deserializers[Godiva::MapKeyGodiva] = [=](ValueMap properties) { return (GameObject*)Godiva::deserialize(properties); };
	this->deserializers[Illia::MapKeyIllia] = [=](ValueMap properties) { return (GameObject*)Illia::deserialize(properties); };
	this->deserializers[Leon::MapKeyLeon] = [=](ValueMap properties) { return (GameObject*)Leon::deserialize(properties); };
	this->deserializers[Mara::MapKeyMara] = [=](ValueMap properties) { return (GameObject*)Mara::deserialize(properties); };
	this->deserializers[Marcel::MapKeyMarcel] = [=](ValueMap properties) { return (GameObject*)Marcel::deserialize(properties); };
	this->deserializers[Piper::MapKeyPiper] = [=](ValueMap properties) { return (GameObject*)Piper::deserialize(properties); };
	this->deserializers[QueenElise::MapKeyQueenElise] = [=](ValueMap properties) { return (GameObject*)QueenElise::deserialize(properties); };
	this->deserializers[Radon::MapKeyRadon] = [=](ValueMap properties) { return (GameObject*)Radon::deserialize(properties); };
	this->deserializers[Ralston::MapKeyRalston] = [=](ValueMap properties) { return (GameObject*)Ralston::deserialize(properties); };
	this->deserializers[Xenon::MapKeyXenon] = [=](ValueMap properties) { return (GameObject*)Xenon::deserialize(properties); };
	this->deserializers[Ysara::MapKeyYsara] = [=](ValueMap properties) { return (GameObject*)Ysara::deserialize(properties); };
}

PlatformerEntityDeserializer::~PlatformerEntityDeserializer()
{
}
