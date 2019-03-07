#include "FloatingRock.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

// TEMP DEBUG:
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugGenericPreview.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugSetSpeedPreview.h"
#include "Strings/Hacking/Objects/HeavenHug/GetTravelHeight/GetTravelHeight.h"
#include "Strings/Hacking/Objects/HeavenHug/GetTravelHeight/RegisterEax.h"
#include "Strings/Hacking/Objects/RegisterRbpWarning.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GET_DENSITY 1

const std::string FloatingRock::MapKeyFloatingRock = "floating-rock";

FloatingRock* FloatingRock::create(ValueMap& initProperties)
{
	FloatingRock* instance = new FloatingRock(initProperties);
	
	instance->autorelease();

	return instance;
}

FloatingRock::FloatingRock(ValueMap& initProperties) : super(initProperties)
{
	this->sprite = Sprite::create(ObjectResources::Physics_RollingStone_RollingStone);
	this->collision = CollisionObject::create(PhysicsBody::createCircle(96.0f), (CollisionType)PlatformerCollisionType::Physics, false, true);

	this->collision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->collision->addChild(this->sprite);
	this->contentNode->addChild(this->collision);
}

FloatingRock::~FloatingRock()
{
}

void FloatingRock::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void FloatingRock::initializePositions()
{
	super::initializePositions();
}

void FloatingRock::update(float dt)
{
	super::update(dt);
}

Vec2 FloatingRock::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void FloatingRock::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_GET_DENSITY,
			HackableCode::LateBindData(
				FloatingRock::MapKeyFloatingRock,
				Strings::Hacking_Objects_HeavenHug_GetTravelHeight_GetTravelHeight::create(),
				UIResources::Menus_Icons_BleedingLimb,
				HeavenHugSetSpeedPreview::create(),
				{
					{ HackableCode::Register::eax, Strings::Hacking_Objects_HeavenHug_GetTravelHeight_RegisterEax::create() },
					{ HackableCode::Register::ebp, Strings::Hacking_Objects_RegisterRbpWarning::create() }
				},
				20.0f
			)
		},
	};

	auto densityFunc = &FloatingRock::getDensityNonVirtual;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)densityFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

float FloatingRock::getDensity()
{
	return this->getDensityNonVirtual();
}

float FloatingRock::getDensityNonVirtual()
{
	static float* xmm0Storage = new float[4];
	static float* xmm1Storage = new float[4];
	static float* freeMemoryForUser = new float[4];
	volatile float densityRet = 0.5f;
	volatile float* densityRetPtr = &densityRet;
	volatile float densityCopy = this->loadedDensity;
	volatile float* densityCopyPtr = &densityCopy;

	// Save XMM registers
	ASM(push EDI);
	ASM(push ESI);
	ASM_MOV_REG_VAR(EDI, xmm0Storage);
	ASM(movaps [EDI], xmm0);
	ASM_MOV_REG_VAR(ESI, xmm1Storage);
	ASM(movaps [ESI], xmm1);

	// Prepare variables (initialize xmm0 with return value, xmm1 with loaded density)
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, densityRetPtr);
	ASM(movss xmm0, dword ptr [EAX]);
	ASM_MOV_REG_VAR(EAX, densityCopyPtr);
	ASM(movss xmm1, dword ptr [EAX]);
	ASM(pop EAX);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GET_DENSITY);
	ASM(movss xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	// Copy from xmm0 to the output variable
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, densityRetPtr);
	ASM(movss dword ptr [EAX], xmm0);
	ASM(pop EAX);

	// Restore XMM registers
	ASM(movaps xmm0, [EDI]);
	ASM(movaps xmm1, [ESI]);
	ASM(pop ESI);
	ASM(pop EDI);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(densityRet, 0.0f, 1.0f);
}
