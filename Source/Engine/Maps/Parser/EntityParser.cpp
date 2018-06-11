#include "EntityParser.h"

SerializableLayer* EntityParser::parse(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::create(objectGroup);
	ValueVector entities = objectGroup->getObjects();

	// Create entities
	for (int index = 0; index < size(entities); index++)
	{
		if (entities[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap entity = entities[index].asValueMap();

		if (!GameUtils::keyExists(entity, GeneralKeys::Type) ||
			!GameUtils::keyExists(entity, GeneralKeys::Width) ||
			!GameUtils::keyExists(entity, GeneralKeys::Height) ||
			!GameUtils::keyExists(entity, GeneralKeys::XPosition) ||
			!GameUtils::keyExists(entity, GeneralKeys::YPosition))
		{
			CCLOG("Missing properties on entity");
			continue;
		}

		string type = entity.at(GeneralKeys::Type).asString();

		HackableObject* newEntity = nullptr;

		if (type == EntityKeys::SpawnProperty)
		{
			newEntity = Player::create();
		}
		else if (type == EntityKeys::NpcKnight)
		{
			newEntity = Knight::create();
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (type == EntityKeys::EnemyBossRhinoman)
		{
			newEntity = BossRhinoman::create();
		}
		else if (type == EntityKeys::EnemyGoblinGrunt)
		{
			newEntity = GoblinGrunt::create();
		}
		else if (type == EntityKeys::EnemyGoblinSwordsman)
		{
			newEntity = GoblinSwordsman::create();
		}
		else if (type == EntityKeys::EnemyGoblinWarrior)
		{
			newEntity = GoblinWarrior::create();
		}
		else if (type == EntityKeys::EnemyJungleDragon)
		{
			newEntity = JungleDragon::create();
		}
		else if (type == EntityKeys::EnemyMantis)
		{
			newEntity = Mantis::create();
		}
		else if (type == EntityKeys::EnemyMinotaur)
		{
			newEntity = Minotaur::create();
		}
		else if (type == EntityKeys::EnemyPigDemon)
		{
			newEntity = PigDemon::create();
		}
		else if (type == EntityKeys::EnemyPurpleDinosaur)
		{
			newEntity = PurpleDinosaur::create();
		}
		else if (type == EntityKeys::EnemyTikiGolem)
		{
			newEntity = TikiGolem::create();
		}
		else if (type == EntityKeys::EnemyTikiWarrior)
		{
			newEntity = TikiWarrior::create();
		}
		//////////////////
		// RUINS
		//////////////////
		else if (type == EntityKeys::EnemyBossEgyptianGoddess)
		{
			newEntity = BossEgyptianGoddess::create();
		}
		else if (type == EntityKeys::EnemyAnubisTiny)
		{
			newEntity = AnubisTiny::create();
		}
		else if (type == EntityKeys::EnemyAnubisWarrior)
		{
			newEntity = AnubisWarrior::create();
		}
		else if (type == EntityKeys::EnemyLioness)
		{
			newEntity = Lioness::create();
		}
		else if (type == EntityKeys::EnemyLionMan)
		{
			newEntity = LionMan::create();
		}
		else if (type == EntityKeys::EnemyMedusa)
		{
			newEntity = Medusa::create();
		}
		else if (type == EntityKeys::EnemyMedusaSmall)
		{
			newEntity = MedusaSmall::create();
		}
		else if (type == EntityKeys::EnemyMermaid)
		{
			newEntity = Mermaid::create();
		}
		else if (type == EntityKeys::EnemyMummyPharaoh)
		{
			newEntity = MummyPharaoh::create();
		}
		else if (type == EntityKeys::EnemyTigerMan)
		{
			newEntity = TigerMan::create();
		}
		else if (type == EntityKeys::EnemyTigress)
		{
			newEntity = Tigress::create();
		}
		//////////////////
		// FOREST
		//////////////////
		else if (type == EntityKeys::EnemyBossDragonOrcKing)
		{
			newEntity = BossDragonOrcKing::create();
		}
		else if (type == EntityKeys::EnemyCyclops)
		{
			newEntity = Cyclops::create();
		}
		else if (type == EntityKeys::EnemyEnt)
		{
			newEntity = Ent::create();
		}
		else if (type == EntityKeys::EnemyEntMage)
		{
			newEntity = EntMage::create();
		}
		else if (type == EntityKeys::EnemyGoblinGruntBoar)
		{
			newEntity = GoblinGruntBoar::create();
		}
		else if (type == EntityKeys::EnemyGoblinGuard)
		{
			newEntity = GoblinGuard::create();
		}
		else if (type == EntityKeys::EnemyGoblinShaman)
		{
			newEntity = GoblinShaman::create();
		}
		else if (type == EntityKeys::EnemyGoblinWarriorPig)
		{
			newEntity = GoblinWarriorPig::create();
		}
		else if (type == EntityKeys::EnemyOrcGrunt)
		{
			newEntity = OrcGrunt::create();
		}
		else if (type == EntityKeys::EnemyOrcWarrior)
		{
			newEntity = OrcWarrior::create();
		}
		else if (type == EntityKeys::EnemyTroll)
		{
			newEntity = Troll::create();
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (type == EntityKeys::EnemyBossKrampus)
		{
			newEntity = BossKrampus::create();
		}
		else if (type == EntityKeys::EnemyBlackWidow)
		{
			newEntity = BlackWidow::create();
		}
		else if (type == EntityKeys::EnemyEarthElemental)
		{
			newEntity = EarthElemental::create();
		}
		else if (type == EntityKeys::EnemyEarthGolem)
		{
			newEntity = EarthGolem::create();
		}
		else if (type == EntityKeys::EnemyForestGolem)
		{
			newEntity = ForestGolem::create();
		}
		else if (type == EntityKeys::EnemyGenie)
		{
			newEntity = Genie::create();
		}
		else if (type == EntityKeys::EnemyRockGolem)
		{
			newEntity = RockGolem::create();
		}
		else if (type == EntityKeys::EnemyShaman)
		{
			newEntity = Shaman::create();
		}
		else if (type == EntityKeys::EnemySkeletonArcher)
		{
			newEntity = SkeletonArcher::create();
		}
		else if (type == EntityKeys::EnemySkeletonNecromancer)
		{
			newEntity = SkeletonNecromancer::create();
		}
		else if (type == EntityKeys::EnemySkeletonWarrior)
		{
			newEntity = SkeletonWarrior::create();
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (type == EntityKeys::EnemyBossWitch)
		{
			newEntity = BossWitch::create();
		}
		else if (type == EntityKeys::EnemyExecutioner)
		{
			newEntity = Executioner::create();
		}
		else if (type == EntityKeys::EnemyGhost)
		{
			newEntity = Ghost::create();
		}
		else if (type == EntityKeys::EnemyGuard)
		{
			newEntity = Guard::create();
		}
		else if (type == EntityKeys::EnemyHarpy)
		{
			newEntity = Harpy::create();
		}
		else if (type == EntityKeys::EnemyJack)
		{
			newEntity = Jack::create();
		}
		else if (type == EntityKeys::EnemyReaper)
		{
			newEntity = Reaper::create();
		}
		else if (type == EntityKeys::EnemySkeletonMage)
		{
			newEntity = SkeletonMage::create();
		}
		else if (type == EntityKeys::EnemyVampireLord)
		{
			newEntity = VampireLord::create();
		}
		else if (type == EntityKeys::EnemyVampiress)
		{
			newEntity = Vampiress::create();
		}
		else if (type == EntityKeys::EnemyZombie)
		{
			newEntity = Zombie::create();
		}
		//////////////////
		// SNOW
		//////////////////
		else if (type == EntityKeys::EnemyBossIceGolem)
		{
			newEntity = BossIceGolem::create();
		}
		else if (type == EntityKeys::EnemyBossSanta)
		{
			newEntity = BossSanta::create();
		}
		else if (type == EntityKeys::EnemyEvilSnowman)
		{
			newEntity = EvilSnowman::create();
		}
		else if (type == EntityKeys::EnemyFrostDragon)
		{
			newEntity = FrostDragon::create();
		}
		else if (type == EntityKeys::EnemyFrostShooter)
		{
			newEntity = FrostShooter::create();
		}
		else if (type == EntityKeys::EnemyGoblinElf)
		{
			newEntity = GoblinElf::create();
		}
		else if (type == EntityKeys::EnemyIceGolem)
		{
			newEntity = IceGolem::create();
		}
		else if (type == EntityKeys::EnemyTinyIceGolem)
		{
			newEntity = TinyIceGolem::create();
		}
		else if (type == EntityKeys::EnemyToySoldierGoblin)
		{
			newEntity = ToySoldierGoblin::create();
		}
		else if (type == EntityKeys::EnemyWaterElemental)
		{
			newEntity = WaterElemental::create();
		}
		else if (type == EntityKeys::EnemyYeti)
		{
			newEntity = Yeti::create();
		}
		else if (type == EntityKeys::EnemyYetiWarrior)
		{
			newEntity = YetiWarrior::create();
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (type == EntityKeys::EnemyBossDemonKing)
		{
			newEntity = BossDemonKing::create();
		}
		else if (type == EntityKeys::EnemyCritterDemon)
		{
			newEntity = CritterDemon::create();
		}
		else if (type == EntityKeys::EnemyDemonDragon)
		{
			newEntity = DemonDragon::create();
		}
		else if (type == EntityKeys::EnemyDemonGhost)
		{
			newEntity = DemonGhost::create();
		}
		else if (type == EntityKeys::EnemyDemonGrunt)
		{
			newEntity = DemonGrunt::create();
		}
		else if (type == EntityKeys::EnemyDemonRogue)
		{
			newEntity = DemonRogue::create();
		}
		else if (type == EntityKeys::EnemyDemonShaman)
		{
			newEntity = DemonShaman::create();
		}
		else if (type == EntityKeys::EnemyDemonSwordsman)
		{
			newEntity = DemonSwordsman::create();
		}
		else if (type == EntityKeys::EnemyDemonWarrior)
		{
			newEntity = DemonWarrior::create();
		}
		else if (type == EntityKeys::EnemyFireElemental)
		{
			newEntity = FireElemental::create();
		}
		else if (type == EntityKeys::EnemyLavaGolem)
		{
			newEntity = LavaGolem::create();
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (type == EntityKeys::EnemyBossSkeletonKing)
		{
			newEntity = BossSkeletonKing::create();
		}
		else if (type == EntityKeys::EnemyAbomination)
		{
			newEntity = Abomination::create();
		}
		else if (type == EntityKeys::EnemyBatDemon)
		{
			newEntity = BatDemon::create();
		}
		else if (type == EntityKeys::EnemyDarkDragon)
		{
			newEntity = DarkDragon::create();
		}
		else if (type == EntityKeys::EnemyDemonArcher)
		{
			newEntity = DemonArcher::create();
		}
		else if (type == EntityKeys::EnemySkeletonBaron)
		{
			newEntity = SkeletonBaron::create();
		}
		else if (type == EntityKeys::EnemySkeletonCleaver)
		{
			newEntity = SkeletonCleaver::create();
		}
		else if (type == EntityKeys::EnemySkeletonKnight)
		{
			newEntity = SkeletonKnight::create();
		}
		else if (type == EntityKeys::EnemySkeletonPriestess)
		{
			newEntity = SkeletonPriestess::create();
		}
		else if (type == EntityKeys::EnemyUndead)
		{
			newEntity = Undead::create();
		}
		else if (type == EntityKeys::EnemyVoidDemon)
		{
			newEntity = VoidDemon::create();
		}
		//////////////////
		// MECH
		//////////////////
		else if (type == EntityKeys::EnemyBossEvilEye)
		{
			newEntity = BossEvilEye::create();
		}
		else if (type == EntityKeys::EnemyExterminator)
		{
			newEntity = Exterminator::create();
		}
		else if (type == EntityKeys::EnemyMechBoxDrone)
		{
			newEntity = MechBoxDrone::create();
		}
		else if (type == EntityKeys::EnemyMechDog)
		{
			newEntity = MechDog::create();
		}
		else if (type == EntityKeys::EnemyMechGolem)
		{
			newEntity = MechGolem::create();
		}
		else if (type == EntityKeys::EnemyMechGolemDark)
		{
			newEntity = MechGolemDark::create();
		}
		else if (type == EntityKeys::EnemyMechGuard)
		{
			newEntity = MechGuard::create();
		}
		else if (type == EntityKeys::EnemyMiteBot)
		{
			newEntity = MiteBot::create();
		}
		else if (type == EntityKeys::EnemyRobot)
		{
			newEntity = Robot::create();
		}
		else if (type == EntityKeys::EnemyVikingBot)
		{
			newEntity = VikingBot::create();
		}
		else if (type == EntityKeys::EnemyVikingBotSmall)
		{
			newEntity = VikingBotSmall::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			continue;
		}

		newEntity->setPosition(Vec2(
			entity.at(GeneralKeys::XPosition).asFloat() + entity.at(GeneralKeys::Width).asFloat() / 2,
			entity.at(GeneralKeys::YPosition).asFloat() + entity.at(GeneralKeys::Height).asFloat() / 2)
		);

		layer->addChild(newEntity);
	}

	return layer;
}
