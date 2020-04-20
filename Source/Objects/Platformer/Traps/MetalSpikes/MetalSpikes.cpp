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
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string MetalSpikes::MapKey = "metal-spikes";
const Vec2 MetalSpikes::SpikesUpPosition = Vec2(0.0f, 32.0f);
const Vec2 MetalSpikes::SpikesDownPosition = Vec2(0.0f, -64.0f);

MetalSpikes* MetalSpikes::create(ValueMap& properties)
{
	MetalSpikes* instance = new MetalSpikes(properties);

	instance->autorelease();

	return instance;
}

MetalSpikes::MetalSpikes(ValueMap& properties) : super(properties)
{
	this->spikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(Size(268.0f, 72.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->currentElapsedTimeForSpikeTrigger = RandomHelper::random_real(0.0f, 3.0f);
	this->totalTimeUntilSpikesTrigger = 4.0f;
	this->isRunningAnimation = false;
	this->isFlippedY = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool();

	this->spikes->setFlippedY(this->isFlippedY);

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

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::HackableCodeInfo(
				MetalSpikes::MapKey,
				Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_UpdateTimer::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Clock,
				MetalSpikesUpdateTimerPreview::create(),
				{
					{ HackableCode::Register::xmm2, Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_RegisterXmm2::create() },
					{ HackableCode::Register::xmm4, Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_RegisterXmm2::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f,
				nullptr,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentAddss::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentChangeTo::create()) + 
						"addss xmm2, xmm4\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()),
						// x64
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentAddss::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentChangeTo::create()) + 
						"addss xmm2, xmm4\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Objects_MetalSpikes_UpdateTimer_CommentSSEInstructionsPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
					)
				},
				true
			)
		},
	};

	auto updateSpikesFunc = &MetalSpikes::updateSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateSpikesFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
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

	static volatile float* elapsedPtr;
	static volatile float* deltaTimePtr;

	elapsedPtr = &this->currentElapsedTimeForSpikeTrigger;
	deltaTimePtr = &dt;
	
	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, elapsedPtr);
	ASM_MOV_REG_VAR(ZBX, deltaTimePtr);

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

	if (this->currentElapsedTimeForSpikeTrigger > this->totalTimeUntilSpikesTrigger)
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
			MoveTo::create(0.425f, this->isFlippedY ? -MetalSpikes::SpikesUpPosition : MetalSpikes::SpikesUpPosition),
			DelayTime::create(StayUpDuration),
			MoveTo::create(0.425f, this->isFlippedY ? -MetalSpikes::SpikesDownPosition : MetalSpikes::SpikesDownPosition),
			CallFunc::create([=]()
			{
				this->spikeCollision->setPhysicsEnabled(false);
			}),
			nullptr
		));

		// Play animation
		this->spikes->playAnimationAndReverse(ObjectResources::Traps_MetalSpikes_Spikes_0000, 0.025f, StayUpDuration, 0.025f, false, [=]()
		{
			this->isRunningAnimation = false;
		});
	}
}
END_NO_OPTIMIZE
