#include "HeavenHug.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugGenericPreview.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugSetSpeedPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/HeavenHug/GetTravelHeight/GetTravelHeight.h"
#include "Strings/Hacking/Objects/HeavenHug/GetTravelHeight/RegisterEax.h"
#include "Strings/Hacking/Objects/RegisterRbpWarning.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TRAVEL_HEIGHT 1

const std::string HeavenHug::MapKeyHeavenHug = "heaven-hug";
const float HeavenHug::SpeedPer480Px = 2.0f;

HeavenHug* HeavenHug::create(ValueMap& initProperties)
{
	HeavenHug* instance = new HeavenHug(initProperties);

	instance->autorelease();

	return instance;
}

HeavenHug::HeavenHug(ValueMap& initProperties) : super(initProperties)
{
	this->heavenHugContainer = Node::create();
	this->heavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_HEAVEN_HUG);
	this->spikeCollision = CollisionObject::create(this->createSpikeCollision(), (CollisionType)PlatformerCollisionType::Damage, false, false);

	this->travelDistance = this->properties.at(SerializableObject::MapKeyHeight).asFloat();

	this->heavenHugContainer->addChild(this->heavenHug);
	this->heavenHug->addChild(this->spikeCollision);
	this->addChild(this->heavenHugContainer);
}

HeavenHug::~HeavenHug()
{
}

void HeavenHug::onEnter()
{
	super::onEnter();

	this->updateHeavenHug();
}

void HeavenHug::initializePositions()
{
	super::initializePositions();

	this->heavenHugContainer->setPositionY(this->properties.at(SerializableObject::MapKeyHeight).asFloat() / 2.0f);
	this->spikeCollision->setPosition(Vec2(this->heavenHug->getContentSize().width / 2.0f, 32.0f));
}

Vec2 HeavenHug::getButtonOffset()
{
	return Vec2(0.0f, this->heavenHug->getPositionY() + 196.0f);
}

void HeavenHug::registerHackables()
{
	super::registerHackables();

	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_TRAVEL_HEIGHT,
			HackableCode::LateBindData(
				HeavenHug::MapKeyHeavenHug,
				Strings::Hacking_Objects_HeavenHug_GetTravelHeight_GetTravelHeight::create(),
				UIResources::Menus_Icons_BleedingLimb,
				HeavenHugSetSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Hacking_Objects_HeavenHug_GetTravelHeight_RegisterEax::create() },
					{ HackableCode::Register::zbp, Strings::Hacking_Objects_RegisterRbpWarning::create() }
				},
				1,
				20.0f
			)
		},
	};

	auto getHeightFunc = &HeavenHug::getTravelHeight;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)getHeightFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* HeavenHug::createDefaultPreview()
{
	return HeavenHugGenericPreview::create();
}

void HeavenHug::updateHeavenHug()
{
	float duration = MathUtils::clamp(this->travelDistance / (480.0f * HeavenHug::SpeedPer480Px), 0.25f, 10.0f);

	if (this->heavenHug->getPositionY() >= 0.0f)
	{
		float delta = this->getTravelHeight();

		this->heavenHug->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(duration, Vec2(0.0f, -delta))),
			CallFunc::create([=]() { this->updateHeavenHug(); }),
			nullptr
		));
	}
	else
	{
		this->heavenHug->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(duration, Vec2::ZERO)),
			CallFunc::create([=]() { this->updateHeavenHug(); }),
			nullptr
		));
	}
}

NO_OPTIMIZE float HeavenHug::getTravelHeight()
{
	static volatile float* travelDistPtr = new float();
	static volatile float retVal;

	*travelDistPtr = this->travelDistance;
	retVal = *travelDistPtr;

	ASM(push ZAX)
	ASM_MOV_REG_VAR(ZAX, travelDistPtr);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TRAVEL_HEIGHT);
	ASM(fld dword ptr [ZAX])
	ASM_NOP12();
	HACKABLE_CODE_END();
	ASM(fstp dword ptr [ZAX])
	ASM(mov ZAX, [ZAX])
	ASM_MOV_VAR_REG(retVal, ZAX);
	ASM(pop ZAX)
	HACKABLES_STOP_SEARCH();

	return retVal;
}

PhysicsBody* HeavenHug::createSpikeCollision()
{
	PhysicsBody* physicsBody = PhysicsBody::createBox(Size(180.0f, 32.0f));

	return physicsBody;
}
