#include "Melt.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Melt/MeltGenericPreview.h"
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

#define LOCAL_FUNC_ID_MELT 1

const std::string Melt::MeltIdentifier = "melt";
const std::string Melt::HackIdentifierMelt = "melt";

const int Melt::MaxMultiplier = 4;
const float Melt::Duration = 16.0f;

Melt* Melt::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Melt* instance = new Melt(caster, target);

	instance->autorelease();

	return instance;
}

Melt::Melt(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_FlamingScroll, AbilityType::Fire, BuffData(Melt::Duration, Melt::MeltIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Melt::~Melt()
{
}

void Melt::onEnter()
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

void Melt::initializePositions()
{
	super::initializePositions();
}

void Melt::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MELT,
			HackableCode::HackableCodeInfo(
				Melt::HackIdentifierMelt,
				Strings::Menus_Hacking_Abilities_Debuffs_Melt_Melt::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_FlamingScroll,
				LazyNode<HackablePreview>::create([=](){ return MeltGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_Melt_RegisterEax::create()
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Melt_RegisterEdx::create()
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
							ConstantString::create("cmp edx, 1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentSet::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()),
							ConstantString::create("setne al\n"),
							ConstantString::create("neg eax\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Melt_CommentHint1::create()
								->setStringReplacementVariables({ Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create(), Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdx::create() })),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Melt_CommentHint2::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))
						})
						, // x64
						ConcatString::create({
							ConstantString::create("cmp rdx, 1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentSet::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()),
							ConstantString::create("setne al\n"),
							ConstantString::create("neg rax\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Melt_CommentHint1::create()
								->setStringReplacementVariables({ Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create(), Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdx::create() })),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Melt_CommentHint2::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create()))
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Melt::applyMelt, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Melt::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyMelt();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Melt::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Melt::MaxMultiplier);
}

NO_OPTIMIZE void Melt::applyMelt()
{
	static volatile int constZero = 0;
	static volatile int multiplier = 0;
	static volatile int currentDamageDealtLocal = 0;

	constZero = 0;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZDX);

	ASM(mov ZAX, 0);
	ASM(mov ZDX, 0);

	ASM_MOV_REG_VAR(edx, constZero);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MELT);
	ASM(cmp ZDX, 1);
	ASM(setne al);
	ASM(neg ZAX)
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(multiplier, eax);

	ASM(pop ZDX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = currentDamageDealtLocal * multiplier;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
