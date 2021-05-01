#pragma once

#include "Engine/Components/Component.h"

class EquipmentInventory;
class PlatformerEntity;

class EntityManaBehavior : public Component
{
public:
	static EntityManaBehavior* create(GameObject* owner);

	int getMana();
	void addMana(int manaDelta);
	void setMana(int mana);
	int getMaxMana();

protected:
	EntityManaBehavior(GameObject* owner);
	virtual ~EntityManaBehavior();

	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity;

private:
	typedef Component super;

	void onRevive();

	int cachedMaxMana;
	
	EquipmentInventory* equipmentInventory;
};
