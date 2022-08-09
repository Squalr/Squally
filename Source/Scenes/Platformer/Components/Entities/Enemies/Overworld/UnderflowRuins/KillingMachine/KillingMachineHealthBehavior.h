#pragma once

#include "Scenes/Platformer/Components/Entities/Enemies/Stats/EnemyHealthBehavior.h"

class PlatformerEnemy;
class StatsBars;

class KillingMachineHealthBehavior : public EnemyHealthBehavior
{
public:
	static KillingMachineHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KillingMachineHealthBehavior(GameObject* owner);
	virtual ~KillingMachineHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EnemyHealthBehavior super;

	PlatformerEnemy* entity = nullptr;
	StatsBars* statsBars;
};
