#include "SpikeLog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/SpikeLog/SpikeLogGenericPreview.h"
#include "Objects/Platformer/Traps/SpikeLog/SpikeLogSetRotation.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/SpikeLog/IncrementAnimationFrame/IncrementAnimationFrame.h"
#include "Strings/Hacking/Objects/SpikeLog/IncrementAnimationFrame/RegisterEcx.h"
#include "Strings/Hacking/Objects/RegisterRbpWarning.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string SpikeLog::MapKeySpikeLog = "spiked-log";

SpikeLog* SpikeLog::create(ValueMap* initProperties)
{
	SpikeLog* instance = new SpikeLog(initProperties);

	instance->autorelease();

	return instance;
}

SpikeLog::SpikeLog(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->beam = Sprite::create(ObjectResources::Traps_SpikeLog_Beam);
	this->spikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);
	this->spikeCollision = CollisionObject::create(PhysicsBody::createBox(Size(480.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Damage, false, false);
	this->logCollision = CollisionObject::create(PhysicsBody::createBox(Size(512.0f, 128.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);
	this->setDefaultPreview(SpikeLogGenericPreview::create());

	this->spikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.08f, 0.0f);

	this->registerHackables();

	this->spikedLog->addChild(this->spikeCollision);
	this->spikedLog->addChild(this->logCollision);
	this->addChild(this->beam);
	this->addChild(this->spikedLog);
}

SpikeLog::~SpikeLog()
{
}

void SpikeLog::onEnter()
{
	super::onEnter();

	this->updateSpikeLog();
}

void SpikeLog::initializePositions()
{
	super::initializePositions();

	this->spikedLog->setPositionY(this->properties->at(SerializableObject::MapKeyHeight).asFloat() / 2.0f);
	this->logCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
	this->spikeCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
}

void SpikeLog::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				Strings::Hacking_Objects_SpikeLog_IncrementAnimationFrame_IncrementAnimationFrame::create(),
				UIResources::Menus_Icons_BleedingLimb,
				SpikeLogSetRotation::create(),
				{
					{ HackableCode::Register::ecx, Strings::Hacking_Objects_SpikeLog_IncrementAnimationFrame_RegisterEcx::create() },
					{ HackableCode::Register::ebp, Strings::Hacking_Objects_RegisterRbpWarning::create() }
				}
			)
		},
	};

	auto getHeightFunc = &SpikeLog::getTravelHeight;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)getHeightFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 SpikeLog::getButtonOffset()
{
	return Vec2(0.0f, this->spikedLog->getPositionY() + 128.0f);
}

void SpikeLog::updateSpikeLog()
{
	// float duration = MathUtils::clamp(this->travelDistance / (480.0f * SpikeLog::SpeedPer480Px), 0.25f, 10.0f);

	if (this->spikedLog->getPositionY() >= 0.0f)
	{
		float delta = this->getTravelHeight();

		this->spikedLog->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.0f, Vec2(0.0f, -delta))),
			CallFunc::create([=]() { this->updateSpikeLog(); }),
			nullptr
		));
	}
	else
	{
		this->spikedLog->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.0f, Vec2::ZERO)),
			CallFunc::create([=]() { this->updateSpikeLog(); }),
			nullptr
		));
	}
}

float SpikeLog::getTravelHeight()
{
	return 0;
	volatile float* travelDistPtr = nullptr;

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM_MOV_REG_VAR(EAX, travelDistPtr);
	ASM(fld[EAX])
	ASM_NOP8();
	HACKABLE_CODE_END();

	HACKABLES_STOP_SEARCH();
}
