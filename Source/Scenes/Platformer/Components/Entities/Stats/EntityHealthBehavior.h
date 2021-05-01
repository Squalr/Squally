#pragma once

#include "Engine/Components/Component.h"

class EquipmentInventory;
class PlatformerEntity;

class EntityHealthBehavior : public Component
{
public:
	static EntityHealthBehavior* create(GameObject* owner);

	int getHealth();
	void addHealth(int healthDelta);
	void setHealth(int health, bool checkDeath = true);
	int getMaxHealth();
	bool isAlive();
	bool isDead();
	virtual void kill(bool playAnimation = true);
	virtual void revive();

protected:
	EntityHealthBehavior(GameObject* owner);
	virtual ~EntityHealthBehavior();

	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity;

private:
	typedef Component super;

	int cachedMaxHealth;

	EquipmentInventory* equipmentInventory;
};
