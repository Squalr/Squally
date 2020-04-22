#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CurrencyInventory;
class EquipmentInventory;
class Inventory;
class PlatformerEntity;

class EntityInventoryBehavior : public AttachedBehavior
{
public:
	static EntityInventoryBehavior* create(GameObject* owner);

	std::vector<Inventory*> getAllInventories();
	Inventory* getInventory();
	EquipmentInventory* getEquipmentInventory();
	CurrencyInventory* getCurrencyInventory();

	void redirectInventoryTo(Inventory* inventory);

	static const std::string MapKey;

protected:
	EntityInventoryBehavior(GameObject* owner, std::string inventorySaveKey = "", std::string equipmentSaveKey = "", std::string currencySaveKey = "");
	virtual ~EntityInventoryBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;
	
	Inventory* inventory;
	EquipmentInventory* equipmentInventory;
	CurrencyInventory* currencyInventory;

	PlatformerEntity* platformerEntity;
};
