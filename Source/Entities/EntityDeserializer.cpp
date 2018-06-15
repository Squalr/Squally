#include "EntityDeserializer.h"

const std::string EntityDeserializer::KeyTypeEntity = "entity";

const std::string EntityDeserializer::KeySpawnProperty = "spawn";

const std::string EntityDeserializer::KeyNpcKnight = "knight";

const std::string EntityDeserializer::KeyEnemyBossRhinoman = "boss_rhinoman";
const std::string EntityDeserializer::KeyEnemyGoblinGrunt = "goblin_grunt";
const std::string EntityDeserializer::KeyEnemyGoblinSwordsman = "goblin_swordsman";
const std::string EntityDeserializer::KeyEnemyGoblinWarrior = "goblin_warrior";
const std::string EntityDeserializer::KeyEnemyJungleDragon = "jungle_dragon";
const std::string EntityDeserializer::KeyEnemyMantis = "mantis";
const std::string EntityDeserializer::KeyEnemyMinotaur = "minotaur";
const std::string EntityDeserializer::KeyEnemyPigDemon = "pig_demon";
const std::string EntityDeserializer::KeyEnemyPurpleDinosaur = "purple_dinosaur";
const std::string EntityDeserializer::KeyEnemyTikiGolem = "tiki_golem";
const std::string EntityDeserializer::KeyEnemyTikiWarrior = "tiki_warrior";

const std::string EntityDeserializer::KeyEnemyBossEgyptianGoddess = "boss_egyptian_goddess";
const std::string EntityDeserializer::KeyEnemyAnubisTiny = "anubis_tiny";
const std::string EntityDeserializer::KeyEnemyAnubisWarrior = "anubis_warrior";
const std::string EntityDeserializer::KeyEnemyLioness = "lioness";
const std::string EntityDeserializer::KeyEnemyLionMan = "lion_man";
const std::string EntityDeserializer::KeyEnemyMedusa = "medusa";
const std::string EntityDeserializer::KeyEnemyMedusaSmall = "medusa_small";
const std::string EntityDeserializer::KeyEnemyMermaid = "mermaid";
const std::string EntityDeserializer::KeyEnemyMummyPharaoh = "mummy_pharaoh";
const std::string EntityDeserializer::KeyEnemyTigerMan = "tiger_man";
const std::string EntityDeserializer::KeyEnemyTigress = "tigress";

const std::string EntityDeserializer::KeyEnemyBossDragonOrcKing = "boss_dragon_orc_king";
const std::string EntityDeserializer::KeyEnemyCyclops = "cyclops";
const std::string EntityDeserializer::KeyEnemyEnt = "ent";
const std::string EntityDeserializer::KeyEnemyEntMage = "ent_mage";
const std::string EntityDeserializer::KeyEnemyGoblinGruntBoar = "goblin_grunt_boar";
const std::string EntityDeserializer::KeyEnemyGoblinGuard = "goblin_guard";
const std::string EntityDeserializer::KeyEnemyGoblinShaman = "goblin_shaman";
const std::string EntityDeserializer::KeyEnemyGoblinWarriorPig = "goblin_warrior_pig";
const std::string EntityDeserializer::KeyEnemyOrcGrunt = "orc_grunt";
const std::string EntityDeserializer::KeyEnemyOrcWarrior = "orc_warrior";
const std::string EntityDeserializer::KeyEnemyTroll = "troll";

const std::string EntityDeserializer::KeyEnemyBossKrampus = "boss_krampus";
const std::string EntityDeserializer::KeyEnemyBlackWidow = "black_widow";
const std::string EntityDeserializer::KeyEnemyEarthElemental = "earth_elemental";
const std::string EntityDeserializer::KeyEnemyEarthGolem = "earth_golem";
const std::string EntityDeserializer::KeyEnemyForestGolem = "forest_golem";
const std::string EntityDeserializer::KeyEnemyGenie = "genie";
const std::string EntityDeserializer::KeyEnemyRockGolem = "rock_golem";
const std::string EntityDeserializer::KeyEnemyShaman = "shaman";
const std::string EntityDeserializer::KeyEnemySkeletonArcher = "skeleton_archer";
const std::string EntityDeserializer::KeyEnemySkeletonNecromancer = "skeleton_necromancer";
const std::string EntityDeserializer::KeyEnemySkeletonWarrior = "skeleton_warrior";

const std::string EntityDeserializer::KeyEnemyBossWitch = "boss_witch";
const std::string EntityDeserializer::KeyEnemyExecutioner = "executioner";
const std::string EntityDeserializer::KeyEnemyGhost = "ghost";
const std::string EntityDeserializer::KeyEnemyGuard = "guard";
const std::string EntityDeserializer::KeyEnemyHarpy = "harpy";
const std::string EntityDeserializer::KeyEnemyJack = "jack";
const std::string EntityDeserializer::KeyEnemyReaper = "reaper";
const std::string EntityDeserializer::KeyEnemySkeletonMage = "skeleton_mage";
const std::string EntityDeserializer::KeyEnemyVampireLord = "vampire_lord";
const std::string EntityDeserializer::KeyEnemyVampiress = "vampiress";
const std::string EntityDeserializer::KeyEnemyZombie = "zombie";

const std::string EntityDeserializer::KeyEnemyBossIceGolem = "boss_ice_golem";
const std::string EntityDeserializer::KeyEnemyBossSanta = "boss_santa";
const std::string EntityDeserializer::KeyEnemyEvilSnowman = "evil_snowman";
const std::string EntityDeserializer::KeyEnemyFrostDragon = "frost_dragon";
const std::string EntityDeserializer::KeyEnemyFrostShooter = "frost_shooter";
const std::string EntityDeserializer::KeyEnemyGoblinElf = "goblin_elf";
const std::string EntityDeserializer::KeyEnemyIceGolem = "ice_golem";
const std::string EntityDeserializer::KeyEnemyTinyIceGolem = "tiny_ice_golem";
const std::string EntityDeserializer::KeyEnemyToySoldierGoblin = "toy_soldier_goblin";
const std::string EntityDeserializer::KeyEnemyWaterElemental = "water_elemental";
const std::string EntityDeserializer::KeyEnemyYeti = "yeti";
const std::string EntityDeserializer::KeyEnemyYetiWarrior = "yeti_warrior";

const std::string EntityDeserializer::KeyEnemyBossDemonKing = "boss_demon_king";
const std::string EntityDeserializer::KeyEnemyCritterDemon = "critter_demon";
const std::string EntityDeserializer::KeyEnemyDemonDragon = "demon_dragon";
const std::string EntityDeserializer::KeyEnemyDemonGhost = "demon_ghost";
const std::string EntityDeserializer::KeyEnemyDemonGrunt = "demon_grunt";
const std::string EntityDeserializer::KeyEnemyDemonRogue = "demon_rogue";
const std::string EntityDeserializer::KeyEnemyDemonShaman = "demon_shaman";
const std::string EntityDeserializer::KeyEnemyDemonSwordsman = "demon_swordsman";
const std::string EntityDeserializer::KeyEnemyDemonWarrior = "demon_warrior";
const std::string EntityDeserializer::KeyEnemyFireElemental = "fire_elemental";
const std::string EntityDeserializer::KeyEnemyLavaGolem = "lava_golem";

const std::string EntityDeserializer::KeyEnemyBossSkeletonKing = "boss_skeleton_king";
const std::string EntityDeserializer::KeyEnemyAbomination = "abomination";
const std::string EntityDeserializer::KeyEnemyBatDemon = "bat_demon";
const std::string EntityDeserializer::KeyEnemyDarkDragon = "dark_dragon";
const std::string EntityDeserializer::KeyEnemyDemonArcher = "demon_archer";
const std::string EntityDeserializer::KeyEnemySkeletonBaron = "skeleton_baron";
const std::string EntityDeserializer::KeyEnemySkeletonCleaver = "skeleton_cleaver";
const std::string EntityDeserializer::KeyEnemySkeletonKnight = "skeleton_knight";
const std::string EntityDeserializer::KeyEnemySkeletonPriestess = "skeleton_priestess";
const std::string EntityDeserializer::KeyEnemyUndead = "undead";
const std::string EntityDeserializer::KeyEnemyVoidDemon = "void_demon";

const std::string EntityDeserializer::KeyEnemyBossEvilEye = "boss_evil_eye";
const std::string EntityDeserializer::KeyEnemyExterminator = "exterminator";
const std::string EntityDeserializer::KeyEnemyMechBoxDrone = "mech_box_drone";
const std::string EntityDeserializer::KeyEnemyMechDog = "mech_dog";
const std::string EntityDeserializer::KeyEnemyMechGolem = "mech_golem";
const std::string EntityDeserializer::KeyEnemyMechGolemDark = "mech_golem_dark";
const std::string EntityDeserializer::KeyEnemyMechGuard = "mech_guard";
const std::string EntityDeserializer::KeyEnemyMiteBot = "mite_bot";
const std::string EntityDeserializer::KeyEnemyRobot = "robot";
const std::string EntityDeserializer::KeyEnemyVikingBot = "viking_bot";
const std::string EntityDeserializer::KeyEnemyVikingBotSmall = "viking_bot_small";

EntityDeserializer::EntityDeserializer()
{
}

EntityDeserializer::~EntityDeserializer()
{
}

void EntityDeserializer::onDeserializationRequest(DeserializationRequestArgs* args)
{
	if (args->typeName == EntityDeserializer::KeyTypeEntity)
	{
		ValueMap entity = args->valueMap;
		string name = entity.at(SerializableObject::KeyName).asString();
		HackableObject* newEntity = nullptr;

		if (name == EntityDeserializer::KeySpawnProperty)
		{
			newEntity = Player::create();
		}
		else if (name == EntityDeserializer::KeyNpcKnight)
		{
			newEntity = Knight::create();
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossRhinoman)
		{
			newEntity = BossRhinoman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinGrunt)
		{
			newEntity = GoblinGrunt::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinSwordsman)
		{
			newEntity = GoblinSwordsman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinWarrior)
		{
			newEntity = GoblinWarrior::create();
		}
		else if (name == EntityDeserializer::KeyEnemyJungleDragon)
		{
			newEntity = JungleDragon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMantis)
		{
			newEntity = Mantis::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMinotaur)
		{
			newEntity = Minotaur::create();
		}
		else if (name == EntityDeserializer::KeyEnemyPigDemon)
		{
			newEntity = PigDemon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyPurpleDinosaur)
		{
			newEntity = PurpleDinosaur::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTikiGolem)
		{
			newEntity = TikiGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTikiWarrior)
		{
			newEntity = TikiWarrior::create();
		}
		//////////////////
		// RUINS
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossEgyptianGoddess)
		{
			newEntity = BossEgyptianGoddess::create();
		}
		else if (name == EntityDeserializer::KeyEnemyAnubisTiny)
		{
			newEntity = AnubisTiny::create();
		}
		else if (name == EntityDeserializer::KeyEnemyAnubisWarrior)
		{
			newEntity = AnubisWarrior::create();
		}
		else if (name == EntityDeserializer::KeyEnemyLioness)
		{
			newEntity = Lioness::create();
		}
		else if (name == EntityDeserializer::KeyEnemyLionMan)
		{
			newEntity = LionMan::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMedusa)
		{
			newEntity = Medusa::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMedusaSmall)
		{
			newEntity = MedusaSmall::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMermaid)
		{
			newEntity = Mermaid::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMummyPharaoh)
		{
			newEntity = MummyPharaoh::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTigerMan)
		{
			newEntity = TigerMan::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTigress)
		{
			newEntity = Tigress::create();
		}
		//////////////////
		// FOREST
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossDragonOrcKing)
		{
			newEntity = BossDragonOrcKing::create();
		}
		else if (name == EntityDeserializer::KeyEnemyCyclops)
		{
			newEntity = Cyclops::create();
		}
		else if (name == EntityDeserializer::KeyEnemyEnt)
		{
			newEntity = Ent::create();
		}
		else if (name == EntityDeserializer::KeyEnemyEntMage)
		{
			newEntity = EntMage::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinGruntBoar)
		{
			newEntity = GoblinGruntBoar::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinGuard)
		{
			newEntity = GoblinGuard::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinShaman)
		{
			newEntity = GoblinShaman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinWarriorPig)
		{
			newEntity = GoblinWarriorPig::create();
		}
		else if (name == EntityDeserializer::KeyEnemyOrcGrunt)
		{
			newEntity = OrcGrunt::create();
		}
		else if (name == EntityDeserializer::KeyEnemyOrcWarrior)
		{
			newEntity = OrcWarrior::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTroll)
		{
			newEntity = Troll::create();
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossKrampus)
		{
			newEntity = BossKrampus::create();
		}
		else if (name == EntityDeserializer::KeyEnemyBlackWidow)
		{
			newEntity = BlackWidow::create();
		}
		else if (name == EntityDeserializer::KeyEnemyEarthElemental)
		{
			newEntity = EarthElemental::create();
		}
		else if (name == EntityDeserializer::KeyEnemyEarthGolem)
		{
			newEntity = EarthGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyForestGolem)
		{
			newEntity = ForestGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGenie)
		{
			newEntity = Genie::create();
		}
		else if (name == EntityDeserializer::KeyEnemyRockGolem)
		{
			newEntity = RockGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyShaman)
		{
			newEntity = Shaman::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonArcher)
		{
			newEntity = SkeletonArcher::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonNecromancer)
		{
			newEntity = SkeletonNecromancer::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonWarrior)
		{
			newEntity = SkeletonWarrior::create();
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossWitch)
		{
			newEntity = BossWitch::create();
		}
		else if (name == EntityDeserializer::KeyEnemyExecutioner)
		{
			newEntity = Executioner::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGhost)
		{
			newEntity = Ghost::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGuard)
		{
			newEntity = Guard::create();
		}
		else if (name == EntityDeserializer::KeyEnemyHarpy)
		{
			newEntity = Harpy::create();
		}
		else if (name == EntityDeserializer::KeyEnemyJack)
		{
			newEntity = Jack::create();
		}
		else if (name == EntityDeserializer::KeyEnemyReaper)
		{
			newEntity = Reaper::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonMage)
		{
			newEntity = SkeletonMage::create();
		}
		else if (name == EntityDeserializer::KeyEnemyVampireLord)
		{
			newEntity = VampireLord::create();
		}
		else if (name == EntityDeserializer::KeyEnemyVampiress)
		{
			newEntity = Vampiress::create();
		}
		else if (name == EntityDeserializer::KeyEnemyZombie)
		{
			newEntity = Zombie::create();
		}
		//////////////////
		// SNOW
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossIceGolem)
		{
			newEntity = BossIceGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyBossSanta)
		{
			newEntity = BossSanta::create();
		}
		else if (name == EntityDeserializer::KeyEnemyEvilSnowman)
		{
			newEntity = EvilSnowman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyFrostDragon)
		{
			newEntity = FrostDragon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyFrostShooter)
		{
			newEntity = FrostShooter::create();
		}
		else if (name == EntityDeserializer::KeyEnemyGoblinElf)
		{
			newEntity = GoblinElf::create();
		}
		else if (name == EntityDeserializer::KeyEnemyIceGolem)
		{
			newEntity = IceGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyTinyIceGolem)
		{
			newEntity = TinyIceGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyToySoldierGoblin)
		{
			newEntity = ToySoldierGoblin::create();
		}
		else if (name == EntityDeserializer::KeyEnemyWaterElemental)
		{
			newEntity = WaterElemental::create();
		}
		else if (name == EntityDeserializer::KeyEnemyYeti)
		{
			newEntity = Yeti::create();
		}
		else if (name == EntityDeserializer::KeyEnemyYetiWarrior)
		{
			newEntity = YetiWarrior::create();
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossDemonKing)
		{
			newEntity = BossDemonKing::create();
		}
		else if (name == EntityDeserializer::KeyEnemyCritterDemon)
		{
			newEntity = CritterDemon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonDragon)
		{
			newEntity = DemonDragon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonGhost)
		{
			newEntity = DemonGhost::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonGrunt)
		{
			newEntity = DemonGrunt::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonRogue)
		{
			newEntity = DemonRogue::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonShaman)
		{
			newEntity = DemonShaman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonSwordsman)
		{
			newEntity = DemonSwordsman::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonWarrior)
		{
			newEntity = DemonWarrior::create();
		}
		else if (name == EntityDeserializer::KeyEnemyFireElemental)
		{
			newEntity = FireElemental::create();
		}
		else if (name == EntityDeserializer::KeyEnemyLavaGolem)
		{
			newEntity = LavaGolem::create();
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossSkeletonKing)
		{
			newEntity = BossSkeletonKing::create();
		}
		else if (name == EntityDeserializer::KeyEnemyAbomination)
		{
			newEntity = Abomination::create();
		}
		else if (name == EntityDeserializer::KeyEnemyBatDemon)
		{
			newEntity = BatDemon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDarkDragon)
		{
			newEntity = DarkDragon::create();
		}
		else if (name == EntityDeserializer::KeyEnemyDemonArcher)
		{
			newEntity = DemonArcher::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonBaron)
		{
			newEntity = SkeletonBaron::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonCleaver)
		{
			newEntity = SkeletonCleaver::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonKnight)
		{
			newEntity = SkeletonKnight::create();
		}
		else if (name == EntityDeserializer::KeyEnemySkeletonPriestess)
		{
			newEntity = SkeletonPriestess::create();
		}
		else if (name == EntityDeserializer::KeyEnemyUndead)
		{
			newEntity = Undead::create();
		}
		else if (name == EntityDeserializer::KeyEnemyVoidDemon)
		{
			newEntity = VoidDemon::create();
		}
		//////////////////
		// MECH
		//////////////////
		else if (name == EntityDeserializer::KeyEnemyBossEvilEye)
		{
			newEntity = BossEvilEye::create();
		}
		else if (name == EntityDeserializer::KeyEnemyExterminator)
		{
			newEntity = Exterminator::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMechBoxDrone)
		{
			newEntity = MechBoxDrone::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMechDog)
		{
			newEntity = MechDog::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMechGolem)
		{
			newEntity = MechGolem::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMechGolemDark)
		{
			newEntity = MechGolemDark::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMechGuard)
		{
			newEntity = MechGuard::create();
		}
		else if (name == EntityDeserializer::KeyEnemyMiteBot)
		{
			newEntity = MiteBot::create();
		}
		else if (name == EntityDeserializer::KeyEnemyRobot)
		{
			newEntity = Robot::create();
		}
		else if (name == EntityDeserializer::KeyEnemyVikingBot)
		{
			newEntity = VikingBot::create();
		}
		else if (name == EntityDeserializer::KeyEnemyVikingBotSmall)
		{
			newEntity = VikingBotSmall::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			return;
		}

		newEntity->setPosition(Vec2(
			entity.at(SerializableObject::KeyXPosition).asFloat() + entity.at(SerializableObject::KeyWidth).asFloat() / 2,
			entity.at(SerializableObject::KeyYPosition).asFloat() + entity.at(SerializableObject::KeyHeight).asFloat() / 2)
		);

		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
