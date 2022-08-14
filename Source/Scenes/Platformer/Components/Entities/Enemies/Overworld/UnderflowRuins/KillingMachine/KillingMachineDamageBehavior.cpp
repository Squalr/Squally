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

	int machineId = GameUtils::getKeyOrDefault(this->entity->properties, KillingMachineDamageBehavior::PropertyMachineId, Value(0)).asInt();

	switch(machineId)
	{
		default:
		case 1:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
		case 2:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
		case 3:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
		case 4:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
		case 5:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
		case 6:
		{
			HackableCode::CodeInfoMap codeInfoMap =
			{
				{
					LOCAL_FUNC_ID_COMPARE_TEAM_1,
					HackableCode::HackableCodeInfo(
						KillingMachineDamageBehavior::HackIdentifierKillingMachineCompare1,
						Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
						HackableBase::HackBarColor::Purple,
						UIResources::Menus_Icons_ArrowRain,
						LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
						{
							{
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
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
								"cmp eax, 1\n"
								, // x64
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
								COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
									->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
								"cmp rax, 1\n"
							),
						},
						true
					)
				},
			};

			auto func = &KillingMachineDamageBehavior::compareDamage1;
			std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

			for (HackableCode* next : hackables)
			{
				this->entity->registerCode(next);
			}
			break;
		}
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

NO_OPTIMIZE void KillingMachineDamageBehavior::compareDamage1()
{
	static volatile int isOnEnemyTeamLocal;

	isOnEnemyTeamLocal = 1;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM(MOV ZAX, 0);
	ASM_MOV_REG_VAR(eax, isOnEnemyTeamLocal);

	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM_1);
	ASM(cmp ZAX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	// If the compare is true, set zax to 1, else 0
	ASM(MOV ZAX, 0);
	ASM(cmove ZAX, ZBX);

	ASM_MOV_VAR_REG(isOnEnemyTeamLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	// this->HackStateStorage[ArrowRain::StateKeyIsCasterOnEnemyTeam] = Value((isOnEnemyTeamLocal == 0) ? false : true);
}
END_NO_OPTIMIZE
