#include "EntityDeserializer.h"

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

SerializableLayer* EntityDeserializer::deserialize(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::deserialize(objectGroup);
	ValueVector entities = objectGroup->getObjects();

	// Create entities
	for (int index = 0; index < size(entities); index++)
	{
		if (entities[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap entity = entities[index].asValueMap();

		if (!GameUtils::keyExists(entity, SerializableObject::KeyType) ||
			!GameUtils::keyExists(entity, SerializableObject::KeyWidth) ||
			!GameUtils::keyExists(entity, SerializableObject::KeyHeight) ||
			!GameUtils::keyExists(entity, SerializableObject::KeyXPosition) ||
			!GameUtils::keyExists(entity, SerializableObject::KeyYPosition))
		{
			CCLOG("Missing properties on entity");
			continue;
		}

		string type = entity.at(SerializableObject::KeyType).asString();

		HackableObject* newEntity = nullptr;

		if (type == EntityDeserializer::KeySpawnProperty)
		{
			newEntity = Player::create();
		}
		else if (type == EntityDeserializer::KeyNpcKnight)
		{
			newEntity = Knight::create();
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossRhinoman)
		{
			newEntity = BossRhinoman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinGrunt)
		{
			newEntity = GoblinGrunt::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinSwordsman)
		{
			newEntity = GoblinSwordsman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinWarrior)
		{
			newEntity = GoblinWarrior::create();
		}
		else if (type == EntityDeserializer::KeyEnemyJungleDragon)
		{
			newEntity = JungleDragon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMantis)
		{
			newEntity = Mantis::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMinotaur)
		{
			newEntity = Minotaur::create();
		}
		else if (type == EntityDeserializer::KeyEnemyPigDemon)
		{
			newEntity = PigDemon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyPurpleDinosaur)
		{
			newEntity = PurpleDinosaur::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTikiGolem)
		{
			newEntity = TikiGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTikiWarrior)
		{
			newEntity = TikiWarrior::create();
		}
		//////////////////
		// RUINS
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossEgyptianGoddess)
		{
			newEntity = BossEgyptianGoddess::create();
		}
		else if (type == EntityDeserializer::KeyEnemyAnubisTiny)
		{
			newEntity = AnubisTiny::create();
		}
		else if (type == EntityDeserializer::KeyEnemyAnubisWarrior)
		{
			newEntity = AnubisWarrior::create();
		}
		else if (type == EntityDeserializer::KeyEnemyLioness)
		{
			newEntity = Lioness::create();
		}
		else if (type == EntityDeserializer::KeyEnemyLionMan)
		{
			newEntity = LionMan::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMedusa)
		{
			newEntity = Medusa::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMedusaSmall)
		{
			newEntity = MedusaSmall::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMermaid)
		{
			newEntity = Mermaid::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMummyPharaoh)
		{
			newEntity = MummyPharaoh::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTigerMan)
		{
			newEntity = TigerMan::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTigress)
		{
			newEntity = Tigress::create();
		}
		//////////////////
		// FOREST
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossDragonOrcKing)
		{
			newEntity = BossDragonOrcKing::create();
		}
		else if (type == EntityDeserializer::KeyEnemyCyclops)
		{
			newEntity = Cyclops::create();
		}
		else if (type == EntityDeserializer::KeyEnemyEnt)
		{
			newEntity = Ent::create();
		}
		else if (type == EntityDeserializer::KeyEnemyEntMage)
		{
			newEntity = EntMage::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinGruntBoar)
		{
			newEntity = GoblinGruntBoar::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinGuard)
		{
			newEntity = GoblinGuard::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinShaman)
		{
			newEntity = GoblinShaman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinWarriorPig)
		{
			newEntity = GoblinWarriorPig::create();
		}
		else if (type == EntityDeserializer::KeyEnemyOrcGrunt)
		{
			newEntity = OrcGrunt::create();
		}
		else if (type == EntityDeserializer::KeyEnemyOrcWarrior)
		{
			newEntity = OrcWarrior::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTroll)
		{
			newEntity = Troll::create();
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossKrampus)
		{
			newEntity = BossKrampus::create();
		}
		else if (type == EntityDeserializer::KeyEnemyBlackWidow)
		{
			newEntity = BlackWidow::create();
		}
		else if (type == EntityDeserializer::KeyEnemyEarthElemental)
		{
			newEntity = EarthElemental::create();
		}
		else if (type == EntityDeserializer::KeyEnemyEarthGolem)
		{
			newEntity = EarthGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyForestGolem)
		{
			newEntity = ForestGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGenie)
		{
			newEntity = Genie::create();
		}
		else if (type == EntityDeserializer::KeyEnemyRockGolem)
		{
			newEntity = RockGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyShaman)
		{
			newEntity = Shaman::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonArcher)
		{
			newEntity = SkeletonArcher::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonNecromancer)
		{
			newEntity = SkeletonNecromancer::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonWarrior)
		{
			newEntity = SkeletonWarrior::create();
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossWitch)
		{
			newEntity = BossWitch::create();
		}
		else if (type == EntityDeserializer::KeyEnemyExecutioner)
		{
			newEntity = Executioner::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGhost)
		{
			newEntity = Ghost::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGuard)
		{
			newEntity = Guard::create();
		}
		else if (type == EntityDeserializer::KeyEnemyHarpy)
		{
			newEntity = Harpy::create();
		}
		else if (type == EntityDeserializer::KeyEnemyJack)
		{
			newEntity = Jack::create();
		}
		else if (type == EntityDeserializer::KeyEnemyReaper)
		{
			newEntity = Reaper::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonMage)
		{
			newEntity = SkeletonMage::create();
		}
		else if (type == EntityDeserializer::KeyEnemyVampireLord)
		{
			newEntity = VampireLord::create();
		}
		else if (type == EntityDeserializer::KeyEnemyVampiress)
		{
			newEntity = Vampiress::create();
		}
		else if (type == EntityDeserializer::KeyEnemyZombie)
		{
			newEntity = Zombie::create();
		}
		//////////////////
		// SNOW
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossIceGolem)
		{
			newEntity = BossIceGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyBossSanta)
		{
			newEntity = BossSanta::create();
		}
		else if (type == EntityDeserializer::KeyEnemyEvilSnowman)
		{
			newEntity = EvilSnowman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyFrostDragon)
		{
			newEntity = FrostDragon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyFrostShooter)
		{
			newEntity = FrostShooter::create();
		}
		else if (type == EntityDeserializer::KeyEnemyGoblinElf)
		{
			newEntity = GoblinElf::create();
		}
		else if (type == EntityDeserializer::KeyEnemyIceGolem)
		{
			newEntity = IceGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyTinyIceGolem)
		{
			newEntity = TinyIceGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyToySoldierGoblin)
		{
			newEntity = ToySoldierGoblin::create();
		}
		else if (type == EntityDeserializer::KeyEnemyWaterElemental)
		{
			newEntity = WaterElemental::create();
		}
		else if (type == EntityDeserializer::KeyEnemyYeti)
		{
			newEntity = Yeti::create();
		}
		else if (type == EntityDeserializer::KeyEnemyYetiWarrior)
		{
			newEntity = YetiWarrior::create();
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossDemonKing)
		{
			newEntity = BossDemonKing::create();
		}
		else if (type == EntityDeserializer::KeyEnemyCritterDemon)
		{
			newEntity = CritterDemon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonDragon)
		{
			newEntity = DemonDragon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonGhost)
		{
			newEntity = DemonGhost::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonGrunt)
		{
			newEntity = DemonGrunt::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonRogue)
		{
			newEntity = DemonRogue::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonShaman)
		{
			newEntity = DemonShaman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonSwordsman)
		{
			newEntity = DemonSwordsman::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonWarrior)
		{
			newEntity = DemonWarrior::create();
		}
		else if (type == EntityDeserializer::KeyEnemyFireElemental)
		{
			newEntity = FireElemental::create();
		}
		else if (type == EntityDeserializer::KeyEnemyLavaGolem)
		{
			newEntity = LavaGolem::create();
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossSkeletonKing)
		{
			newEntity = BossSkeletonKing::create();
		}
		else if (type == EntityDeserializer::KeyEnemyAbomination)
		{
			newEntity = Abomination::create();
		}
		else if (type == EntityDeserializer::KeyEnemyBatDemon)
		{
			newEntity = BatDemon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDarkDragon)
		{
			newEntity = DarkDragon::create();
		}
		else if (type == EntityDeserializer::KeyEnemyDemonArcher)
		{
			newEntity = DemonArcher::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonBaron)
		{
			newEntity = SkeletonBaron::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonCleaver)
		{
			newEntity = SkeletonCleaver::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonKnight)
		{
			newEntity = SkeletonKnight::create();
		}
		else if (type == EntityDeserializer::KeyEnemySkeletonPriestess)
		{
			newEntity = SkeletonPriestess::create();
		}
		else if (type == EntityDeserializer::KeyEnemyUndead)
		{
			newEntity = Undead::create();
		}
		else if (type == EntityDeserializer::KeyEnemyVoidDemon)
		{
			newEntity = VoidDemon::create();
		}
		//////////////////
		// MECH
		//////////////////
		else if (type == EntityDeserializer::KeyEnemyBossEvilEye)
		{
			newEntity = BossEvilEye::create();
		}
		else if (type == EntityDeserializer::KeyEnemyExterminator)
		{
			newEntity = Exterminator::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMechBoxDrone)
		{
			newEntity = MechBoxDrone::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMechDog)
		{
			newEntity = MechDog::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMechGolem)
		{
			newEntity = MechGolem::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMechGolemDark)
		{
			newEntity = MechGolemDark::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMechGuard)
		{
			newEntity = MechGuard::create();
		}
		else if (type == EntityDeserializer::KeyEnemyMiteBot)
		{
			newEntity = MiteBot::create();
		}
		else if (type == EntityDeserializer::KeyEnemyRobot)
		{
			newEntity = Robot::create();
		}
		else if (type == EntityDeserializer::KeyEnemyVikingBot)
		{
			newEntity = VikingBot::create();
		}
		else if (type == EntityDeserializer::KeyEnemyVikingBotSmall)
		{
			newEntity = VikingBotSmall::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			continue;
		}

		newEntity->setPosition(Vec2(
			entity.at(SerializableObject::KeyXPosition).asFloat() + entity.at(SerializableObject::KeyWidth).asFloat() / 2,
			entity.at(SerializableObject::KeyYPosition).asFloat() + entity.at(SerializableObject::KeyHeight).asFloat() / 2)
		);

		layer->addChild(newEntity);
	}

	return layer;
}
