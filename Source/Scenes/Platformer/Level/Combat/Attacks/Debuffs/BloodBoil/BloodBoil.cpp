#include "BloodBoil.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/BloodBoil/BloodBoilGenericPreview.h"
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

#define LOCAL_FUNC_ID_BLOOD_BOIL 1

const std::string BloodBoil::BloodBoilIdentifier = "blood-boil";
const std::string BloodBoil::HackIdentifierBloodBoil = "blood-boil";

const float BloodBoil::Duration = 60.0f;
const int BloodBoil::MaxMultiplier = 5;

BloodBoil* BloodBoil::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	BloodBoil* instance = new BloodBoil(caster, target);

	instance->autorelease();

	return instance;
}

BloodBoil::BloodBoil(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SkullGlowRed, AbilityType::Fire, BuffData(BloodBoil::Duration, BloodBoil::BloodBoilIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::RED);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

BloodBoil::~BloodBoil()
{
}

void BloodBoil::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void BloodBoil::initializePositions()
{
	super::initializePositions();
}

void BloodBoil::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_BLOOD_BOIL,
			HackableCode::HackableCodeInfo(
				BloodBoil::HackIdentifierBloodBoil,
				Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_BloodBoil::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_SkullGlowRed,
				LazyNode<HackablePreview>::create([=](){ return BloodBoilGenericPreview::create(); }),
				{ 
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_RegisterEax::create(), true
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_RegisterEbx::create(), true
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							ConstantString::create("movss xmm0, dword ptr [ebx]\n"),
							ConstantString::create("movss dword ptr [eax], xmm0\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_CommentHint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_RegisterEax::create()))
						})
						, // x64
						ConcatString::create({
							ConstantString::create("movss xmm0, dword ptr [rbx]\n"),
							ConstantString::create("movss dword ptr [rax], xmm0\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_CommentHint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_RegisterRax::create()))
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(BloodBoil::applyBloodBoil, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void BloodBoil::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyBloodBoil();

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * BloodBoil::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * BloodBoil::MaxMultiplier);
}

NO_OPTIMIZE void BloodBoil::applyBloodBoil()
{
	static volatile float currentDamageDealtLocal = 0;
	static volatile float fixedDamage = 0;
	static volatile float* currentDamageDealtLocalPtr = nullptr;
	static volatile float* fixedDamagePtr = nullptr;

	currentDamageDealtLocal = (float)Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	fixedDamage = 1.0f;
	fixedDamagePtr = &fixedDamage;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZBX);
	
	ASM_MOV_REG_VAR(ZAX, currentDamageDealtLocalPtr);
	ASM_MOV_REG_VAR(ZBX, fixedDamagePtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_BLOOD_BOIL);
	ASM(movss xmm0, dword ptr [ZBX]);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value((int)currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
