#include "EntityDeserializer.h"

const std::string EntityDeserializer::KeyTypeEntity = "entity";

EntityDeserializer::EntityDeserializer()
{
}

EntityDeserializer::~EntityDeserializer()
{
}

void EntityDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == EntityDeserializer::KeyTypeEntity)
	{
		ValueMap properties = args->properties;
		string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newEntity = nullptr;

		if (name == Player::KeySquallyProperty)
		{
			newEntity = Player::create();
		}
		else if (name == Knight::KeyNpcKnight)
		{
			newEntity = Knight::create();
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (name == BossRhinoman::KeyEnemyBossRhinoman)
		{
			newEntity = BossRhinoman::create();
		}
		else if (name == GoblinGrunt::KeyEnemyGoblinGrunt)
		{
			newEntity = GoblinGrunt::create();
		}
		else if (name == GoblinSwordsman::KeyEnemyGoblinSwordsman)
		{
			newEntity = GoblinSwordsman::create();
		}
		else if (name == GoblinWarrior::KeyEnemyGoblinWarrior)
		{
			newEntity = GoblinWarrior::create();
		}
		else if (name == JungleDragon::KeyEnemyJungleDragon)
		{
			newEntity = JungleDragon::create();
		}
		else if (name == Mantis::KeyEnemyMantis)
		{
			newEntity = Mantis::create();
		}
		else if (name == Minotaur::KeyEnemyMinotaur)
		{
			newEntity = Minotaur::create();
		}
		else if (name == PigDemon::KeyEnemyPigDemon)
		{
			newEntity = PigDemon::create();
		}
		else if (name == PurpleDinosaur::KeyEnemyPurpleDinosaur)
		{
			newEntity = PurpleDinosaur::create();
		}
		else if (name == TikiGolem::KeyEnemyTikiGolem)
		{
			newEntity = TikiGolem::create();
		}
		else if (name == TikiWarrior::KeyEnemyTikiWarrior)
		{
			newEntity = TikiWarrior::create();
		}
		//////////////////
		// RUINS
		//////////////////
		else if (name == BossEgyptianGoddess::KeyEnemyBossEgyptianGoddess)
		{
			newEntity = BossEgyptianGoddess::create();
		}
		else if (name == AnubisTiny::KeyEnemyAnubisTiny)
		{
			newEntity = AnubisTiny::create();
		}
		else if (name == AnubisWarrior::KeyEnemyAnubisWarrior)
		{
			newEntity = AnubisWarrior::create();
		}
		else if (name == Lioness::KeyEnemyLioness)
		{
			newEntity = Lioness::create();
		}
		else if (name == LionMan::KeyEnemyLionMan)
		{
			newEntity = LionMan::create();
		}
		else if (name == Medusa::KeyEnemyMedusa)
		{
			newEntity = Medusa::create();
		}
		else if (name == MedusaSmall::KeyEnemyMedusaSmall)
		{
			newEntity = MedusaSmall::create();
		}
		else if (name == Mermaid::KeyEnemyMermaid)
		{
			newEntity = Mermaid::create();
		}
		else if (name == MummyPharaoh::KeyEnemyMummyPharaoh)
		{
			newEntity = MummyPharaoh::create();
		}
		else if (name == TigerMan::KeyEnemyTigerMan)
		{
			newEntity = TigerMan::create();
		}
		else if (name == Tigress::KeyEnemyTigress)
		{
			newEntity = Tigress::create();
		}
		//////////////////
		// FOREST
		//////////////////
		else if (name == BossDragonOrcKing::KeyEnemyBossDragonOrcKing)
		{
			newEntity = BossDragonOrcKing::create();
		}
		else if (name == Cyclops::KeyEnemyCyclops)
		{
			newEntity = Cyclops::create();
		}
		else if (name == Ent::KeyEnemyEnt)
		{
			newEntity = Ent::create();
		}
		else if (name == EntMage::KeyEnemyEntMage)
		{
			newEntity = EntMage::create();
		}
		else if (name == GoblinGruntBoar::KeyEnemyGoblinGruntBoar)
		{
			newEntity = GoblinGruntBoar::create();
		}
		else if (name == GoblinGuard::KeyEnemyGoblinGuard)
		{
			newEntity = GoblinGuard::create();
		}
		else if (name == GoblinShaman::KeyEnemyGoblinShaman)
		{
			newEntity = GoblinShaman::create();
		}
		else if (name == GoblinWarriorPig::KeyEnemyGoblinWarriorPig)
		{
			newEntity = GoblinWarriorPig::create();
		}
		else if (name == OrcGrunt::KeyEnemyOrcGrunt)
		{
			newEntity = OrcGrunt::create();
		}
		else if (name == OrcWarrior::KeyEnemyOrcWarrior)
		{
			newEntity = OrcWarrior::create();
		}
		else if (name == Troll::KeyEnemyTroll)
		{
			newEntity = Troll::create();
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (name == BossKrampus::KeyEnemyBossKrampus)
		{
			newEntity = BossKrampus::create();
		}
		else if (name == BlackWidow::KeyEnemyBlackWidow)
		{
			newEntity = BlackWidow::create();
		}
		else if (name == EarthElemental::KeyEnemyEarthElemental)
		{
			newEntity = EarthElemental::create();
		}
		else if (name == EarthGolem::KeyEnemyEarthGolem)
		{
			newEntity = EarthGolem::create();
		}
		else if (name == ForestGolem::KeyEnemyForestGolem)
		{
			newEntity = ForestGolem::create();
		}
		else if (name == Genie::KeyEnemyGenie)
		{
			newEntity = Genie::create();
		}
		else if (name == RockGolem::KeyEnemyRockGolem)
		{
			newEntity = RockGolem::create();
		}
		else if (name == Shaman::KeyEnemyShaman)
		{
			newEntity = Shaman::create();
		}
		else if (name == SkeletonArcher::KeyEnemySkeletonArcher)
		{
			newEntity = SkeletonArcher::create();
		}
		else if (name == SkeletonNecromancer::KeyEnemySkeletonNecromancer)
		{
			newEntity = SkeletonNecromancer::create();
		}
		else if (name == SkeletonWarrior::KeyEnemySkeletonWarrior)
		{
			newEntity = SkeletonWarrior::create();
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (name == BossWitch::KeyEnemyBossWitch)
		{
			newEntity = BossWitch::create();
		}
		else if (name == Executioner::KeyEnemyExecutioner)
		{
			newEntity = Executioner::create();
		}
		else if (name == Ghost::KeyEnemyGhost)
		{
			newEntity = Ghost::create();
		}
		else if (name == Guard::KeyEnemyGuard)
		{
			newEntity = Guard::create();
		}
		else if (name == Harpy::KeyEnemyHarpy)
		{
			newEntity = Harpy::create();
		}
		else if (name == Jack::KeyEnemyJack)
		{
			newEntity = Jack::create();
		}
		else if (name == Reaper::KeyEnemyReaper)
		{
			newEntity = Reaper::create();
		}
		else if (name == SkeletonMage::KeyEnemySkeletonMage)
		{
			newEntity = SkeletonMage::create();
		}
		else if (name == VampireLord::KeyEnemyVampireLord)
		{
			newEntity = VampireLord::create();
		}
		else if (name == Vampiress::KeyEnemyVampiress)
		{
			newEntity = Vampiress::create();
		}
		else if (name == Zombie::KeyEnemyZombie)
		{
			newEntity = Zombie::create();
		}
		//////////////////
		// SNOW
		//////////////////
		else if (name == BossIceGolem::KeyEnemyBossIceGolem)
		{
			newEntity = BossIceGolem::create();
		}
		else if (name == BossSanta::KeyEnemyBossSanta)
		{
			newEntity = BossSanta::create();
		}
		else if (name == EvilSnowman::KeyEnemyEvilSnowman)
		{
			newEntity = EvilSnowman::create();
		}
		else if (name == FrostDragon::KeyEnemyFrostDragon)
		{
			newEntity = FrostDragon::create();
		}
		else if (name == FrostShooter::KeyEnemyFrostShooter)
		{
			newEntity = FrostShooter::create();
		}
		else if (name == GoblinElf::KeyEnemyGoblinElf)
		{
			newEntity = GoblinElf::create();
		}
		else if (name == IceGolem::KeyEnemyIceGolem)
		{
			newEntity = IceGolem::create();
		}
		else if (name == TinyIceGolem::KeyEnemyTinyIceGolem)
		{
			newEntity = TinyIceGolem::create();
		}
		else if (name == ToySoldierGoblin::KeyEnemyToySoldierGoblin)
		{
			newEntity = ToySoldierGoblin::create();
		}
		else if (name == WaterElemental::KeyEnemyWaterElemental)
		{
			newEntity = WaterElemental::create();
		}
		else if (name == Yeti::KeyEnemyYeti)
		{
			newEntity = Yeti::create();
		}
		else if (name == YetiWarrior::KeyEnemyYetiWarrior)
		{
			newEntity = YetiWarrior::create();
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (name == BossDemonKing::KeyEnemyBossDemonKing)
		{
			newEntity = BossDemonKing::create();
		}
		else if (name == CritterDemon::KeyEnemyCritterDemon)
		{
			newEntity = CritterDemon::create();
		}
		else if (name == DemonDragon::KeyEnemyDemonDragon)
		{
			newEntity = DemonDragon::create();
		}
		else if (name == DemonGhost::KeyEnemyDemonGhost)
		{
			newEntity = DemonGhost::create();
		}
		else if (name == DemonGrunt::KeyEnemyDemonGrunt)
		{
			newEntity = DemonGrunt::create();
		}
		else if (name == DemonRogue::KeyEnemyDemonRogue)
		{
			newEntity = DemonRogue::create();
		}
		else if (name == DemonShaman::KeyEnemyDemonShaman)
		{
			newEntity = DemonShaman::create();
		}
		else if (name == DemonSwordsman::KeyEnemyDemonSwordsman)
		{
			newEntity = DemonSwordsman::create();
		}
		else if (name == DemonWarrior::KeyEnemyDemonWarrior)
		{
			newEntity = DemonWarrior::create();
		}
		else if (name == FireElemental::KeyEnemyFireElemental)
		{
			newEntity = FireElemental::create();
		}
		else if (name == LavaGolem::KeyEnemyLavaGolem)
		{
			newEntity = LavaGolem::create();
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (name == BossSkeletonKing::KeyEnemyBossSkeletonKing)
		{
			newEntity = BossSkeletonKing::create();
		}
		else if (name == Abomination::KeyEnemyAbomination)
		{
			newEntity = Abomination::create();
		}
		else if (name == BatDemon::KeyEnemyBatDemon)
		{
			newEntity = BatDemon::create();
		}
		else if (name == DarkDragon::KeyEnemyDarkDragon)
		{
			newEntity = DarkDragon::create();
		}
		else if (name == DemonArcher::KeyEnemyDemonArcher)
		{
			newEntity = DemonArcher::create();
		}
		else if (name == SkeletonBaron::KeyEnemySkeletonBaron)
		{
			newEntity = SkeletonBaron::create();
		}
		else if (name == SkeletonCleaver::KeyEnemySkeletonCleaver)
		{
			newEntity = SkeletonCleaver::create();
		}
		else if (name == SkeletonKnight::KeyEnemySkeletonKnight)
		{
			newEntity = SkeletonKnight::create();
		}
		else if (name == SkeletonPriestess::KeyEnemySkeletonPriestess)
		{
			newEntity = SkeletonPriestess::create();
		}
		else if (name == Undead::KeyEnemyUndead)
		{
			newEntity = Undead::create();
		}
		else if (name == VoidDemon::KeyEnemyVoidDemon)
		{
			newEntity = VoidDemon::create();
		}
		//////////////////
		// MECH
		//////////////////
		else if (name == BossEvilEye::KeyEnemyBossEvilEye)
		{
			newEntity = BossEvilEye::create();
		}
		else if (name == Exterminator::KeyEnemyExterminator)
		{
			newEntity = Exterminator::create();
		}
		else if (name == MechBoxDrone::KeyEnemyMechBoxDrone)
		{
			newEntity = MechBoxDrone::create();
		}
		else if (name == MechDog::KeyEnemyMechDog)
		{
			newEntity = MechDog::create();
		}
		else if (name == MechGolem::KeyEnemyMechGolem)
		{
			newEntity = MechGolem::create();
		}
		else if (name == MechGolemDark::KeyEnemyMechGolemDark)
		{
			newEntity = MechGolemDark::create();
		}
		else if (name == MechGuard::KeyEnemyMechGuard)
		{
			newEntity = MechGuard::create();
		}
		else if (name == MiteBot::KeyEnemyMiteBot)
		{
			newEntity = MiteBot::create();
		}
		else if (name == Robot::KeyEnemyRobot)
		{
			newEntity = Robot::create();
		}
		else if (name == VikingBot::KeyEnemyVikingBot)
		{
			newEntity = VikingBot::create();
		}
		else if (name == VikingBotSmall::KeyEnemyVikingBotSmall)
		{
			newEntity = VikingBotSmall::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			return;
		}

		newEntity->setPosition(Vec2(
			properties.at(SerializableObject::KeyXPosition).asFloat() + properties.at(SerializableObject::KeyWidth).asFloat() / 2,
			properties.at(SerializableObject::KeyYPosition).asFloat() + properties.at(SerializableObject::KeyHeight).asFloat() / 2)
		);

		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
