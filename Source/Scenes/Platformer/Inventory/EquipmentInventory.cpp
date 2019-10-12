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
		std::vector<Item*> items = nonEquippedInventory->getItems();
		
		for (auto it = items.begin(); it != items.end(); it++)
		{
			if (dynamic_cast<HexusCard*>(*it) != nullptr)
			{
				cardKeyCount[dynamic_cast<HexusCard*>(*it)->getCardKey()]++;
			}
		}
	}

	return cardKeyCount;
}

std::vector<Equipable*> EquipmentInventory::getEquipment()
{
	std::vector<Equipable*> equipment = std::vector<Equipable*>();

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Equipable*>(*it) != nullptr)
		{
			equipment.push_back(dynamic_cast<Equipable*>(*it));
		}
	}

	return equipment;
}

Weapon* EquipmentInventory::getWeapon()
{
	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Weapon*>(*it) != nullptr)
		{
			return dynamic_cast<Weapon*>(*it);
		}
	}

	return nullptr;
}

Offhand* EquipmentInventory::getOffhand()
{
	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Offhand*>(*it) != nullptr)
		{
			return dynamic_cast<Offhand*>(*it);
		}
	}

	return nullptr;
}

Hat* EquipmentInventory::getHat()
{
	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Hat*>(*it) != nullptr)
		{
			return dynamic_cast<Hat*>(*it);
		}
	}

	return nullptr;
}

std::vector<Gear*> EquipmentInventory::getGear()
{
	std::vector<Gear*> gear = std::vector<Gear*>();

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Gear*>(*it) != nullptr)
		{
			gear.push_back(dynamic_cast<Gear*>(*it));
		}
	}

	return gear;
}

std::vector<HexusCard*> EquipmentInventory::getHexusCards()
{
	std::vector<HexusCard*> cards = std::vector<HexusCard*>();

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<HexusCard*>(*it) != nullptr)
		{
			cards.push_back(dynamic_cast<HexusCard*>(*it));
		}
	}

	return cards;
}

int EquipmentInventory::getTotalMinAttack()
{
	int minAttack = 0;

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Weapon*>(*it) != nullptr)
		{
			minAttack += dynamic_cast<Weapon*>(*it)->getMinAttack();
		}
	}

	return minAttack;
}

int EquipmentInventory::getTotalMaxAttack()
{
	int maxAttack = 0;

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Weapon*>(*it) != nullptr)
		{
			maxAttack += dynamic_cast<Weapon*>(*it)->getMinAttack();
		}
	}

	return maxAttack;
}

int EquipmentInventory::getTotalDefense()
{
	int defense = 0;

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		if (dynamic_cast<Gear*>(*it) != nullptr)
		{
			defense += dynamic_cast<Gear*>(*it)->getDefense();
		}
	}

	return defense;
}
