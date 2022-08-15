#include "KillingMachineDamageBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_COMPARE_TEAM_1 1
#define LOCAL_FUNC_ID_COMPARE_TEAM_2 2
#define LOCAL_FUNC_ID_COMPARE_TEAM_3 3
#define LOCAL_FUNC_ID_COMPARE_TEAM_4 4
#define LOCAL_FUNC_ID_COMPARE_TEAM_5 5
#define LOCAL_FUNC_ID_COMPARE_TEAM_6 6

const std::string KillingMachineDamageBehavior::MapKey = "killing-machine-damage-behavior";
const std::string KillingMachineDamageBehavior::PropertyMachineId = "machine-id";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1 = "killing-machine-compare-1";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare2 = "killing-machine-compare-2";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare3 = "killing-machine-compare-3";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare4 = "killing-machine-compare-4";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare5 = "killing-machine-compare-5";
const std::string KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare6 = "killing-machine-compare-6";
Value KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(0);
std::map<int, KillingMachineDamageBehavior::MachineAsmConstants> KillingMachineDamageBehavior::MachineAsmConstantsMap
{
	{ 1, KillingMachineDamageBehavior::MachineAsmConstants("cmovl", "eax", "rax", 50, 5, 4) },
	{ 2, KillingMachineDamageBehavior::MachineAsmConstants("cmovle", "ebx", "rbx", 75, 7, 5) },
	{ 3, KillingMachineDamageBehavior::MachineAsmConstants("cmove", "ecx", "rcx", 100, 1, 0) },
	{ 4, KillingMachineDamageBehavior::MachineAsmConstants("cmovne", "edx", "rdx", 125, 10, 10) },
	{ 5, KillingMachineDamageBehavior::MachineAsmConstants("cmovg", "edi", "rdi", 150, 15, 20) },
	{ 6, KillingMachineDamageBehavior::MachineAsmConstants("cmovge", "esi", "rsi", 175, 5, 8) },
};

KillingMachineDamageBehavior* KillingMachineDamageBehavior::create(GameObject* owner)
{
	KillingMachineDamageBehavior* instance = new KillingMachineDamageBehavior(owner);

	instance->autorelease();

	return instance;
}

KillingMachineDamageBehavior::KillingMachineDamageBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

KillingMachineDamageBehavior::~KillingMachineDamageBehavior()
{
}

void KillingMachineDamageBehavior::onLoad()
{
	super::onLoad();

	if (this->entity == nullptr)
	{
		return;
	}

	this->machineId = GameUtils::getKeyOrDefault(this->entity->properties, KillingMachineDamageBehavior::PropertyMachineId, Value(1)).asInt();
	int functionId = 0;
	void* functionPtr = nullptr;
	std::string icon = "";
	std::string functionIdentifier = "";
	KillingMachineDamageBehavior::MachineAsmConstants machineAsmConstants;
	LocalizedString* commandComment = nullptr;

	switch(this->machineId)
	{
		default:
		case 1:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_1;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1;
			icon = UIResources::Menus_Icons_Tools;
			auto func = &KillingMachineDamageBehavior::compareDamage1;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[1];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovle::create();

			// TODO: Equivalent of this
			/*
			COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
				->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
			COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
				->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
			*/
			break;
		}
		case 2:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_2;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare2;
			icon = UIResources::Menus_Icons_RobotArm;
			auto func = &KillingMachineDamageBehavior::compareDamage2;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[2];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovl::create();
			break;
		}
		case 3:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_3;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare3;
			icon = UIResources::Menus_Icons_Pickaxe;
			auto func = &KillingMachineDamageBehavior::compareDamage3;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[3];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmove::create();
			break;
		}
		case 4:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_4;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare4;
			icon = UIResources::Menus_Icons_Hammer;
			auto func = &KillingMachineDamageBehavior::compareDamage4;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[4];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovne::create();
			break;
		}
		case 5:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_5;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare5;
			icon = UIResources::Menus_Icons_HammerSmithing;
			auto func = &KillingMachineDamageBehavior::compareDamage5;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[5];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovg::create();
			break;
		}
		case 6:
		{
			functionId = LOCAL_FUNC_ID_COMPARE_TEAM_6;
			functionIdentifier = KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare6;
			icon = UIResources::Menus_Icons_GearBroken;
			auto func = &KillingMachineDamageBehavior::compareDamage6;
			functionPtr = (void*&)func;
			machineAsmConstants = KillingMachineDamageBehavior::MachineAsmConstantsMap[6];
			commandComment = Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovge::create();
			break;
		}
	}

	const std::string& command = machineAsmConstants.command;
	const std::string& reg32 = machineAsmConstants.reg32;
	const std::string& reg64 = machineAsmConstants.reg64;
	std::string constant1 = std::to_string(machineAsmConstants.constant1);
	std::string constant2 = std::to_string(machineAsmConstants.constant2);
	std::string constant3 = std::to_string(machineAsmConstants.constant3);

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			functionId,
			HackableCode::HackableCodeInfo(
				functionIdentifier,
				// TODO: Fix
				Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				icon,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						// TODO: Fix
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				15.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(commandComment) +
							"mov ebp, " + constant1 + "\n" +
							"mov " + reg32 + ", " + constant2 + "\n" +
							"cmp " + reg32 + ", " + constant3 + "\n" +
							command + " " + reg32 + ", ebp\n"
						, // x64
						COMMENT(commandComment == nullptr ? nullptr : commandComment->clone()) +
							"mov rbp, " + constant1 + "\n" +
							"mov " + reg64 + ", " + constant2 + "\n" +
							"cmp " + reg64 + ", " + constant3 + "\n" +
							command + " " + reg64 + ", rbp\n"
					),
				},
				true
			)
		},
	};

	std::vector<HackableCode*> hackables = HackableCode::create(functionPtr, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->entity->registerCode(next);
	}
}

void KillingMachineDamageBehavior::onDisable()
{
	super::onDisable();
}

HackablePreview* KillingMachineDamageBehavior::createDefaultPreview()
{
	return nullptr;
}

NO_OPTIMIZE int KillingMachineDamageBehavior::compare()
{
	switch(this->machineId)
	{
		default:
		case 1:
		{
			this->compareDamage1();
			break;
		}
		case 2:
		{
			this->compareDamage2();
			break;
		}
		case 3:
		{
			this->compareDamage3();
			break;
		}
		case 4:
		{
			this->compareDamage4();
			break;
		}
		case 5:
		{
			this->compareDamage5();
			break;
		}
		case 6:
		{
			this->compareDamage6();
			break;
		}
	}

	return KillingMachineDamageBehavior::DamageStorageAntiOptimize.asInt();
}
END_NO_OPTIMIZE

// Less than
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage1()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZAX, 0);
	ASM(cmp ZAX, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_1);
	ASM(mov ZBP, 50);
	ASM(mov ZAX, 5);
	ASM(cmp ZAX, 4);
	ASM(cmovl ZAX, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, eax);

	ASM(pop ZBP);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE

// Less than or equal
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage2()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZBX);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZBX, 0);
	ASM(cmp ZBX, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_2);
	ASM(mov ZBP, 75);
	ASM(mov ZBX, 7);
	ASM(cmp ZBX, 5);
	ASM(cmovle ZBX, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, ebx);

	ASM(pop ZBP);
	ASM(pop ZBX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE

// Equal
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage3()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZCX);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZCX, 0);
	ASM(cmp ZCX, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_3);
	ASM(mov ZBP, 100);
	ASM(mov ZCX, 1);
	ASM(cmp ZCX, 0);
	ASM(cmove ZCX, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, ecx);

	ASM(pop ZBP);
	ASM(pop ZCX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE

// Not equal
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage4()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZDX);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZDX, 0);
	ASM(cmp ZDX, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_4);
	ASM(mov ZBP, 125);
	ASM(mov ZDX, 10);
	ASM(cmp ZDX, 10);
	ASM(cmovne ZDX, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, edx);

	ASM(pop ZBP);
	ASM(pop ZDX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE

// Greater than
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage5()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZDI);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZDI, 0);
	ASM(cmp ZDI, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_5);
	ASM(mov ZBP, 150);
	ASM(mov ZDI, 15);
	ASM(cmp ZDI, 20);
	ASM(cmovg ZDI, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, edi);

	ASM(pop ZBP);
	ASM(pop ZDI);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE

// Greater than or equal
NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage6()
{
	static volatile int damage;

	damage = 0;

	ASM_PUSH_EFLAGS();
	ASM(push ZSI);
	ASM(push ZBP);
	
	// Create a cmp false result condition as the default behavior
	ASM(mov ZBP, 3);
	ASM(mov ZSI, 0);
	ASM(cmp ZSI, ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_6);
	ASM(mov ZBP, 175);
	ASM(mov ZSI, 5);
	ASM(cmp ZSI, 8);
	ASM(cmovge ZSI, ZBP);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damage, esi);

	ASM(pop ZBP);
	ASM(pop ZSI);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	KillingMachineDamageBehavior::DamageStorageAntiOptimize = Value(damage);
}
END_NO_OPTIMIZE
