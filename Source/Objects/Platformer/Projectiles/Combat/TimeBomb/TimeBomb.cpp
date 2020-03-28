#include "TimeBomb.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Combat/TimeBomb/TimeBombClippy.h"
#include "Objects/Platformer/Projectiles/Combat/TimeBomb/TimeBombGenericPreview.h"
#include "Objects/Platformer/Projectiles/Combat/TimeBomb/TimeBombSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TIME_BOMB_TICK 11

const float TimeBomb::HackDuration = 3.1f;
const int TimeBomb::TimerInitial = 7;
const int TimeBomb::TimerMax = 90;

TimeBomb* TimeBomb::create(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onExplode)
{
	TimeBomb* instance = new TimeBomb(owner, target, onExplode);

	instance->autorelease();

	return instance;
}

TimeBomb::TimeBomb(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onExplode)
	: super(owner, target, true, Node::create(), Size(32.0f, 32.0f))
{
	this->bomb = Sprite::create(ObjectResources::Traps_TimeBomb_BOMB);
	this->timerPlate = Sprite::create(ObjectResources::Traps_TimeBomb_TimerPlate);
	this->minutesString = ConstantString::create();
	this->secondsString = ConstantString::create();
	this->timerLabel = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::H2,
		Strings::Common_XColonY::create()->setStringReplacementVariables({ this->minutesString, this->secondsString })
	);
	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->spawnSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);
	this->tickSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Ding1);
	this->explodeSound = WorldSound::create(SoundResources::Platformer_FX_Explosions_Explosion1);
	this->clippy = TimeBombClippy::create();
	this->onExplode = onExplode;
	this->bombTick = TimeBomb::TimerInitial;
	this->hasExploded = false;
	this->elapsed = 0.0f;

	this->registerClippy(this->clippy);
	this->postFXNode->addChild(this->spawnSound);
	this->postFXNode->addChild(this->tickSound);
	this->postFXNode->addChild(this->explodeSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->bomb);
	this->object->addChild(this->timerPlate);
	this->object->addChild(this->timerLabel);
}

TimeBomb::~TimeBomb()
{
}

void TimeBomb::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->updateTimerText();
}

void TimeBomb::initializePositions()
{
	super::initializePositions();

	this->explosionAnim->setPosition(Vec2(0.0f, 96.0f));
}

void TimeBomb::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}

	this->elapsed += dt;

	if (this->elapsed >= 1.0f)
	{
		this->elapsed -= 1.0f;

		int previousTick = this->bombTick;

		this->tickTimeBomb();

		if (previousTick != this->bombTick)
		{
			this->tickSound->play();
			this->updateTimerText();
		}

		if (this->bombTick <= 0)
		{
			this->explode();
		}
	}
}

void TimeBomb::enableClippy()
{
	this->clippy->setIsEnabled(true);
}

void TimeBomb::runSpawnFX()
{
	this->spawnSound->play();
}

void TimeBomb::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);

	this->explodeSound->play();
}

Vec2 TimeBomb::getButtonOffset()
{
	return Vec2(0.0f, -48.0f);
}

void TimeBomb::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_TIME_BOMB_TICK,
			HackableCode::HackableCodeInfo(
				"TimeBomb",
				Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_ApplySpeed::create(),
				UIResources::Menus_Icons_Clock,
				TimeBombSpeedPreview::create(),
				{
					/*
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_TimeBomb_ApplySpeed_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_TimeBomb_ApplySpeed_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_TimeBomb_ApplySpeed_RegisterXmm1::create() }
					*/
				},
				int(HackFlags::None),
				TimeBomb::HackDuration,
				0.0f,
				this->clippy,
				{
				}
			)
		},
	};

	auto tickFunc = &TimeBomb::tickTimeBomb;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)tickFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* TimeBomb::createDefaultPreview()
{
	return TimeBombGenericPreview::create();
}

void TimeBomb::updateTimerText()
{
	this->minutesString->setString(std::to_string(this->bombTick / 60));
	this->secondsString->setString(std::to_string(this->bombTick % 60));

	this->timerLabel->setTextColor(this->bombTick <= 5 ? Color4B::RED : Color4B::WHITE);
}

void TimeBomb::explode()
{
	if (this->hasExploded)
	{
		return;
	}

	this->hasExploded = true;

	this->bomb->setVisible(false);
	this->timerPlate->setVisible(false);
	this->timerLabel->setVisible(false);
	this->explosionAnim->playAnimation(FXResources::ExplosionGround_ExplosionGround_0000, 0.05f, true);
	this->explodeSound->play();

	this->onExplode();
}

NO_OPTIMIZE void TimeBomb::tickTimeBomb()
{
	volatile int currentTick = this->bombTick;

	ASM(push ZCX);
	ASM_MOV_REG_VAR(ZCX, currentTick);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TIME_BOMB_TICK);
	ASM(dec ZCX);
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(currentTick, ZCX);
	ASM(pop ZCX);

	this->bombTick = MathUtils::clamp(currentTick, 0, TimeBomb::TimerMax);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
