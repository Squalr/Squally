#include "EntityAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
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
}

EntityAttackBehavior::~EntityAttackBehavior()
{
}

void EntityAttackBehavior::initializePositions()
{
}

void EntityAttackBehavior::onLoad()
{
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
		if ((*it)->getSpecialCost() <= this->getStateOrDefaultInt(StateKeys::Mana, 0))
		{
			availableAttacks.push_back(*it);
		}
	}

	return availableAttacks;
}

void EntityAttackBehavior::registerAttack(PlatformerAttack* attack)
{
	if (attack == nullptr)
	{
		return;
	}
	
	this->addChild(attack);
	this->registeredAttacks.push_back(attack);
}

void EntityAttackBehavior::buildEquipmentAttacks()
{
	EquipmentInventory* equipmentInventory = this->entity->getEquipmentInventory();

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
		
		std::vector<PlatformerAttack*> weaponAttacks = (*it)->createAssociatedAttacks();

		for (auto it = weaponAttacks.begin(); it != weaponAttacks.end(); it++)
		{
			this->registerAttack(*it);
		}
	}
}
