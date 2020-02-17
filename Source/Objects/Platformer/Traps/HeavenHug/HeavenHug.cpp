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
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TRAVEL_HEIGHT 1

const std::string HeavenHug::MapKeyHeavenHug = "heaven-hug";
const float HeavenHug::SpeedPer480Px = 2.0f;

HeavenHug* HeavenHug::create(ValueMap& properties)
{
	HeavenHug* instance = new HeavenHug(properties);

	instance->autorelease();

	return instance;
}

HeavenHug::HeavenHug(ValueMap& properties) : super(properties)
{
	this->heavenHugContainer = Node::create();
	this->heavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_HEAVEN_HUG);
	this->spikeCollision = CollisionObject::create(this->createSpikeCollision(), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	this->travelDistance = this->properties.at(GameObject::MapKeyHeight).asFloat();

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

	this->heavenHugContainer->setPositionY(this->properties.at(GameObject::MapKeyHeight).asFloat() / 2.0f);
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

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_TRAVEL_HEIGHT,
			HackableCode::HackableCodeInfo(
				HeavenHug::MapKeyHeavenHug,
				Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_GetTravelHeight::create(),
				UIResources::Menus_Icons_BleedingLimb,
				HeavenHugSetSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_RegisterEax::create() },
					{ HackableCode::Register::zbp, Strings::Menus_Hacking_Objects_RegisterRbpWarning::create() }
				},
				int(HackFlags::Gravity),
				20.0f,
				0.0f
			)
		},
	};

	auto getHeightFunc = &HeavenHug::getTravelHeight;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)getHeightFunc, codeInfoMap);

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
END_NO_OPTIMIZE

std::vector<Vec2>& HeavenHug::createSpikeCollision()
{
	return std::vector<Vec2>();
}
