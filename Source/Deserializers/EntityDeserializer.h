#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Entities/Entities.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectDeserializer.h"

using namespace cocos2d;

class EntityDeserializer
{
public:
	static SerializableLayer* deserialize(TMXObjectGroup* objectGroup);

	static const std::string KeySpawnProperty;

	static const std::string KeyNpcKnight;

	static const std::string KeyEnemyBossRhinoman;
	static const std::string KeyEnemyGoblinGrunt;
	static const std::string KeyEnemyGoblinSwordsman;
	static const std::string KeyEnemyGoblinWarrior;
	static const std::string KeyEnemyJungleDragon;
	static const std::string KeyEnemyMantis;
	static const std::string KeyEnemyMinotaur;
	static const std::string KeyEnemyPigDemon;
	static const std::string KeyEnemyPurpleDinosaur;
	static const std::string KeyEnemyTikiGolem;
	static const std::string KeyEnemyTikiWarrior;

	static const std::string KeyEnemyBossEgyptianGoddess;
	static const std::string KeyEnemyAnubisTiny;
	static const std::string KeyEnemyAnubisWarrior;
	static const std::string KeyEnemyLioness;
	static const std::string KeyEnemyLionMan;
	static const std::string KeyEnemyMedusa;
	static const std::string KeyEnemyMedusaSmall;
	static const std::string KeyEnemyMermaid;
	static const std::string KeyEnemyMummyPharaoh;
	static const std::string KeyEnemyTigerMan;
	static const std::string KeyEnemyTigress;

	static const std::string KeyEnemyBossDragonOrcKing;
	static const std::string KeyEnemyCyclops;
	static const std::string KeyEnemyEnt;
	static const std::string KeyEnemyEntMage;
	static const std::string KeyEnemyGoblinGruntBoar;
	static const std::string KeyEnemyGoblinGuard;
	static const std::string KeyEnemyGoblinShaman;
	static const std::string KeyEnemyGoblinWarriorPig;
	static const std::string KeyEnemyOrcGrunt;
	static const std::string KeyEnemyOrcWarrior;
	static const std::string KeyEnemyTroll;

	static const std::string KeyEnemyBossKrampus;
	static const std::string KeyEnemyBlackWidow;
	static const std::string KeyEnemyEarthElemental;
	static const std::string KeyEnemyEarthGolem;
	static const std::string KeyEnemyForestGolem;
	static const std::string KeyEnemyGenie;
	static const std::string KeyEnemyRockGolem;
	static const std::string KeyEnemyShaman;
	static const std::string KeyEnemySkeletonArcher;
	static const std::string KeyEnemySkeletonNecromancer;
	static const std::string KeyEnemySkeletonWarrior;

	static const std::string KeyEnemyBossWitch;
	static const std::string KeyEnemyExecutioner;
	static const std::string KeyEnemyGhost;
	static const std::string KeyEnemyGuard;
	static const std::string KeyEnemyHarpy;
	static const std::string KeyEnemyJack;
	static const std::string KeyEnemyReaper;
	static const std::string KeyEnemySkeletonMage;
	static const std::string KeyEnemyVampireLord;
	static const std::string KeyEnemyVampiress;
	static const std::string KeyEnemyZombie;

	static const std::string KeyEnemyBossIceGolem;
	static const std::string KeyEnemyBossSanta;
	static const std::string KeyEnemyEvilSnowman;
	static const std::string KeyEnemyFrostDragon;
	static const std::string KeyEnemyFrostShooter;
	static const std::string KeyEnemyGoblinElf;
	static const std::string KeyEnemyIceGolem;
	static const std::string KeyEnemyTinyIceGolem;
	static const std::string KeyEnemyToySoldierGoblin;
	static const std::string KeyEnemyWaterElemental;
	static const std::string KeyEnemyYeti;
	static const std::string KeyEnemyYetiWarrior;

	static const std::string KeyEnemyBossDemonKing;
	static const std::string KeyEnemyCritterDemon;
	static const std::string KeyEnemyDemonDragon;
	static const std::string KeyEnemyDemonGhost;
	static const std::string KeyEnemyDemonGrunt;
	static const std::string KeyEnemyDemonRogue;
	static const std::string KeyEnemyDemonShaman;
	static const std::string KeyEnemyDemonSwordsman;
	static const std::string KeyEnemyDemonWarrior;
	static const std::string KeyEnemyFireElemental;
	static const std::string KeyEnemyLavaGolem;

	static const std::string KeyEnemyBossSkeletonKing;
	static const std::string KeyEnemyAbomination;
	static const std::string KeyEnemyBatDemon;
	static const std::string KeyEnemyDarkDragon;
	static const std::string KeyEnemyDemonArcher;
	static const std::string KeyEnemySkeletonBaron;
	static const std::string KeyEnemySkeletonCleaver;
	static const std::string KeyEnemySkeletonKnight;
	static const std::string KeyEnemySkeletonPriestess;
	static const std::string KeyEnemyUndead;
	static const std::string KeyEnemyVoidDemon;

	static const std::string KeyEnemyBossEvilEye;
	static const std::string KeyEnemyExterminator;
	static const std::string KeyEnemyMechBoxDrone;
	static const std::string KeyEnemyMechDog;
	static const std::string KeyEnemyMechGolem;
	static const std::string KeyEnemyMechGolemDark;
	static const std::string KeyEnemyMechGuard;
	static const std::string KeyEnemyMiteBot;
	static const std::string KeyEnemyRobot;
	static const std::string KeyEnemyVikingBot;
	static const std::string KeyEnemyVikingBotSmall;
};
