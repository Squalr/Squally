#pragma once

#include "Engine/Components/GameComponent.h"

class EquipmentInventory;
class PlatformerEntity;

class EntityManaBehavior : public GameComponent
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

	PlatformerEntity* entity = nullptr;

private:
	typedef GameComponent super;

	void onRevive();

	int cachedMaxMana;
	
	EquipmentInventory* equipmentInventory;
};
