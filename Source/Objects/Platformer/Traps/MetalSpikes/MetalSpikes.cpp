#include "MetalSpikes.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/MetalSpikes/MetalSpikesGenericPreview.h"
#include "Objects/Platformer/Traps/MetalSpikes/MetalSpikesUpdateTimerPreview.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/MetalSpikes/UpdateTimer/RegisterSt0.h"
#include "Strings/Hacking/Objects/MetalSpikes/UpdateTimer/UpdateTimer.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string MetalSpikes::MapKeyMetalSpikes = "metal-spikes";

MetalSpikes* MetalSpikes::create(ValueMap* initProperties)
{
	MetalSpikes* instance = new MetalSpikes(initProperties);

	instance->autorelease();

	return instance;
}

MetalSpikes::MetalSpikes(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->currentElapsedTimeForSpikeTrigger = 0.0f;
	this->totalTimeUntilSpikesTrigger = 5.0f;
	this->isRunningAnimation = false;

	this->spikeCollision = CollisionObject::create(PhysicsBody::createBox(Size(480.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Damage, false, false);
	this->setDefaultPreview(MetalSpikesGenericPreview::create());

	this->registerHackables();
}

MetalSpikes::~MetalSpikes()
{
}

void MetalSpikes::onEnter()
{
	super::onEnter();
}

void MetalSpikes::update(float dt)
{
	super::update(dt);

	this->updateSpikes(dt);
}

void MetalSpikes::initializePositions()
{
	super::initializePositions();
}

void MetalSpikes::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				MetalSpikes::MapKeyMetalSpikes,
				Strings::Hacking_Objects_MetalSpikes_UpdateTimer_UpdateTimer::create(),
				UIResources::Menus_Icons_BleedingLimb,
				MetalSpikesUpdateTimerPreview::create(),
				{
					{ HackableCode::Register::st0, Strings::Hacking_Objects_MetalSpikes_UpdateTimer_RegisterSt0::create() },
				}
			)
		},
	};

	auto updateSpikesFunc = &MetalSpikes::updateSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateSpikesFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 MetalSpikes::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void MetalSpikes::updateSpikes(float dt)
{
	if (this->isRunningAnimation)
	{
		return;
	}

	volatile float* elapsedPtr = &this->currentElapsedTimeForSpikeTrigger;
	volatile float* deltaTimePtr = &dt;

	ASM(push EAX);
	ASM(push EBX);
	ASM_MOV_REG_VAR(EAX, elapsedPtr);
	ASM_MOV_REG_VAR(EBX, dt);

	ASM(fld dword ptr[EAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(fadd dword ptr[EBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr[EAX])

	ASM(pop EAX);
	ASM(pop EBX);

	HACKABLES_STOP_SEARCH();
}
