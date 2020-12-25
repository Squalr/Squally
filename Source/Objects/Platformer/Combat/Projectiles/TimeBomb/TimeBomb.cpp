#include "TimeBomb.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/TimeBomb/TimeBombGenericPreview.h"
#include "Objects/Platformer/Combat/Projectiles/TimeBomb/TimeBombTickPreview.h"
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
	: super(owner, target, true, Node::create(), Size(133.0f, 133.0f))
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
	this->spawnSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_Spawn1);
	this->tickSound = WorldSound::create(SoundResources::Platformer_Objects_Traps_Tick1);
	this->tickSoundPositive = WorldSound::create(SoundResources::Platformer_Objects_Traps_Tick2);
	this->explodeSound = WorldSound::create(SoundResources::Platformer_FX_Explosions_Explosion1);
	this->onExplode = onExplode;
	this->bombTick = TimeBomb::TimerInitial;
	this->hasExploded = false;
	this->elapsed = 0.0f;

	this->postFXNode->addChild(this->spawnSound);
	this->postFXNode->addChild(this->tickSound);
	this->postFXNode->addChild(this->tickSoundPositive);
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
	
	this->explosionAnim->setPosition(Vec2(0.0f, 48.0f));
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

		if (this->bombTick < previousTick)
		{
			this->tickSound->play();
			this->updateTimerText();
		}
		else if (this->bombTick > previousTick)
		{
			this->tickSoundPositive->play();
			this->updateTimerText();
		}

		if (this->bombTick <= 0)
		{
			this->explode();
		}
	}
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
				Strings::Menus_Hacking_Abilities_Abilities_TimeBomb_TimeBombTick::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_Clock,
				LazyNode<HackablePreview>::create([=](){ return TimeBombTickPreview::create(); }),
				{
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Abilities_TimeBomb_RegisterEcx::create() },
				},
				int(HackFlags::None),
				TimeBomb::HackDuration,
				0.0f
			)
		},
	};

	auto tickFunc = &TimeBomb::tickTimeBomb;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)tickFunc, codeInfoMap);

	for (HackableCode* next : hackables)
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
	static volatile int currentTick;

	currentTick = this->bombTick;

	ASM(push ZCX);
	ASM_MOV_REG_VAR(ecx, currentTick);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TIME_BOMB_TICK);
	ASM(dec ZCX);
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(currentTick, ecx);
	ASM(pop ZCX);

	this->bombTick = MathUtils::clamp(currentTick, 0, TimeBomb::TimerMax);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
