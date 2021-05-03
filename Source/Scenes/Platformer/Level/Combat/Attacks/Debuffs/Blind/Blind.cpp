#include "Blind.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/BlindGenericPreview.h"
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

#define LOCAL_FUNC_ID_BLIND 1

const std::string Blind::BlindIdentifier = "blind";

const float Blind::Duration = 60.0f;
const int Blind::DamageDealt = 20;

Blind* Blind::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Blind* instance = new Blind(caster, target);

	instance->autorelease();

	return instance;
}

Blind::Blind(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_RuneGreen, AbilityType::Physical, BuffData(Blind::Duration, Blind::BlindIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Blind::~Blind()
{
}

void Blind::onEnter()
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

void Blind::initializePositions()
{
	super::initializePositions();
}

void Blind::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_BLIND,
			HackableCode::HackableCodeInfo(
				Blind::BlindIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Blind_Blind::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_RuneGreen,
				LazyNode<HackablePreview>::create([=](){ return BlindGenericPreview::create(); }),
				{
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"xor edi, edi\n"
						, // x64
						"xor rdi, rdi\n"
					),
				},
				true
			)
		},
	};

	auto func = &Blind::applyBlind;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Blind::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyBlind();

	*(int*)(GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer())
		= GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
}

NO_OPTIMIZE void Blind::applyBlind()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = 0;

	ASM(push ZDI);
	ASM_MOV_REG_VAR(edx, currentDamageDealtLocal);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_BLIND);
	ASM(xor ZDI, ZDI);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(currentDamageDealtLocal, edi);
	ASM(pop ZDI);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
