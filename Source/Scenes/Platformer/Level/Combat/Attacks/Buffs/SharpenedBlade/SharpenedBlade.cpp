#include "SharpenedBlade.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/SharpenedBlade/SharpenedBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string SharpenedBlade::SharpenedBladeIdentifier = "sharpened-blade";
const std::string SharpenedBlade::HackIdentifierSharpenedBlade = "sharpened-blade";

const int SharpenedBlade::MaxMultiplier = 4;
const float SharpenedBlade::Duration = 20.0f;

SharpenedBlade* SharpenedBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SharpenedBlade* instance = new SharpenedBlade(caster, target);

	instance->autorelease();

	return instance;
}

SharpenedBlade::SharpenedBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordAlt, AbilityType::Physical, BuffData(SharpenedBlade::Duration, SharpenedBlade::SharpenedBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

SharpenedBlade::~SharpenedBlade()
{
}

void SharpenedBlade::onEnter()
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

void SharpenedBlade::initializePositions()
{
	super::initializePositions();
}

void SharpenedBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				SharpenedBlade::HackIdentifierSharpenedBlade,
				Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_SharpenedBlade::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_SwordAlt,
				LazyNode<HackablePreview>::create([=](){ return SharpenedBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_RegisterEax::create(),
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_RegisterEbx::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentMinDamage::create()) +
						"mov ebx, 7\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentCompare::create()) +
						"cmp eax, ebx\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentConditionalMov::create()) +
						"cmovle eax, ebx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovle::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentLe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentFinale::create()
							->setStringReplacementVariables({
								Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create(),
								Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create(),
							})) +
						"\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentHint::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))
						
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentMinDamage::create()) +
						"mov rbx, 7\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentCompare::create()) +
						"cmp rax, rbx\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentConditionalMov::create()) +
						"cmovle rax, rbx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovle::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentLe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentFinale::create()
							->setStringReplacementVariables({
								Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create(),
								Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create(),
							})) +
						"\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_CommentHint::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create()))
					),
				},
				true
			)
		},
	};

	auto func = &SharpenedBlade::applySharpenedBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void SharpenedBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applySharpenedBlade();

	// Bound multiplier in either direction
	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(MathUtils::clamp(
		this->HackStateStorage[Buff::StateKeyDamageDealt].asInt(),
		-std::abs(this->HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * SharpenedBlade::MaxMultiplier),
		std::abs(this->HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * SharpenedBlade::MaxMultiplier)
	));

	*(int*)(GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
}

NO_OPTIMIZE void SharpenedBlade::applySharpenedBlade()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(eax, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(mov ZBX, 7);
	ASM(cmp ZAX, ZBX);
	ASM(cmovle ZAX, ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
