#include "Manifest.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Manifest/ManifestGenericPreview.h"
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

#define LOCAL_FUNC_ID_MANIFEST 1

const std::string Manifest::ManifestIdentifier = "manifest";

const int Manifest::MinMultiplier = -1;
const int Manifest::MaxMultiplier = 2;
const int Manifest::DamageIncrease = 3; // Keep in sync with asm
const float Manifest::Duration = 12.0f;

Manifest* Manifest::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Manifest* instance = new Manifest(caster, target);

	instance->autorelease();

	return instance;
}

Manifest::Manifest(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Spirit, AbilityType::Shadow, BuffData(Manifest::Duration, Manifest::ManifestIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Manifest::~Manifest()
{
}

void Manifest::onEnter()
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

void Manifest::initializePositions()
{
	super::initializePositions();
}

void Manifest::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MANIFEST,
			HackableCode::HackableCodeInfo(
				Manifest::ManifestIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Manifest_Manifest::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Spirit,
				LazyNode<HackablePreview>::create([=](){ return ManifestGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_Manifest_RegisterEax::create()
					},
				},
			int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentCompareDamage::create()) + 
						"cmp dword ptr [eax], 0\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentJumpReduce::create()) + 
						"jne reduceDamage\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentElseSkip::create()) + 
						"jmp skipCode\n\n" +
						"reduceDamage:\n" +
						"mov dword ptr [eax], 0\n\n" +
						"skipCode:\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJne::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentNe::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentCompareDamage::create()) + 
						"cmp dword ptr [rax], 0\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentJumpReduce::create()) + 
						"jne reduceDamage\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Manifest_CommentElseSkip::create()) + 
						"jmp skipCode\n" +
						"reduceDamage:\n" +
						"mov dword ptr [rax], 0\n\n" +
						"skipCode:\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJne::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentNe::create())
					)
				},
				true
			)
		},
	};

	auto func = &Manifest::applyManifest;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Manifest::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyManifest();

	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Manifest::MinMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Manifest::MaxMultiplier);
	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
}

NO_OPTIMIZE void Manifest::applyManifest()
{
	static volatile int currentDamageDealt;
	static volatile int* currentDamagePtr;

	currentDamageDealt = 0;
	currentDamagePtr = &currentDamageDealt;
	
	ASM_PUSH_EFLAGS();
	ASM(push ZAX);

	ASM_MOV_REG_PTR(ZAX, currentDamagePtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MANIFEST);
	ASM(cmp dword ptr [ZAX], 0);
	ASM(jne manifestReduceDamage);
	ASM(jmp skipManifestCode);
	ASM(manifestReduceDamage:);
	ASM(mov dword ptr [ZAX], 0);
	ASM(skipManifestCode:);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealt);
}
END_NO_OPTIMIZE
