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
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/MetalSpikes/UpdateTimer/RegisterSt0.h"
#include "Strings/Hacking/Objects/MetalSpikes/UpdateTimer/UpdateTimer.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string MetalSpikes::MapKeyMetalSpikes = "metal-spikes";
const Vec2 MetalSpikes::SpikesDownPosition = Vec2(0.0f, -64.0f);

MetalSpikes* MetalSpikes::create(ValueMap& initProperties)
{
	MetalSpikes* instance = new MetalSpikes(initProperties);

	instance->autorelease();

	return instance;
}

MetalSpikes::MetalSpikes(ValueMap& initProperties) : super(initProperties)
{
	this->currentElapsedTimeForSpikeTrigger = RandomHelper::random_real(0.0f, 3.0f);
	this->totalTimeUntilSpikesTrigger = 4.0f;
	this->isRunningAnimation = false;

	this->spikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);

	this->spikeCollision = CollisionObject::create(PhysicsBody::createBox(Size(268.0f, 72.0f)), (CollisionType)PlatformerCollisionType::Damage, false, false);

	this->addChild(this->spikeCollision);
	this->addChild(this->spikes);
}

MetalSpikes::~MetalSpikes()
{
}

void MetalSpikes::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MetalSpikes::update(float dt)
{
	super::update(dt);

	this->updateSpikes(dt);
}

void MetalSpikes::initializePositions()
{
	super::initializePositions();

	this->spikeCollision->setPosition(MetalSpikes::SpikesDownPosition);
}

Vec2 MetalSpikes::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void MetalSpikes::registerHackables()
{
	super::registerHackables();

	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				MetalSpikes::MapKeyMetalSpikes,
				Strings::Hacking_Objects_MetalSpikes_UpdateTimer_UpdateTimer::create(),
				UIResources::Menus_Icons_Clock,
				MetalSpikesUpdateTimerPreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Hacking_Objects_MetalSpikes_UpdateTimer_RegisterSt0::create() },
				},
				20.0f
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

HackablePreview* MetalSpikes::createDefaultPreview()
{
	return MetalSpikesGenericPreview::create();
}

NO_OPTIMIZE void MetalSpikes::updateSpikes(float dt)
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
	ASM_MOV_REG_VAR(EBX, deltaTimePtr);

	ASM(fld dword ptr [EAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(fadd dword ptr [EBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [EAX])

	ASM(pop EAX);
	ASM(pop EBX);

	HACKABLES_STOP_SEARCH();

	if (this->currentElapsedTimeForSpikeTrigger > this->totalTimeUntilSpikesTrigger)
	{
		const float stayUpDuration = 1.5f;

		this->isRunningAnimation = true;
		this->currentElapsedTimeForSpikeTrigger = 0.0f;

		// Move collision box
		this->spikeCollision->runAction(Sequence::create(
			MoveTo::create(0.425f, Vec2::ZERO),
			DelayTime::create(stayUpDuration),
			MoveTo::create(0.425f, MetalSpikes::SpikesDownPosition),
			nullptr
		));

		// Play animation
		this->spikes->playAnimationAndReverse(ObjectResources::Traps_MetalSpikes_Spikes_0000, 0.025f, stayUpDuration, 0.025f, false, [=]()
		{
			this->isRunningAnimation = false;
		});
	}
}
