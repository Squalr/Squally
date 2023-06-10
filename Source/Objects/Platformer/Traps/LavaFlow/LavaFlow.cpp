#include "LavaFlow.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/LavaFlow/LavaFlowGenericPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RAISE_LAVA 1

const std::string LavaFlow::MapKey = "lava-flow";
const Vec2 LavaFlow::SpikesUpPosition = Vec2(0.0f, 32.0f);
const Vec2 LavaFlow::SpikesDownPosition = Vec2(0.0f, -64.0f);

LavaFlow* LavaFlow::create(ValueMap& properties)
{
	LavaFlow* instance = new LavaFlow(properties);

	instance->autorelease();

	return instance;
}

LavaFlow::LavaFlow(ValueMap& properties) : super(properties)
{
	this->ripple = SmartAnimationSequenceNode::create(FXResources::FireAura_FireAura_0000);

	this->addChild(this->ripple);
}

LavaFlow::~LavaFlow()
{
}

void LavaFlow::onEnter()
{
	super::onEnter();

	this->ripple->playAnimationRepeat(FXResources::FireAura_FireAura_0000, 0.075f, 0.0f, true);

	this->scheduleUpdate();
}

void LavaFlow::update(float dt)
{
	super::update(dt);

	this->checkLavaFlow();
}

void LavaFlow::initializePositions()
{
	super::initializePositions();
}

Vec2 LavaFlow::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void LavaFlow::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RAISE_LAVA,
			HackableCode::HackableCodeInfo(
				LavaFlow::MapKey,
				Strings::TODO::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_Fire,
				LazyNode<HackablePreview>::create([=](){ return LavaFlowGenericPreview::create(); }),
				{
					{ HackableCode::Register::xmm2, Strings::TODO::create() },
					{ HackableCode::Register::xmm4, Strings::TODO::create() },
				},
				int(HackFlags::Fire),
				20.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							ConstantString::create("maxss xmm0, xmm1\n"),
							ConstantString::create("movss [eax], xmm1\n\n")
						})
						, // x64
						ConcatString::create({
							ConstantString::create("maxss xmm0, xmm1\n"),
							ConstantString::create("movss [rax], xmm1\n\n")
						})
					)
				},
				true
			)
		},
	};

	auto func = &LavaFlow::checkLavaFlow;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* LavaFlow::createDefaultPreview()
{
	return LavaFlowGenericPreview::create();
}

NO_OPTIMIZE void LavaFlow::checkLavaFlow()
{
	static volatile float flow = 0.0f;
	static volatile float* flowPtr;
	static bool runOnce = true;

	flowPtr = &flow;
	
	ASM(push ZAX);

	ASM_MOV_REG_PTR(ZAX, flowPtr);

	ASM(xorps xmm0, xmm0) // Set to 0.0f
	ASM(movss xmm1, [ZAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RAISE_LAVA);
	ASM(maxss xmm0, xmm1)
	ASM(movss [ZAX], xmm0)
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZAX);

	if (runOnce && flow >= 1.0f)
	{
		runOnce = false;
		this->broadcastMapEvent("lava-flooded", ValueMap());
	}

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
