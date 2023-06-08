#include "EntityAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityAttackBehavior::MapKey = "entity-attacks";
const float EntityAttackBehavior::DefaultRecoverSpeed = 1.0f;
const float EntityAttackBehavior::DefaultRecoverSpeedSlow = 1.5f;
const float EntityAttackBehavior::DefaultRecoverSpeedVerySlow = 2.0f;

EntityAttackBehavior* EntityAttackBehavior::create(GameObject* owner)
{
	EntityAttackBehavior* instance = new EntityAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityAttackBehavior::EntityAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->attacksNode = Node::create();
	this->defensivesNode = Node::create();
	this->consumablessNode = Node::create();

	this->toggleQueryable(false);

	this->addChild(this->attacksNode);
	this->addChild(this->defensivesNode);
	this->addChild(this->consumablessNode);
}

EntityAttackBehavior::~EntityAttackBehavior()
{
}

void EntityAttackBehavior::initializePositions()
{
}

void EntityAttackBehavior::onLoad()
{
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->inventory = entityInventoryBehavior->getInventory();
		this->equipmentInventory = entityInventoryBehavior->getEquipmentInventory();
		
		this->buildEquipmentAttacks();

		this->toggleQueryable(true);
	});
}

void EntityAttackBehavior::onDisable()
{
	super::onDisable();
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAttacks()
{
	std::vector<PlatformerAttack*> attacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->registeredAttacks)
	{
		attacks.push_back(attack);
	}

	return attacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAvailableAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->getAttacks())
	{
		if (attack->getSpecialCost() <= this->entity->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0))
		{
			availableAttacks.push_back(attack);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getNoCostAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->getAttacks())
	{
		if (attack->getSpecialCost() <= 0)
		{
			availableAttacks.push_back(attack);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getDefensives()
{
	std::vector<PlatformerAttack*> attacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->registeredDefensives)
	{
		attacks.push_back(attack);
	}

	return attacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAvailableDefensives()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->getDefensives())
	{
		if (attack->getSpecialCost() <= this->entity->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0))
		{
			availableAttacks.push_back(attack);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getNoCostDefensives()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (PlatformerAttack* attack : this->getDefensives())
	{
		if (attack->getSpecialCost() <= 0)
		{
			availableAttacks.push_back(attack);
		}
	}

	return availableAttacks;
}

std::vector<Consumable*> EntityAttackBehavior::getAvailableConsumables()
{
	if (this->consumablesStale)
	{
		this->rebuildConsumables();
	}

	return this->registeredConsumables;
}

void EntityAttackBehavior::registerAttack(PlatformerAttack* attack)
{
	if (attack == nullptr)
	{
		return;
	}

	attack->owner = this->entity;
	
	this->attacksNode->addChild(attack);
	this->registeredAttacks.push_back(attack);
}

void EntityAttackBehavior::registerDefensive(PlatformerAttack* defensive)
{
	if (defensive == nullptr)
	{
		return;
	}

	defensive->owner = this->entity;
	
	this->defensivesNode->addChild(defensive);
	this->registeredDefensives.push_back(defensive);
}

void EntityAttackBehavior::buildEquipmentAttacks()
{
	if (this->equipmentInventory == nullptr)
	{
		return;
	}

	for (Equipable* equipable : this->equipmentInventory->getEquipment())
	{
		if (equipable == nullptr)
		{
			continue;
		}

		for (PlatformerAttack* attack : equipable->cloneAssociatedAttacks())
		{
			this->registerAttack(attack);
		}
	}
}

void EntityAttackBehavior::rebuildConsumables()
{
	this->registeredConsumables.clear();
	this->consumablessNode->removeAllChildren();

	// Disabled due to refactor. Only reinstate if this causes perf issues.
	// this->consumablesStale = false;

	if (this->inventory != nullptr)
	{
		this->registeredConsumables = inventory->getItemsOfType<Consumable>();
	}
}

std::tuple<int, int> EntityAttackBehavior::computeAttackRange()
{
	const int DefaultMinAttack = 3;
	const int DefaultMaxAttack = 5;

	int minAttack = DefaultMinAttack;
	int maxAttack = DefaultMaxAttack;

	if (this->equipmentInventory != nullptr)
	{
		Weapon* weapon = this->equipmentInventory->getWeapon();

		minAttack = weapon == nullptr ? minAttack : weapon->getMinAttack();
		maxAttack = weapon == nullptr ? maxAttack : weapon->getMaxAttack();
	}

	return std::make_tuple(minAttack, maxAttack);
}
