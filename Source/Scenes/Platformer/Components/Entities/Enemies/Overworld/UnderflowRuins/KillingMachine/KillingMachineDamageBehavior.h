#pragma once

#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"

class HackablePreview;
class PlatformerEnemy;
class StatsBars;

class KillingMachineDamageBehavior : public EntityHealthBehavior
{
public:
	static KillingMachineDamageBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string HackIdentifierKillingMachineCompare1;
	static const std::string HackIdentifierKillingMachineCompare2;
	static const std::string HackIdentifierKillingMachineCompare3;
	static const std::string HackIdentifierKillingMachineCompare4;
	static const std::string HackIdentifierKillingMachineCompare5;
	static const std::string HackIdentifierKillingMachineCompare6;

protected:
	KillingMachineDamageBehavior(GameObject* owner);
	virtual ~KillingMachineDamageBehavior();

	void onLoad() override;
	void onDisable() override;
	HackablePreview* createDefaultPreview();

private:
	typedef EntityHealthBehavior super;

	void compareDamage1();

	static const std::string PropertyMachineId;
};
