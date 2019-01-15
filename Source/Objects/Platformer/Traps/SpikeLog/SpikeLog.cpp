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

	this->spikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.08f, 0.0f);
	this->spikedLog->getForwardsAnimation()->incrementCallback = [=](int count, int max) { return this->incrementSpikeLogAnimation(count, max); };
}

void SpikeLog::initializePositions()
{
	super::initializePositions();

	// this->spikedLog->setPositionY(this->properties->at(SerializableObject::MapKeyHeight).asFloat() / 2.0f);
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
				SpikeLog::MapKeySpikeLog,
				Strings::Hacking_Objects_SpikeLog_IncrementAnimationFrame_IncrementAnimationFrame::create(),
				UIResources::Menus_Icons_BleedingLimb,
				SpikeLogSetRotation::create(),
				{
					{ HackableCode::Register::ecx, Strings::Hacking_Objects_SpikeLog_IncrementAnimationFrame_RegisterEcx::create() },
				}
			)
		},
	};

	auto incrementAnimationFunc = &SpikeLog::incrementSpikeLogAnimation;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)incrementAnimationFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 SpikeLog::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

int SpikeLog::incrementSpikeLogAnimation(int count, int max)
{
	ASM(push ECX)
	ASM_MOV_REG_VAR(ECX, count);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(inc ECX)
	ASM_NOP6();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(count, ECX);
	ASM(pop ECX);

	HACKABLES_STOP_SEARCH();

	this->spikeCollision->setPositionY(96.0f * std::sin(((float)count / (float)max) * 2.0f * M_PI));

	return count;
}
