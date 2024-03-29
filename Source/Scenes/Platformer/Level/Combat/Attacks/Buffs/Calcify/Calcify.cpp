#include "Calcify.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Calcify/CalcifyGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_CALCIFY 1

const std::string Calcify::CalcifyIdentifier = "calcify";
const std::string Calcify::HackIdentifierCalcify = "calcify";

const int Calcify::MaxMultiplier = 4;
const int Calcify::DamageReduction = 3; // Keep in sync with asm
const float Calcify::Duration = 16.0f;

Calcify* Calcify::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Calcify* instance = new Calcify(caster, target);

	instance->autorelease();

	return instance;
}

Calcify::Calcify(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Bone, AbilityType::Physical, BuffData(Calcify::Duration, Calcify::CalcifyIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

Calcify::~Calcify()
{
}

void Calcify::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->bubble->runAction(FadeTo::create(0.25f, 255));

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Calcify::initializePositions()
{
	super::initializePositions();
}

void Calcify::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CALCIFY,
			HackableCode::HackableCodeInfo(
				Calcify::HackIdentifierCalcify,
				Strings::Menus_Hacking_Abilities_Buffs_Calcify_Calcify::create(),
				HackableBase::HackBarColor::Teal,
				UIResources::Menus_Icons_Bone,
				LazyNode<HackablePreview>::create([=](){ return CalcifyGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Calcify_RegisterEax::create(), HackableDataType::Int32, true
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_Calcify_RegisterEbx::create(), HackableDataType::Int32, true
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentLoadDamage::create()),
							ConstantString::create("movss xmm0, dword ptr [eax]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentLoadDivisor::create()),
							ConstantString::create("movss xmm1, dword ptr [ebx]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentDivide::create()),
							ConstantString::create("divss xmm0, xmm1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentStore::create()),
							ConstantString::create("movss dword ptr [eax], xmm0\n")
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentLoadDamage::create()),
							ConstantString::create("movss xmm0, dword ptr [rax]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentLoadDivisor::create()),
							ConstantString::create("movss xmm1, dword ptr [rbx]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentDivide::create()),
							ConstantString::create("divss xmm0, xmm1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Calcify_CommentStore::create()),
							ConstantString::create("movss dword ptr [rax], xmm0\n")
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Calcify::applyCalcify, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Calcify::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(damageOrHealing->damageOrHealingValue);

	this->applyCalcify();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Calcify::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Calcify::MaxMultiplier);
}

NO_OPTIMIZE void Calcify::applyCalcify()
{
	static volatile float currentDamageTakenLocal = 0;
	static volatile float divideByLocal = 0;
	static volatile float* currentDamageTakenLocalPtr = nullptr;
	static volatile float* divideByLocalPtr = nullptr;

	currentDamageTakenLocal = (float)Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	currentDamageTakenLocalPtr = &currentDamageTakenLocal;
	divideByLocal = 3.0f;
	divideByLocalPtr = &divideByLocal;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, currentDamageTakenLocalPtr);
	ASM_MOV_REG_VAR(ZBX, divideByLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CALCIFY);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM(movss xmm1, dword ptr [ZBX]);
	ASM(divss xmm0, xmm1);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
