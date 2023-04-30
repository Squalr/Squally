#include "SeekingBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/SeekingBlade/SeekingBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_SEEKING_BLADE 1

const std::string SeekingBlade::SeekingBladeIdentifier = "seeking-blade";
const std::string SeekingBlade::HackIdentifierSeekingBlade = "seeking-blade";

const int SeekingBlade::MaxMultiplier = 4;
const int SeekingBlade::CritDamage = 20; // Keep in sync with asm
const float SeekingBlade::Duration = 16.0f;

SeekingBlade* SeekingBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SeekingBlade* instance = new SeekingBlade(caster, target);

	instance->autorelease();

	return instance;
}

SeekingBlade::SeekingBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_DaggerGlowYellow, AbilityType::Fire, BuffData(SeekingBlade::Duration, SeekingBlade::SeekingBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

SeekingBlade::~SeekingBlade()
{
}

void SeekingBlade::onEnter()
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

void SeekingBlade::initializePositions()
{
	super::initializePositions();
}

void SeekingBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SEEKING_BLADE,
			HackableCode::HackableCodeInfo(
				SeekingBlade::HackIdentifierSeekingBlade,
				Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_SeekingBlade::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_DaggerGlowYellow,
				LazyNode<HackablePreview>::create([=](){ return SeekingBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_RegisterEax::create()
					},
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_RegisterEcx::create()
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
							ConstantString::create("cmp ecx, 1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentSet::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()),
							ConstantString::create("sete al\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_CommentHint1::create()
								->setStringReplacementVariables({ Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create(), Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create() })),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_CommentHint2::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))
						})
						, // x64
						ConcatString::create({
							ConstantString::create("cmp rcx, 1\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentSet::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()),
							ConstantString::create("sete al\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_CommentHint1::create()
								->setStringReplacementVariables({ Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create(), Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create() })),
							COMMENT(Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_CommentHint2::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create()))
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(SeekingBlade::applySeekingBlade, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void SeekingBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applySeekingBlade();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * SeekingBlade::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * SeekingBlade::MaxMultiplier);
}

NO_OPTIMIZE void SeekingBlade::applySeekingBlade()
{
	static volatile int rng = 0;
	static volatile float currentDamageDealtLocal = 0;
	static volatile float* currentDamageDealtLocalPtr = nullptr;

	rng = RandomHelper::random_int(0, 1);
	currentDamageDealtLocal = (float)Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZCX);

	ASM(mov ZAX, 0);
	ASM(mov ZCX, 0);

	ASM_MOV_REG_VAR(ecx, rng);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SEEKING_BLADE);
	ASM(cmp ZCX, 1);
	ASM(sete al);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(rng, eax);

	ASM(pop ZCX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	currentDamageDealtLocal = rng == 1 ? SeekingBlade::CritDamage : currentDamageDealtLocal;

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value((int)currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
