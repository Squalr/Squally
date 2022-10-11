#pragma once

#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"

#include "Engine/Hackables/HackableCode.h"

class HackablePreview;
class PlatformerEnemy;
class StatsBars;

namespace cocos2d
{
	class Value;
}

class KillingMachineDamageBehavior : public EntityHealthBehavior
{
public:
	static KillingMachineDamageBehavior* create(GameObject* owner);

	int compare();

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
	void compareDamage2();
	void compareDamage3();
	void compareDamage4();
	void compareDamage5();
	void compareDamage6();

	int machineId = -1;

	struct MachineAsmConstants
	{
		std::string command;
		HackableCode::Register reg = HackableCode::Register::zax;
		int probabilityConstant = 0;

		MachineAsmConstants() { }
		MachineAsmConstants(std::string command, HackableCode::Register reg, int probabilityConstant) :
			command(command), reg(reg), probabilityConstant(probabilityConstant) { }
	};

	static const std::string PropertyMachineId;
	static cocos2d::Value DamageStorageAntiOptimize;
	static std::map<int, MachineAsmConstants> MachineAsmConstantsMap;

	static const int DefaultDamage;
	static const int CritDamage;
};
