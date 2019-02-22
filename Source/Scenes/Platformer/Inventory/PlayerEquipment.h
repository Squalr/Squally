#pragma once

#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

class PlayerEquipment : public EquipmentInventory
{
public:
	static PlayerEquipment* getInstance();

protected:
	PlayerEquipment();
	virtual ~PlayerEquipment();
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef EquipmentInventory super;

	static PlayerEquipment* instance;
	static const std::string SaveKeyPlayerEquipment;
};
