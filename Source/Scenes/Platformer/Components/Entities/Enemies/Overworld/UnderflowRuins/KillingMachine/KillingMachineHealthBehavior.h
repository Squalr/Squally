#pragma once

#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"

class PlatformerEnemy;
class StatsBars;

class KillingMachineHealthBehavior : public EntityHealthBehavior
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
	typedef EntityHealthBehavior super;

	PlatformerEnemy* entity = nullptr;
	StatsBars* statsBars;
};
