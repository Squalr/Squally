#include "FogOfWar.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
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
	return Vec2(0.0f, 512.0f);
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
				Strings::Menus_SaveSelect_ConfirmDelete::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Fog,
				this->createDefaultPreview(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_SaveSelect_ConfirmDelete::create()
					},
				},
				int(HackFlags::None),
				-1.0f,
				0.0f
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

void FogOfWar::updateAnimation(float dt)
{
	for (auto next : this->fog)
	{
		const float WidthOver2 = next.sprite->getContentSize().width / 2.0f;
		const float ResetPosition = 2048.0f + WidthOver2;

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
	const float y = RandomHelper::random_real(0.0f, 256.0f);
	const float z = -y * 2.0f;

	return Vec3(x, y, z);
}

NO_OPTIMIZE void FogOfWar::increaseDamage()
{
	/*
	static volatile int isOnPlayerTeamLocal;

	isOnPlayerTeamLocal = entry->isPlayerEntry();

	ASM(pushfd);
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, isOnPlayerTeamLocal);

	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(cmp ZAX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	// If the compare is true, set zax to 1, else 0
	ASM(mov ZAX, 0);
	ASM(cmove ZAX, ZBX);
	ASM_MOV_VAR_REG(isOnPlayerTeamLocal, ZAX);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM(popfd);

	HACKABLES_STOP_SEARCH();

	this->isOnPlayerTeam = (isOnPlayerTeamLocal == 0) ? false : true;
	*/
}
END_NO_OPTIMIZE
