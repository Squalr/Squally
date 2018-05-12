#include "EntityParser.h"

Layer* EntityParser::parse(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueVector entities = objectGroup->getObjects();

	// Create entities
	for (int index = 0; index < size(entities); index++)
	{
		if (entities[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap entity = entities[index].asValueMap();

		if (!GameUtils::keyExists(entity, "type") ||
			!GameUtils::keyExists(entity, "width") ||
			!GameUtils::keyExists(entity, "height") ||
			!GameUtils::keyExists(entity, "x") ||
			!GameUtils::keyExists(entity, "y"))
		{
			CCLOG("Missing properties on entity");
			continue;
		}

		string type = entity.at("type").asString();

		HackableObject* newEntity = nullptr;

		if (type == "spawn")
		{
			newEntity = Player::create();
		}
		else if (type == "knight")
		{
			newEntity = Knight::create();
		}
		//////////////////
		// JUNGLE
		//////////////////
		else if (type == "boss_rhinoman")
		{
			newEntity = BossRhinoman::create();
		}
		else if (type == "goblin_grunt")
		{
			newEntity = GoblinGrunt::create();
		}
		else if (type == "goblin_swordsman")
		{
			newEntity = GoblinSwordsman::create();
		}
		else if (type == "goblin_warrior")
		{
			newEntity = GoblinWarrior::create();
		}
		else if (type == "jungle_dragon")
		{
			newEntity = JungleDragon::create();
		}
		else if (type == "mantis")
		{
			newEntity = Mantis::create();
		}
		else if (type == "minotaur")
		{
			newEntity = Minotaur::create();
		}
		else if (type == "pig_demon")
		{
			newEntity = PigDemon::create();
		}
		else if (type == "purple_dinosaur")
		{
			newEntity = PurpleDinosaur::create();
		}
		else if (type == "tiki_golem")
		{
			newEntity = TikiGolem::create();
		}
		else if (type == "tiki_warrior")
		{
			newEntity = TikiWarrior::create();
		}
		//////////////////
		// RUINS
		//////////////////
		else if (type == "boss_egyptian_goddess")
		{
			newEntity = BossEgyptianGoddess::create();
		}
		else if (type == "anubis_tiny")
		{
			newEntity = AnubisTiny::create();
		}
		else if (type == "anubis_warrior")
		{
			newEntity = AnubisWarrior::create();
		}
		else if (type == "lioness")
		{
			newEntity = Lioness::create();
		}
		else if (type == "lion_man")
		{
			newEntity = LionMan::create();
		}
		else if (type == "medusa")
		{
			newEntity = Medusa::create();
		}
		else if (type == "medusa_small")
		{
			newEntity = MedusaSmall::create();
		}
		else if (type == "mermaid")
		{
			newEntity = Mermaid::create();
		}
		else if (type == "mummy_pharaoh")
		{
			newEntity = MummyPharaoh::create();
		}
		else if (type == "tiger_man")
		{
			newEntity = TigerMan::create();
		}
		else if (type == "tigress")
		{
			newEntity = Tigress::create();
		}
		//////////////////
		// FOREST
		//////////////////
		else if (type == "boss_dragon_orc_king")
		{
			newEntity = BossDragonOrcKing::create();
		}
		else if (type == "cyclops")
		{
			newEntity = Cyclops::create();
		}
		else if (type == "ent")
		{
			newEntity = Ent::create();
		}
		else if (type == "ent_mage")
		{
			newEntity = EntMage::create();
		}
		else if (type == "goblin_grunt_boar")
		{
			newEntity = GoblinGruntBoar::create();
		}
		else if (type == "goblin_guard")
		{
			newEntity = GoblinGuard::create();
		}
		else if (type == "goblin_shaman")
		{
			newEntity = GoblinShaman::create();
		}
		else if (type == "goblin_warrior_pig")
		{
			newEntity = GoblinWarriorPig::create();
		}
		else if (type == "orc_grunt")
		{
			newEntity = OrcGrunt::create();
		}
		else if (type == "orc_warrior")
		{
			newEntity = OrcWarrior::create();
		}
		else if (type == "troll")
		{
			newEntity = Troll::create();
		}
		//////////////////
		// CAVERNS
		//////////////////
		else if (type == "boss_krampus")
		{
			newEntity = BossKrampus::create();
		}
		else if (type == "black_widow")
		{
			newEntity = BlackWidow::create();
		}
		else if (type == "earth_elemental")
		{
			newEntity = EarthElemental::create();
		}
		else if (type == "earth_golem")
		{
			newEntity = EarthGolem::create();
		}
		else if (type == "forest_golem")
		{
			newEntity = ForestGolem::create();
		}
		else if (type == "genie")
		{
			newEntity = Genie::create();
		}
		else if (type == "rock_golem")
		{
			newEntity = RockGolem::create();
		}
		else if (type == "shaman")
		{
			newEntity = Shaman::create();
		}
		else if (type == "skeleton_archer")
		{
			newEntity = SkeletonArcher::create();
		}
		else if (type == "skeleton_necromancer")
		{
			newEntity = SkeletonNecromancer::create();
		}
		else if (type == "skeleton_warrior")
		{
			newEntity = SkeletonWarrior::create();
		}
		//////////////////
		// CASTLE
		//////////////////
		else if (type == "boss_witch")
		{
			newEntity = BossWitch::create();
		}
		else if (type == "executioner")
		{
			newEntity = Executioner::create();
		}
		else if (type == "ghost")
		{
			newEntity = Ghost::create();
		}
		else if (type == "guard")
		{
			newEntity = Guard::create();
		}
		else if (type == "harpy")
		{
			newEntity = Harpy::create();
		}
		else if (type == "jack")
		{
			newEntity = Jack::create();
		}
		else if (type == "reaper")
		{
			newEntity = Reaper::create();
		}
		else if (type == "skeleton_mage")
		{
			newEntity = SkeletonMage::create();
		}
		else if (type == "vampire_lord")
		{
			newEntity = VampireLord::create();
		}
		else if (type == "vampiress")
		{
			newEntity = Vampiress::create();
		}
		else if (type == "zombie")
		{
			newEntity = Zombie::create();
		}
		//////////////////
		// SNOW
		//////////////////
		else if (type == "boss_ice_golem")
		{
			newEntity = BossIceGolem::create();
		}
		else if (type == "boss_santa")
		{
			newEntity = BossSanta::create();
		}
		else if (type == "evil_snowman")
		{
			newEntity = EvilSnowman::create();
		}
		else if (type == "frost_dragon")
		{
			newEntity = FrostDragon::create();
		}
		else if (type == "frost_shooter")
		{
			newEntity = FrostShooter::create();
		}
		else if (type == "goblin_elf")
		{
			newEntity = GoblinElf::create();
		}
		else if (type == "ice_golem")
		{
			newEntity = IceGolem::create();
		}
		else if (type == "tiny_ice_golem")
		{
			newEntity = TinyIceGolem::create();
		}
		else if (type == "toy_soldier_goblin")
		{
			newEntity = ToySoldierGoblin::create();
		}
		else if (type == "water_elemental")
		{
			newEntity = WaterElemental::create();
		}
		else if (type == "yeti")
		{
			newEntity = Yeti::create();
		}
		else if (type == "yeti_warrior")
		{
			newEntity = YetiWarrior::create();
		}
		//////////////////
		// VOLCANO
		//////////////////
		else if (type == "boss_demon_king")
		{
			newEntity = BossDemonKing::create();
		}
		else if (type == "critter_demon")
		{
			newEntity = CritterDemon::create();
		}
		else if (type == "demon_dragon")
		{
			newEntity = DemonDragon::create();
		}
		else if (type == "demon_ghost")
		{
			newEntity = DemonGhost::create();
		}
		else if (type == "demon_grunt")
		{
			newEntity = DemonGrunt::create();
		}
		else if (type == "demon_rogue")
		{
			newEntity = DemonRogue::create();
		}
		else if (type == "demon_shaman")
		{
			newEntity = DemonShaman::create();
		}
		else if (type == "demon_swordsman")
		{
			newEntity = DemonSwordsman::create();
		}
		else if (type == "demon_warrior")
		{
			newEntity = DemonWarrior::create();
		}
		else if (type == "fire_elemental")
		{
			newEntity = FireElemental::create();
		}
		else if (type == "lava_golem")
		{
			newEntity = LavaGolem::create();
		}
		//////////////////
		// OBELISK
		//////////////////
		else if (type == "boss_skeleton_king")
		{
			newEntity = BossSkeletonKing::create();
		}
		else if (type == "dark_dragon")
		{
			newEntity = DarkDragon::create();
		}
		else if (type == "demon_archer")
		{
			newEntity = DemonArcher::create();
		}
		else if (type == "skeleton_baron")
		{
			newEntity = SkeletonBaron::create();
		}
		else if (type == "skeleton_cleaver")
		{
			newEntity = SkeletonCleaver::create();
		}
		else if (type == "skeleton_knight")
		{
			newEntity = SkeletonKnight::create();
		}
		else if (type == "skeleton_priestess")
		{
			newEntity = SkeletonPriestess::create();
		}
		else if (type == "undead")
		{
			newEntity = Undead::create();
		}
		else if (type == "void_demon")
		{
			newEntity = VoidDemon::create();
		}
		//////////////////
		// MECH
		//////////////////
		else if (type == "boss_evil_eye")
		{
			newEntity = BossEvilEye::create();
		}
		else if (type == "exterminator")
		{
			newEntity = Exterminator::create();
		}
		else if (type == "mech_box_drone")
		{
			newEntity = MechBoxDrone::create();
		}
		else if (type == "mech_golem")
		{
			newEntity = MechGolem::create();
		}
		else if (type == "mech_golem_dark")
		{
			newEntity = MechGolemDark::create();
		}
		else if (type == "mech_guard")
		{
			newEntity = MechGuard::create();
		}
		else if (type == "mite_bot")
		{
			newEntity = MiteBot::create();
		}
		else if (type == "robot")
		{
			newEntity = Robot::create();
		}
		else if (type == "viking_bot")
		{
			newEntity = VikingBot::create();
		}
		else if (type == "viking_bot_small")
		{
			newEntity = VikingBotSmall::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			continue;
		}

		newEntity->setPosition(Vec2(entity.at("x").asFloat() + entity.at("width").asFloat() / 2, entity.at("y").asFloat() + entity.at("height").asFloat() / 2));
		layer->addChild(newEntity);
	}

	return layer;
}
