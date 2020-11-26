#include "FogOfWar.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Combat/Abilities/FogOfWar/FogOfWarGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/DecorResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_COMPARE_TEAM 11

const std::string FogOfWar::HackIdentifierFogOfWarTeamCompare = "fog-of-war";

// Static to prevent GCC optimization issues
volatile int FogOfWar::damageDealt = 0;

FogOfWar* FogOfWar::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	FogOfWar* instance = new FogOfWar(caster, target);

	instance->autorelease();

	return instance;
}

FogOfWar::FogOfWar(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, false)
{
	this->fog = std::vector<Fog>();

	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog1), -32.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog2), 256.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog3), -128.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog4), 160.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog5), -192.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog6), 64.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog7), -96.0f, this->getRandomSpawnPosition()));
	this->fog.push_back(Fog(Sprite::create(DecorResources::Generic_Background_Fog8), 96.0f, this->getRandomSpawnPosition()));

	for (auto next : this->fog)
	{
		this->addChild(next.sprite);
	}
}

FogOfWar::~FogOfWar()
{
}

void FogOfWar::onEnter()
{
	super::onEnter();

	for (auto next : this->fog)
	{
		next.sprite->setPosition3D(next.spawnPosition);
		next.sprite->setOpacity(0);
		next.sprite->runAction(FadeTo::create(0.5f, 192));
	}
	
	CombatEvents::TriggerHackableCombatCue();
}

void FogOfWar::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 FogOfWar::getButtonOffset()
{
	return Vec2(0.0f, 256.0f);
}

void FogOfWar::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				FogOfWar::HackIdentifierFogOfWarTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_FogOfWar::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Fog,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_RegisterEdx::create()
					},
				},
				int(HackFlags::None),
				-1.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentShl::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentShlBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentElaborate::create()) +
						"shl edx, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentHint::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentShl::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentShlBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentElaborate::create()) +
						"shl rdx, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_FogOfWar_CommentHint::create())
					),
				},
				true
			)
		},
	};

	auto func = &FogOfWar::increaseDamage;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* FogOfWar::createDefaultPreview()
{
	return FogOfWarGenericPreview::create();
}

void FogOfWar::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	bool isOnCasterTeam = false;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getSameTeamEntities(this->caster))
		{
			if (next == damageOrHealing->caster)
			{
				isOnCasterTeam = true;
			}
		}
	}));

	if (!isOnCasterTeam)
	{
		return;
	}

	this->damageDealt = damageOrHealing->damageOrHealingValue;

	this->increaseDamage();

	// Bound by 0.5x and 2x
	*(damageOrHealing->damageOrHealing) = MathUtils::clamp(this->damageDealt, damageOrHealing->damageOrHealingValue / 2, damageOrHealing->damageOrHealingValue * 2);
}

void FogOfWar::updateAnimation(float dt)
{
	for (auto next : this->fog)
	{
		const float WidthOver2 = next.sprite->getContentSize().width / 2.0f;
		const float ResetPosition = 1568.0f + WidthOver2;

		next.sprite->setPositionX(next.sprite->getPositionX() + next.speed * dt);

		if (next.sprite->getPositionX() > ResetPosition)
		{
			next.sprite->setPositionX(-ResetPosition);
		}
		else if (next.sprite->getPositionX() < -ResetPosition)
		{
			next.sprite->setPositionX(ResetPosition);
		}
	}
}

Vec3 FogOfWar::getRandomSpawnPosition()
{
	const float x = RandomHelper::random_real(-1024.0f, 1024.0f);
	const float y = RandomHelper::random_real(-64.0f, 192.0f);
	const float z = RandomHelper::random_real(0.0f, -128.0f);

	return Vec3(x, y, z);
}

NO_OPTIMIZE void FogOfWar::increaseDamage()
{
	static volatile int damageDealtLocal;

	damageDealtLocal = this->damageDealt;

	ASM(push ZDX);

	ASM_MOV_REG_VAR(edx, damageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(shl ZDX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageDealtLocal, edx);

	ASM(pop ZDX);

	this->damageDealt = damageDealtLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
