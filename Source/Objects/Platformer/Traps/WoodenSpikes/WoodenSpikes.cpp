#include "WoodenSpikes.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikesGenericPreview.h"
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikesUpdateTimerPreview.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/WoodenSpikes/UpdateTimer/RegisterSt0.h"
#include "Strings/Hacking/Objects/WoodenSpikes/UpdateTimer/UpdateTimer.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string WoodenSpikes::MapKeyWoodenSpikes = "wooden-spikes";
const Vec2 WoodenSpikes::SpikesDownPosition = Vec2(0.0f, -64.0f);

WoodenSpikes* WoodenSpikes::create(ValueMap* initProperties)
{
	WoodenSpikes* instance = new WoodenSpikes(initProperties);

	instance->autorelease();

	return instance;
}

WoodenSpikes::WoodenSpikes(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->currentElapsedTimeForSpikeTrigger = RandomHelper::random_real(0.0f, 3.0f);
	this->totalTimeUntilSpikesTrigger = 4.0f;
	this->isRunningAnimation = false;

	this->spikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);

	this->spikeCollision = CollisionObject::create(PhysicsBody::createBox(Size(268.0f, 72.0f)), (CollisionType)PlatformerCollisionType::Damage, false, false);
	this->setDefaultPreview(WoodenSpikesGenericPreview::create());

	this->registerHackables();

	this->addChild(this->spikeCollision);
	this->addChild(this->spikes);
}

WoodenSpikes::~WoodenSpikes()
{
}

void WoodenSpikes::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void WoodenSpikes::update(float dt)
{
	super::update(dt);

	this->updateSpikes(dt);
}

void WoodenSpikes::initializePositions()
{
	super::initializePositions();

	this->spikeCollision->setPosition(WoodenSpikes::SpikesDownPosition);
}

void WoodenSpikes::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				WoodenSpikes::MapKeyWoodenSpikes,
				Strings::Hacking_Objects_WoodenSpikes_UpdateTimer_UpdateTimer::create(),
				UIResources::Menus_Icons_Clock,
				WoodenSpikesUpdateTimerPreview::create(),
				{
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_WoodenSpikes_UpdateTimer_RegisterSt0::create() },
				}
			)
		},
	};

	auto updateSpikesFunc = &WoodenSpikes::updateSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateSpikesFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 WoodenSpikes::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void WoodenSpikes::updateSpikes(float dt)
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
			MoveTo::create(0.425, Vec2::ZERO),
			DelayTime::create(stayUpDuration),
			MoveTo::create(0.425, WoodenSpikes::SpikesDownPosition),
			nullptr
		));

		// Play animation
		this->spikes->playAnimationAndReverse(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, stayUpDuration, 0.025f, false, [=]()
		{
			this->isRunningAnimation = false;
		});
	}
}
