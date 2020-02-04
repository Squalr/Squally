#include "EntityAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityAttackBehavior::MapKeyAttachedBehavior = "entity-attacks";
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

	this->registeredAttacks = std::vector<PlatformerAttack*>();
	this->registeredConsumables = std::vector<Consumable*>();
	this->attacksNode = Node::create();
	this->consumablessNode = Node::create();
	this->consumablesStale = true;

	this->addChild(this->attacksNode);
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
	this->buildEquipmentAttacks();
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAttacks()
{
	std::vector<PlatformerAttack*> attacks = std::vector<PlatformerAttack*>();

	for (auto attack : this->registeredAttacks)
	{
		attacks.push_back(attack);
	}

	return attacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAvailableAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto attack : this->getAttacks())
	{
		if (attack->getSpecialCost() <= this->entity->getStateOrDefaultInt(StateKeys::Mana, 0))
		{
			availableAttacks.push_back(attack);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getNoCostAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto attack : this->getAttacks())
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
	
	this->attacksNode->addChild(attack);
	this->registeredAttacks.push_back(attack);
}

void EntityAttackBehavior::buildEquipmentAttacks()
{
	this->entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		EquipmentInventory* equipmentInventory = entityInventoryBehavior->getEquipmentInventory();

		if (equipmentInventory == nullptr)
		{
			return;
		}
		
		for (auto equipable : equipmentInventory->getEquipment())
		{
			if (equipable == nullptr)
			{
				continue;
			}

			for (auto attack : equipable->cloneAssociatedAttacks())
			{
				this->registerAttack(attack);
			}
		}
	});
}

void EntityAttackBehavior::rebuildConsumables()
{
	this->registeredConsumables.clear();
	this->consumablessNode->removeAllChildren();

	// Disabled due to refactor. Only reinstate if this causes perf issues.
	// this->consumablesStale = false;

	this->entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();
		
		if (inventory == nullptr)
		{
			return;
		}

		this->registeredConsumables = inventory->getItemsOfType<Consumable>();
	});
}
