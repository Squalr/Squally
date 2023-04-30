#include "Parry.h"

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
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Parry/ParryGenericPreview.h"
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

#define LOCAL_FUNC_ID_STONE_SKIN 1

const std::string Parry::ParryIdentifier = "parry";

const int Parry::MaxMultiplier = 4;
const float Parry::Duration = 16.0f;

// Static to prevent GCC optimization issues
volatile int Parry::currentDamageTaken = 0;

Parry* Parry::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Parry* instance = new Parry(caster, target);

	instance->autorelease();

	return instance;
}

Parry::Parry(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldAdorned, AbilityType::Physical, BuffData(Parry::Duration, Parry::ParryIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Gray);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageTaken = 0;

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

Parry::~Parry()
{
}

void Parry::onEnter()
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

void Parry::initializePositions()
{
	super::initializePositions();
}

void Parry::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_STONE_SKIN,
			HackableCode::HackableCodeInfo(
				Parry::ParryIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Parry_Parry::create(),
				HackableBase::HackBarColor::Gray,
				UIResources::Menus_Icons_ShieldAdorned,
				LazyNode<HackablePreview>::create([=](){ return ParryGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Parry_RegisterEax::create()
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
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentTest::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zax)),
							ConstantString::create("test eax, eax\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentSkipParry::create(),
							ConstantString::create("jns skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentParry::create(),
							ConstantString::create("mov eax, 0\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJs::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentS::create()
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentTest::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zax)),
							ConstantString::create("test rax, rax\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentSkipParry::create(),
							ConstantString::create("jns skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Parry_CommentParry::create(),
							ConstantString::create("mov rax, 0\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJs::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentS::create()
						})
					)
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Parry::applyParry, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Parry::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->currentDamageTaken = damageOrHealing->damageOrHealingValue;

	this->applyParry();

	(*damageOrHealing->damageOrHealing) = this->currentDamageTaken;
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Parry::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Parry::MaxMultiplier);
}

NO_OPTIMIZE void Parry::applyParry()
{
	static volatile int currentDamageTakenLocal = 0;

	currentDamageTakenLocal = this->currentDamageTaken;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);

	ASM_MOV_REG_VAR(eax, currentDamageTakenLocal);
	ASM(DIV_CONVERT);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_STONE_SKIN);
	ASM(test ZAX, ZAX);
	ASM(js skipCode);
	ASM(mov ZAX, 0);
	ASM(skipCode:);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageTakenLocal, eax);

	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	this->currentDamageTaken = currentDamageTakenLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
