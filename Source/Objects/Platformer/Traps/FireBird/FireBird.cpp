#include "FireBird.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/FireBird/FireBirdGenericPreview.h"
#include "Objects/Platformer/Traps/FireBird/FireBirdUpdateTimerPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string FireBird::MapKey = "fire-bird";
const Vec2 FireBird::SpikesUpPosition = Vec2(0.0f, 32.0f);
const Vec2 FireBird::SpikesDownPosition = Vec2(0.0f, -64.0f);

FireBird* FireBird::create(ValueMap& properties)
{
	FireBird* instance = new FireBird(properties);

	instance->autorelease();

	return instance;
}

FireBird::FireBird(ValueMap& properties) : super(properties)
{
	this->spikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_FireBird_FireBird_0000);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(CSize(225.0f, 395.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->currentElapsedTimeForSpikeTrigger = RandomHelper::random_real(0.0f, 3.0f);
	this->totalTimeUntilSpikesTrigger = 4.0f;
	this->isRunningAnimation = false;
	this->isFlippedY = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool();

	this->spikes->setFlippedY(this->isFlippedY);

	this->addChild(this->spikeCollision);
	this->addChild(this->spikes);
}

FireBird::~FireBird()
{
}

void FireBird::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void FireBird::update(float dt)
{
	super::update(dt);

	this->updateSpikes(dt);
}

void FireBird::initializePositions()
{
	super::initializePositions();

	this->spikeCollision->setPosition(FireBird::SpikesDownPosition);
}

Vec2 FireBird::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void FireBird::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::HackableCodeInfo(
				FireBird::MapKey,
				Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_UpdateTimer::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Clock,
				LazyNode<HackablePreview>::create([=](){ return FireBirdUpdateTimerPreview::create(); }),
				{
					{ HackableCode::Register::xmm2, Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_RegisterXmm2::create() },
					{ HackableCode::Register::xmm4, Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_RegisterXmm2::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentAddss::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentChangeTo::create()) + 
						"addss xmm2, xmm4\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentAddss::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentChangeTo::create()) + 
						"addss xmm2, xmm4\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_FireBird_UpdateTimer_CommentSSEInstructionsPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
					)
				},
				true
			)
		},
	};

	auto updateSpikesFunc = &FireBird::updateSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateSpikesFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* FireBird::createDefaultPreview()
{
	return FireBirdGenericPreview::create();
}

NO_OPTIMIZE void FireBird::updateSpikes(float dt)
{
	if (this->isRunningAnimation)
	{
		return;
	}

	static volatile float* elapsedPtr;
	static volatile float* deltaTimePtr;

	elapsedPtr = &this->currentElapsedTimeForSpikeTrigger;
	deltaTimePtr = &dt;
	
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_PTR(ZAX, elapsedPtr);
	ASM_MOV_REG_PTR(ZBX, deltaTimePtr);

	ASM(movss xmm2, [ZAX])
	ASM(movss xmm4, [ZBX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(addss xmm2, xmm4)
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(movss [ZAX], xmm2)

	ASM(pop ZAX);
	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();
	
	this->currentElapsedTimeForSpikeTrigger = MathUtils::clamp(this->currentElapsedTimeForSpikeTrigger, 0.0f, this->totalTimeUntilSpikesTrigger);

	if (this->currentElapsedTimeForSpikeTrigger >= this->totalTimeUntilSpikesTrigger)
	{
		const float StayUpDuration = 0.0f;

		this->isRunningAnimation = true;
		this->currentElapsedTimeForSpikeTrigger = 0.0f;

		// Move collision box
		this->spikeCollision->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->spikeCollision->setPhysicsFlagEnabled(true);
			}),
			MoveTo::create(0.425f, this->isFlippedY ? -FireBird::SpikesUpPosition : FireBird::SpikesUpPosition),
			DelayTime::create(StayUpDuration),
			MoveTo::create(0.425f, this->isFlippedY ? -FireBird::SpikesDownPosition : FireBird::SpikesDownPosition),
			CallFunc::create([=]()
			{
				this->spikeCollision->setPhysicsFlagEnabled(false);
			}),
			nullptr
		));

		// Play animation
		this->spikes->playAnimationAndReverse(ObjectResources::Traps_FireBird_FireBird_0000, 0.025f, StayUpDuration, 0.025f, false, false, [=]()
		{
			this->isRunningAnimation = false;
		});
	}
}
END_NO_OPTIMIZE
