#include "Flurry.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FLURRY 11

const int Flurry::LowerBoundHits = 1;
const int Flurry::MinHits = 2;
const int Flurry::MaxHits = 4;

Flurry* Flurry::create(float attackDuration, float recoverDuration, Priority priority)
{
	Flurry* instance = new Flurry(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

Flurry::Flurry(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_SwordSlash, priority, 2, 3, 0, attackDuration, recoverDuration)
{
	this->slashSounds = std::vector<WorldSound*>();
	this->hitSounds = std::vector<WorldSound*>();
	this->hits = Flurry::LowerBoundHits;

	for (int index = 0; index < Flurry::MaxHits; index++)
	{
		switch (index % 3)
		{
			default: case 0: { this->slashSounds.push_back(WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingBlade1)); }
			case 1: { this->slashSounds.push_back(WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingBlade2)); }
			case 2: { this->slashSounds.push_back(WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingBlade3)); }
		}
		
		this->hitSounds.push_back(WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1));
	}

	for (auto next : this->slashSounds)
	{
		this->addChild(next);
	}

	for (auto next : this->hitSounds)
	{
		this->addChild(next);
	}
}

Flurry::~Flurry()
{
}

PlatformerAttack* Flurry::cloneInternal()
{
	return Flurry::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* Flurry::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

void Flurry::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FLURRY,
			HackableCode::HackableCodeInfo(
				"Flurry",
				Strings::Menus_Hacking_Abilities_TrainingDummy_AddHealth::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_SwordSlash,
				nullptr,
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_TrainingDummy_RegisterEdi::create() }
				},
				int(HackFlags::None),
				8.0f,
				0.0f
			)
		},
	};

	auto hitsFunc = &Flurry::setRandomHits;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)hitsFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->owner->registerCode(next);
	}
}

std::string Flurry::getAttackAnimation()
{
	return "Attack";
}

void Flurry::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();

	this->setRandomHits();
	
	for (int index = 0; index < this->hits; index++)
	{
		this->slashSounds[index]->play(false, this->attackDuration / 2.0f + float(index) * this->attackDuration);
	}
}

void Flurry::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (int index = 0; index < this->hits; index++)
	{
		for (auto next : targets)
		{
			this->runAction(Sequence::create(
				DelayTime::create(float(index) * this->attackDuration),
				CallFunc::create([=]()
				{
					this->hitSounds[index]->play(false);
					this->doDamageOrHealing(owner, next);
				}),
				nullptr
			));
		}
	}
}

void Flurry::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}

NO_OPTIMIZE void Flurry::setRandomHits()
{
	volatile int minHits = Flurry::MinHits;
	volatile int maxHits = Flurry::MaxHits;

	ASM(push ZSI);
	ASM(push ZDI);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FLURRY);
	ASM(mov ZSI, 2);
	ASM(mov ZDI, 4);
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(minHits, ZSI);
	ASM_MOV_VAR_REG(maxHits, ZDI);
	ASM(pop ZDI);
	ASM(pop ZSI);

	HACKABLES_STOP_SEARCH();

	minHits = MathUtils::clamp(minHits, Flurry::LowerBoundHits, Flurry::MaxHits);
	maxHits = MathUtils::clamp(maxHits, Flurry::LowerBoundHits, Flurry::MaxHits);

	this->hits = RandomHelper::random_int(minHits, maxHits);
}
END_NO_OPTIMIZE
