#include "EquipmentInventory.h"

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

using namespace cocos2d;

EquipmentInventory* EquipmentInventory::create(std::string saveKey, int capacity)
{
	EquipmentInventory* instance = new EquipmentInventory(saveKey, capacity);

	instance->autorelease();

	return instance;
}

EquipmentInventory::EquipmentInventory(std::string saveKey, int capacity) : super(saveKey, capacity)
{
}

EquipmentInventory::~EquipmentInventory()
{
}

void EquipmentInventory::onEnter()
{
	super::onEnter();
}

void EquipmentInventory::initializeListeners()
{
	super::initializeListeners();
}

std::map<std::string, int> EquipmentInventory::getCardKeyCount(Inventory* nonEquippedInventory)
{
	std::map<std::string, int> cardKeyCount = std::map<std::string, int>();

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<HexusCard*>(*it) != nullptr)
		{
			cardKeyCount[dynamic_cast<HexusCard*>(*it)->getCardKey()]++;
		}
	}

	if (nonEquippedInventory != nullptr)
	{
		for (auto item : nonEquippedInventory->getItems())
		{
			if (dynamic_cast<HexusCard*>(item) != nullptr)
			{
				cardKeyCount[dynamic_cast<HexusCard*>(item)->getCardKey()]++;
			}
		}
	}

	return cardKeyCount;
}

std::vector<Equipable*> EquipmentInventory::getEquipment()
{
	std::vector<Equipable*> equipment = std::vector<Equipable*>();

	for (auto next : this->items)
	{
		if (dynamic_cast<Equipable*>(next) != nullptr)
		{
			equipment.push_back(dynamic_cast<Equipable*>(next));
		}
	}

	return equipment;
}

Weapon* EquipmentInventory::getWeapon()
{
	for (auto next : this->items)
	{
		if (dynamic_cast<Weapon*>(next) != nullptr)
		{
			return dynamic_cast<Weapon*>(next);
		}
	}

	return nullptr;
}

Offhand* EquipmentInventory::getOffhand()
{
	for (auto next : this->items)
	{
		if (dynamic_cast<Offhand*>(next) != nullptr)
		{
			return dynamic_cast<Offhand*>(next);
		}
	}

	return nullptr;
}

Hat* EquipmentInventory::getHat()
{
	for (auto next : this->items)
	{
		if (dynamic_cast<Hat*>(next) != nullptr)
		{
			return dynamic_cast<Hat*>(next);
		}
	}

	return nullptr;
}

std::vector<Gear*> EquipmentInventory::getGear()
{
	std::vector<Gear*> gear = std::vector<Gear*>();

	for (auto next : this->items)
	{
		if (dynamic_cast<Gear*>(next) != nullptr)
		{
			gear.push_back(dynamic_cast<Gear*>(next));
		}
	}

	return gear;
}

std::vector<HexusCard*> EquipmentInventory::getHexusCards()
{
	std::vector<HexusCard*> cards = std::vector<HexusCard*>();

	for (auto next : this->items)
	{
		if (dynamic_cast<HexusCard*>(next) != nullptr)
		{
			cards.push_back(dynamic_cast<HexusCard*>(next));
		}
	}

	return cards;
}

int EquipmentInventory::getTotalMinAttack()
{
	int minAttack = 0;

	for (auto next : this->items)
	{
		if (dynamic_cast<Weapon*>(next) != nullptr)
		{
			minAttack += dynamic_cast<Weapon*>(next)->getMinAttack();
		}
	}

	return minAttack;
}

int EquipmentInventory::getTotalMaxAttack()
{
	int maxAttack = 0;

	for (auto next : this->items)
	{
		if (dynamic_cast<Weapon*>(next) != nullptr)
		{
			maxAttack += dynamic_cast<Weapon*>(next)->getMinAttack();
		}
	}

	return maxAttack;
}
