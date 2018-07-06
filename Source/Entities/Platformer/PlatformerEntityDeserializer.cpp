#include "PlatformerEntityDeserializer.h"

const std::string PlatformerEntityDeserializer::KeyTypeEntity = "entity";

PlatformerEntityDeserializer::PlatformerEntityDeserializer()
{
}

PlatformerEntityDeserializer::~PlatformerEntityDeserializer()
{
}

void PlatformerEntityDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerEntityDeserializer::KeyTypeEntity)
	{
		ValueMap properties = args->properties;
		string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newEntity = nullptr;

		if (name == Squally::KeySquallyProperty)
		{
			newEntity = Squally::deserialize(&properties);
		}
		else if (name == Knight::KeyNpcKnight)
		{
			newEntity = Knight::deserialize(&properties);
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (name == BossRhinoman::KeyEnemyBossRhinoman)
		{
			newEntity = BossRhinoman::deserialize(&properties);
		}
		else if (name == GoblinGrunt::KeyEnemyGoblinGrunt)
		{
			newEntity = GoblinGrunt::deserialize(&properties);
		}
		else if (name == GoblinSwordsman::KeyEnemyGoblinSwordsman)
		{
			newEntity = GoblinSwordsman::deserialize(&properties);
		}
		else if (name == GoblinWarrior::KeyEnemyGoblinWarrior)
		{
			newEntity = GoblinWarrior::deserialize(&properties);
		}
		else if (name == JungleDragon::KeyEnemyJungleDragon)
		{
			newEntity = JungleDragon::deserialize(&properties);
		}
		else if (name == Mantis::KeyEnemyMantis)
		{
			newEntity = Mantis::deserialize(&properties);
		}
		else if (name == Minotaur::KeyEnemyMinotaur)
		{
			newEntity = Minotaur::deserialize(&properties);
		}
		else if (name == PigDemon::KeyEnemyPigDemon)
		{
			newEntity = PigDemon::deserialize(&properties);
		}
		else if (name == PurpleDinosaur::KeyEnemyPurpleDinosaur)
		{
			newEntity = PurpleDinosaur::deserialize(&properties);
		}
		else if (name == TikiGolem::KeyEnemyTikiGolem)
		{
			newEntity = TikiGolem::deserialize(&properties);
		}
		else if (name == TikiWarrior::KeyEnemyTikiWarrior)
		{
			newEntity = TikiWarrior::deserialize(&properties);
		}
		//////////////////
		// RUINS
		//////////////////
		else if (name == BossEgyptianGoddess::KeyEnemyBossEgyptianGoddess)
		{
			newEntity = BossEgyptianGoddess::deserialize(&properties);
		}
		else if (name == AnubisTiny::KeyEnemyAnubisTiny)
		{
			newEntity = AnubisTiny::deserialize(&properties);
		}
		else if (name == AnubisWarrior::KeyEnemyAnubisWarrior)
		{
			newEntity = AnubisWarrior::deserialize(&properties);
		}
		else if (name == Lioness::KeyEnemyLioness)
		{
			newEntity = Lioness::deserialize(&properties);
		}
		else if (name == LionMan::KeyEnemyLionMan)
		{
			newEntity = LionMan::deserialize(&properties);
		}
		else if (name == Medusa::KeyEnemyMedusa)
		{
			newEntity = Medusa::deserialize(&properties);
		}
		else if (name == MedusaSmall::KeyEnemyMedusaSmall)
		{
			newEntity = MedusaSmall::deserialize(&properties);
		}
		else if (name == Mermaid::KeyEnemyMermaid)
		{
			newEntity = Mermaid::deserialize(&properties);
		}
		else if (name == MummyPharaoh::KeyEnemyMummyPharaoh)
		{
			newEntity = MummyPharaoh::deserialize(&properties);
		}
		else if (name == TigerMan::KeyEnemyTigerMan)
		{
			newEntity = TigerMan::deserialize(&properties);
		}
		else if (name == Tigress::KeyEnemyTigress)
		{
			newEntity = Tigress::deserialize(&properties);
		}
		//////////////////
		// FOREST
		//////////////////
		else if (name == BossDragonOrcKing::KeyEnemyBossDragonOrcKing)
		{
			newEntity = BossDragonOrcKing::deserialize(&properties);
		}
		else if (name == Cyclops::KeyEnemyCyclops)
		{
			newEntity = Cyclops::deserialize(&properties);
		}
		else if (name == Ent::KeyEnemyEnt)
		{
			newEntity = Ent::deserialize(&properties);
		}
		else if (name == EntMage::KeyEnemyEntMage)
		{
			newEntity = EntMage::deserialize(&properties);
		}
		else if (name == GoblinGruntBoar::KeyEnemyGoblinGruntBoar)
		{
			newEntity = GoblinGruntBoar::deserialize(&properties);
		}
		else if (name == GoblinGuard::KeyEnemyGoblinGuard)
		{
			newEntity = GoblinGuard::deserialize(&properties);
		}
		else if (name == GoblinShaman::KeyEnemyGoblinShaman)
		{
			newEntity = GoblinShaman::deserialize(&properties);
		}
		else if (name == GoblinWarriorPig::KeyEnemyGoblinWarriorPig)
		{
			newEntity = GoblinWarriorPig::deserialize(&properties);
		}
		else if (name == OrcGrunt::KeyEnemyOrcGrunt)
		{
			newEntity = OrcGrunt::deserialize(&properties);
		}
		else if (name == OrcWarrior::KeyEnemyOrcWarrior)
		{
			newEntity = OrcWarrior::deserialize(&properties);
		}
		else if (name == Troll::KeyEnemyTroll)
		{
			newEntity = Troll::deserialize(&properties);
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (name == BossKrampus::KeyEnemyBossKrampus)
		{
			newEntity = BossKrampus::deserialize(&properties);
		}
		else if (name == BlackWidow::KeyEnemyBlackWidow)
		{
			newEntity = BlackWidow::deserialize(&properties);
		}
		else if (name == EarthElemental::KeyEnemyEarthElemental)
		{
			newEntity = EarthElemental::deserialize(&properties);
		}
		else if (name == EarthGolem::KeyEnemyEarthGolem)
		{
			newEntity = EarthGolem::deserialize(&properties);
		}
		else if (name == ForestGolem::KeyEnemyForestGolem)
		{
			newEntity = ForestGolem::deserialize(&properties);
		}
		else if (name == Genie::KeyEnemyGenie)
		{
			newEntity = Genie::deserialize(&properties);
		}
		else if (name == RockGolem::KeyEnemyRockGolem)
		{
			newEntity = RockGolem::deserialize(&properties);
		}
		else if (name == Shaman::KeyEnemyShaman)
		{
			newEntity = Shaman::deserialize(&properties);
		}
		else if (name == SkeletonArcher::KeyEnemySkeletonArcher)
		{
			newEntity = SkeletonArcher::deserialize(&properties);
		}
		else if (name == SkeletonNecromancer::KeyEnemySkeletonNecromancer)
		{
			newEntity = SkeletonNecromancer::deserialize(&properties);
		}
		else if (name == SkeletonWarrior::KeyEnemySkeletonWarrior)
		{
			newEntity = SkeletonWarrior::deserialize(&properties);
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (name == BossWitch::KeyEnemyBossWitch)
		{
			newEntity = BossWitch::deserialize(&properties);
		}
		else if (name == Executioner::KeyEnemyExecutioner)
		{
			newEntity = Executioner::deserialize(&properties);
		}
		else if (name == Ghost::KeyEnemyGhost)
		{
			newEntity = Ghost::deserialize(&properties);
		}
		else if (name == Guard::KeyEnemyGuard)
		{
			newEntity = Guard::deserialize(&properties);
		}
		else if (name == Harpy::KeyEnemyHarpy)
		{
			newEntity = Harpy::deserialize(&properties);
		}
		else if (name == Jack::KeyEnemyJack)
		{
			newEntity = Jack::deserialize(&properties);
		}
		else if (name == Reaper::KeyEnemyReaper)
		{
			newEntity = Reaper::deserialize(&properties);
		}
		else if (name == SkeletonMage::KeyEnemySkeletonMage)
		{
			newEntity = SkeletonMage::deserialize(&properties);
		}
		else if (name == VampireLord::KeyEnemyVampireLord)
		{
			newEntity = VampireLord::deserialize(&properties);
		}
		else if (name == Vampiress::KeyEnemyVampiress)
		{
			newEntity = Vampiress::deserialize(&properties);
		}
		else if (name == Zombie::KeyEnemyZombie)
		{
			newEntity = Zombie::deserialize(&properties);
		}
		//////////////////
		// SNOW
		//////////////////
		else if (name == BossIceGolem::KeyEnemyBossIceGolem)
		{
			newEntity = BossIceGolem::deserialize(&properties);
		}
		else if (name == BossSanta::KeyEnemyBossSanta)
		{
			newEntity = BossSanta::deserialize(&properties);
		}
		else if (name == EvilSnowman::KeyEnemyEvilSnowman)
		{
			newEntity = EvilSnowman::deserialize(&properties);
		}
		else if (name == FrostDragon::KeyEnemyFrostDragon)
		{
			newEntity = FrostDragon::deserialize(&properties);
		}
		else if (name == FrostShooter::KeyEnemyFrostShooter)
		{
			newEntity = FrostShooter::deserialize(&properties);
		}
		else if (name == GoblinElf::KeyEnemyGoblinElf)
		{
			newEntity = GoblinElf::deserialize(&properties);
		}
		else if (name == IceGolem::KeyEnemyIceGolem)
		{
			newEntity = IceGolem::deserialize(&properties);
		}
		else if (name == TinyIceGolem::KeyEnemyTinyIceGolem)
		{
			newEntity = TinyIceGolem::deserialize(&properties);
		}
		else if (name == ToySoldierGoblin::KeyEnemyToySoldierGoblin)
		{
			newEntity = ToySoldierGoblin::deserialize(&properties);
		}
		else if (name == WaterElemental::KeyEnemyWaterElemental)
		{
			newEntity = WaterElemental::deserialize(&properties);
		}
		else if (name == Yeti::KeyEnemyYeti)
		{
			newEntity = Yeti::deserialize(&properties);
		}
		else if (name == YetiWarrior::KeyEnemyYetiWarrior)
		{
			newEntity = YetiWarrior::deserialize(&properties);
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (name == BossDemonKing::KeyEnemyBossDemonKing)
		{
			newEntity = BossDemonKing::deserialize(&properties);
		}
		else if (name == CritterDemon::KeyEnemyCritterDemon)
		{
			newEntity = CritterDemon::deserialize(&properties);
		}
		else if (name == DemonDragon::KeyEnemyDemonDragon)
		{
			newEntity = DemonDragon::deserialize(&properties);
		}
		else if (name == DemonGhost::KeyEnemyDemonGhost)
		{
			newEntity = DemonGhost::deserialize(&properties);
		}
		else if (name == DemonGrunt::KeyEnemyDemonGrunt)
		{
			newEntity = DemonGrunt::deserialize(&properties);
		}
		else if (name == DemonRogue::KeyEnemyDemonRogue)
		{
			newEntity = DemonRogue::deserialize(&properties);
		}
		else if (name == DemonShaman::KeyEnemyDemonShaman)
		{
			newEntity = DemonShaman::deserialize(&properties);
		}
		else if (name == DemonSwordsman::KeyEnemyDemonSwordsman)
		{
			newEntity = DemonSwordsman::deserialize(&properties);
		}
		else if (name == DemonWarrior::KeyEnemyDemonWarrior)
		{
			newEntity = DemonWarrior::deserialize(&properties);
		}
		else if (name == FireElemental::KeyEnemyFireElemental)
		{
			newEntity = FireElemental::deserialize(&properties);
		}
		else if (name == LavaGolem::KeyEnemyLavaGolem)
		{
			newEntity = LavaGolem::deserialize(&properties);
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (name == BossSkeletonKing::KeyEnemyBossSkeletonKing)
		{
			newEntity = BossSkeletonKing::deserialize(&properties);
		}
		else if (name == Abomination::KeyEnemyAbomination)
		{
			newEntity = Abomination::deserialize(&properties);
		}
		else if (name == BatDemon::KeyEnemyBatDemon)
		{
			newEntity = BatDemon::deserialize(&properties);
		}
		else if (name == DarkDragon::KeyEnemyDarkDragon)
		{
			newEntity = DarkDragon::deserialize(&properties);
		}
		else if (name == DemonArcher::KeyEnemyDemonArcher)
		{
			newEntity = DemonArcher::deserialize(&properties);
		}
		else if (name == SkeletonBaron::KeyEnemySkeletonBaron)
		{
			newEntity = SkeletonBaron::deserialize(&properties);
		}
		else if (name == SkeletonCleaver::KeyEnemySkeletonCleaver)
		{
			newEntity = SkeletonCleaver::deserialize(&properties);
		}
		else if (name == SkeletonKnight::KeyEnemySkeletonKnight)
		{
			newEntity = SkeletonKnight::deserialize(&properties);
		}
		else if (name == SkeletonPriestess::KeyEnemySkeletonPriestess)
		{
			newEntity = SkeletonPriestess::deserialize(&properties);
		}
		else if (name == Undead::KeyEnemyUndead)
		{
			newEntity = Undead::deserialize(&properties);
		}
		else if (name == VoidDemon::KeyEnemyVoidDemon)
		{
			newEntity = VoidDemon::deserialize(&properties);
		}
		//////////////////
		// MECH
		//////////////////
		else if (name == BossEvilEye::KeyEnemyBossEvilEye)
		{
			newEntity = BossEvilEye::deserialize(&properties);
		}
		else if (name == Exterminator::KeyEnemyExterminator)
		{
			newEntity = Exterminator::deserialize(&properties);
		}
		else if (name == MechBoxDrone::KeyEnemyMechBoxDrone)
		{
			newEntity = MechBoxDrone::deserialize(&properties);
		}
		else if (name == MechDog::KeyEnemyMechDog)
		{
			newEntity = MechDog::deserialize(&properties);
		}
		else if (name == MechGolem::KeyEnemyMechGolem)
		{
			newEntity = MechGolem::deserialize(&properties);
		}
		else if (name == MechGolemDark::KeyEnemyMechGolemDark)
		{
			newEntity = MechGolemDark::deserialize(&properties);
		}
		else if (name == MechGuard::KeyEnemyMechGuard)
		{
			newEntity = MechGuard::deserialize(&properties);
		}
		else if (name == MiteBot::KeyEnemyMiteBot)
		{
			newEntity = MiteBot::deserialize(&properties);
		}
		else if (name == Robot::KeyEnemyRobot)
		{
			newEntity = Robot::deserialize(&properties);
		}
		else if (name == VikingBot::KeyEnemyVikingBot)
		{
			newEntity = VikingBot::deserialize(&properties);
		}
		else if (name == VikingBotSmall::KeyEnemyVikingBotSmall)
		{
			newEntity = VikingBotSmall::deserialize(&properties);
		}
		else
		{
			CCLOG("Missing type on entity");
			return;
		}

		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
