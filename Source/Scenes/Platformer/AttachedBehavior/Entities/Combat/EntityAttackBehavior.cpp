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
	this->registeredConsumables = std::vector<PlatformerAttack*>();
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

	for (auto it = this->registeredAttacks.begin(); it != this->registeredAttacks.end(); it++)
	{
		attacks.push_back(*it);
	}

	return attacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAvailableAttacks()
{
	std::vector<PlatformerAttack*> attacks = this->getAttacks();
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto it = attacks.begin(); it != attacks.end(); it++)
	{
		if ((*it)->getSpecialCost() <= this->entity->getStateOrDefaultInt(StateKeys::Mana, 0))
		{
			availableAttacks.push_back(*it);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getNoCostAttacks()
{
	std::vector<PlatformerAttack*> attacks = this->getAttacks();
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto it = attacks.begin(); it != attacks.end(); it++)
	{
		if ((*it)->getSpecialCost() <= 0)
		{
			availableAttacks.push_back(*it);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> EntityAttackBehavior::getAvailableConsumables()
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

		std::vector<Equipable*> equipment = equipmentInventory->getEquipment();

		for (auto it = equipment.begin(); it != equipment.end(); it++)
		{
			if (*it == nullptr)
			{
				continue;
			}
			
			std::vector<PlatformerAttack*> weaponAttacks = (*it)->cloneAssociatedAttacks();

			for (auto it = weaponAttacks.begin(); it != weaponAttacks.end(); it++)
			{
				this->registerAttack(*it);
			}
		}
	});
}

void EntityAttackBehavior::rebuildConsumables()
{
	this->registeredConsumables.clear();
	this->consumablessNode->removeAllChildren();
	this->consumablesStale = false;

	this->entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();
		
		if (inventory == nullptr)
		{
			return;
		}

		std::vector<Consumable*> consumables = inventory->getItemsOfType<Consumable>();

		for (auto it = consumables.begin(); it != consumables.end(); it++)
		{
			Consumable* item = *it;
			PlatformerAttack* consumable = item->cloneAssociatedAttack();

			consumable->registerAttackCompleteCallback([=]()
			{
				inventory->tryRemove(item);

				this->consumablesStale = true;
			});

			this->consumablessNode->addChild(consumable);
			this->registeredConsumables.push_back(consumable);
		}
	});
}
