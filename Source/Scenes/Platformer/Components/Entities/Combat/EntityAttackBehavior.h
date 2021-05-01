#pragma once

#include "Engine/Components/Component.h"

class Consumable;
class EquipmentInventory;
class Inventory;
class PlatformerAttack;
class PlatformerEntity;

class EntityAttackBehavior : public Component
{
public:
	static EntityAttackBehavior* create(GameObject* owner);

	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> getAvailableAttacks();
	std::vector<PlatformerAttack*> getNoCostAttacks();
	std::vector<Consumable*> getAvailableConsumables();
	void registerAttack(PlatformerAttack* attack);
	std::tuple<int, int> computeAttackRange();

	static const float DefaultRecoverSpeed;
	static const float DefaultRecoverSpeedSlow;
	static const float DefaultRecoverSpeedVerySlow;
	static const std::string MapKey;

protected:
	EntityAttackBehavior(GameObject* owner);
	virtual ~EntityAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void buildEquipmentAttacks();
	void rebuildConsumables();

	EquipmentInventory* equipmentInventory;
	Inventory* inventory;

	PlatformerEntity* entity;
	cocos2d::Node* attacksNode;
	cocos2d::Node* consumablessNode;

	bool consumablesStale;

	std::vector<PlatformerAttack*> registeredAttacks;
	std::vector<Consumable*> registeredConsumables;
};
