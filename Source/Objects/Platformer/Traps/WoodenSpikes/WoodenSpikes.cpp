#include "WoodenSpikes.h"

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
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikesGenericPreview.h"
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikesUpdateTimerPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string WoodenSpikes::MapKey = "wooden-spikes";
const Vec2 WoodenSpikes::SpikesUpPosition = Vec2(0.0f, 32.0f);
const Vec2 WoodenSpikes::SpikesDownPosition = Vec2(0.0f, -64.0f);

WoodenSpikes* WoodenSpikes::create(ValueMap& properties)
{
	WoodenSpikes* instance = new WoodenSpikes(properties);

	instance->autorelease();

	return instance;
}

WoodenSpikes::WoodenSpikes(ValueMap& properties) : super(properties)
{
	this->spikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(Size(268.0f, 72.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->currentElapsedTimeForSpikeTrigger = RandomHelper::random_real(0.0f, 3.0f);
	this->totalTimeUntilSpikesTrigger = 4.0f;
	this->isRunningAnimation = false;
	this->isFlippedY = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool();

	this->spikes->setFlippedY(this->isFlippedY);

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

Vec2 WoodenSpikes::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void WoodenSpikes::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::HackableCodeInfo(
				WoodenSpikes::MapKey,
				Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_UpdateTimer::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Clock,
				LazyNode<HackablePreview>::create([=](){ return WoodenSpikesUpdateTimerPreview::create(); }),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_RegisterSt0::create() },
					{ HackableCode::Register::st0, Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_RegisterSt0::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFadd::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentDontWorry::create()) + 
						"fadd dword ptr [ebx]\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFPUInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFPUInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFadd::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentDontWorry::create()) + 
						"fadd dword ptr [rbx]\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFPUInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_WoodenSpikes_UpdateTimer_CommentFPUInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
					)
				},
				true
			)
		},
	};

	auto updateSpikesFunc = &WoodenSpikes::updateSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateSpikesFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* WoodenSpikes::createDefaultPreview()
{
	return WoodenSpikesGenericPreview::create();
}

NO_OPTIMIZE void WoodenSpikes::updateSpikes(float dt)
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

	ASM_MOV_REG_VAR(ZAX, elapsedPtr);
	ASM_MOV_REG_VAR(ZBX, deltaTimePtr);

	ASM(fld dword ptr [ZAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(fadd dword ptr [ZBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [ZAX])

	ASM(pop ZAX);
	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	this->currentElapsedTimeForSpikeTrigger = MathUtils::clamp(this->currentElapsedTimeForSpikeTrigger, 0.0f, this->totalTimeUntilSpikesTrigger);

	if (this->currentElapsedTimeForSpikeTrigger >= this->totalTimeUntilSpikesTrigger)
	{
		const float StayUpDuration = 1.5f;

		this->isRunningAnimation = true;
		this->currentElapsedTimeForSpikeTrigger = 0.0f;

		// Move collision box
		this->spikeCollision->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->spikeCollision->setPhysicsEnabled(true);
			}),
			MoveTo::create(0.425f, this->isFlippedY ? -WoodenSpikes::SpikesUpPosition : WoodenSpikes::SpikesUpPosition),
			DelayTime::create(StayUpDuration),
			MoveTo::create(0.425f, this->isFlippedY ? -WoodenSpikes::SpikesDownPosition : WoodenSpikes::SpikesDownPosition),
			CallFunc::create([=]()
			{
				this->spikeCollision->setPhysicsEnabled(false);
			}),
			nullptr
		));

		// Play animation
		this->spikes->playAnimationAndReverse(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, StayUpDuration, 0.025f, false, [=]()
		{
			this->isRunningAnimation = false;
		});
	}
}
END_NO_OPTIMIZE
