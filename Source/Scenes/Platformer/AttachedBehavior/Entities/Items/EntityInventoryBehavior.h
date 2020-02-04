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

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityInventoryBehavior(GameObject* owner);
	virtual ~EntityInventoryBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	Inventory* inventory;
	EquipmentInventory* equipmentInventory;
	CurrencyInventory* currencyInventory;

	PlatformerEntity* platformerEntity;
};
