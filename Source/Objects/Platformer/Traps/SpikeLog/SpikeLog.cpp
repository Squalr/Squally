#include "SpikeLog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/SpikeLog/SpikeLogGenericPreview.h"
#include "Objects/Platformer/Traps/SpikeLog/SpikeLogSetRotationPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string SpikeLog::MapKey = "spiked-log";

SpikeLog* SpikeLog::create(ValueMap& properties)
{
	SpikeLog* instance = new SpikeLog(properties);

	instance->autorelease();

	return instance;
}

SpikeLog::SpikeLog(ValueMap& properties) : super(properties)
{
	this->beam = Sprite::create(ObjectResources::Traps_SpikeLog_Beam);
	this->spikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLog_SpikedLog_00);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(Size(32.0f, 480.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->logCollision = CollisionObject::create(CollisionObject::createBox(Size(128.0f, 512.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));

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

	this->spikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLog_SpikedLog_00, 0.08f, 0.0f);
	this->spikedLog->getForwardsAnimation()->incrementCallback = [=](int current, int max)
	{
		return this->incrementSpikeLogAnimation(current, max);
	};
}

void SpikeLog::initializePositions()
{
	super::initializePositions();

	// this->spikedLog->setPositionY(this->properties->at(GameObject::MapKeyHeight).asFloat() / 2.0f);
	this->logCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
	this->spikeCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
}

Vec2 SpikeLog::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void SpikeLog::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::HackableCodeInfo(
				SpikeLog::MapKey,
				Strings::Menus_Hacking_Objects_SpikeLog_IncrementAnimationFrame_IncrementAnimationFrame::create(),
				UIResources::Menus_Icons_Banner,
				SpikeLogSetRotationPreview::create(),
				{
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_SpikeLog_IncrementAnimationFrame_RegisterEcx::create() },
				},
				int(HackFlags::None),
				16.0f,
				0.0f
			)
		},
	};

	auto incrementAnimationFunc = &SpikeLog::incrementSpikeLogAnimation;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)incrementAnimationFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* SpikeLog::createDefaultPreview()
{
	return SpikeLogGenericPreview::create();
}

NO_OPTIMIZE int SpikeLog::incrementSpikeLogAnimation(int count, int max)
{
	this->spikeCollision->setPhysicsEnabled(true);
	float offsetX = 0;

	switch(count)
	{
		case 1:
		{
			offsetX = 32.0f;
			break;
		}
		case 2:
		{
			offsetX = 96.0f;
			break;
		}
		case 3:
		{
			offsetX = 72.0f;
			break;
		}
		case 7:
		{
			offsetX = -72.0f;
			break;
		}
		case 8:
		{
			offsetX = -96.0f;
			break;
		}
		case 9:
		{
			offsetX = -32.0f;
			break;
		}
		default:
		{
			this->spikeCollision->setPhysicsEnabled(false);
		}
	}

	this->spikeCollision->setPositionX(offsetX);

	ASM(push ZCX)
	ASM_MOV_REG_VAR(ZCX, count);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(inc ZCX)
	ASM_NOP6();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(count, ZCX);
	ASM(pop ZCX);

	HACKABLES_STOP_SEARCH();

	return count;
}
END_NO_OPTIMIZE
