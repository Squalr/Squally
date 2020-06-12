#include "ArrowRain.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ArrowRain/ArrowRainGenericPreview.h"
#include "Objects/Platformer/Combat/Projectiles/ArrowRain/ArrowRainSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

const std::string ArrowRain::HackIdentifierArrowRainSpeed = "arrow-rain-team";

ArrowRain* ArrowRain::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ArrowRain* instance = new ArrowRain(caster, target);

	instance->autorelease();

	return instance;
}

ArrowRain::ArrowRain(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
}

ArrowRain::~ArrowRain()
{
}

void ArrowRain::update(float dt)
{
	super::update(dt);

	this->setArrowRainSpeed();
}

Vec2 ArrowRain::getButtonOffset()
{
	return Vec2::ZERO;
}

void ArrowRain::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FIREBALL_SPEED,
			HackableCode::HackableCodeInfo(
				ArrowRain::HackIdentifierArrowRainSpeed,
				Strings::Menus_Hacking_Objects_Combat_Projectiles_ArrowRain_CompareTeam_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_FireBalls,
				ArrowRainSpeedPreview::create(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Combat_Projectiles_ArrowRain_CompareTeam_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				3.0f,
				0.0f
			)
		},
	};

	auto fireballFunc = &ArrowRain::setArrowRainSpeed;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)fireballFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ArrowRain::createDefaultPreview()
{
	return ArrowRainGenericPreview::create();
}

NO_OPTIMIZE void ArrowRain::setArrowRainSpeed()
{
	static volatile float* freeMemoryForUser = new float[16];
	static volatile float speedMultiplier;
	static volatile float speedMultiplierTemp;
	static volatile float* speedMultiplierPtr;
	static volatile float* speedMultiplierTempPtr;

	speedMultiplier = 1.0f;
	speedMultiplierTemp = 1.0f;
	speedMultiplierPtr = &speedMultiplier;
	speedMultiplierTempPtr = &speedMultiplierTemp;

	// Initialize xmm0 and xmm1
	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierTempPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FIREBALL_SPEED);
	ASM(mulps xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
