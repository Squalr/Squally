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
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/HeavenHug/RegisterEax.h"
#include "Strings/Hacking/Objects/HeavenHug/RegisterEbx.h"
#include "Strings/Hacking/Objects/HeavenHug/SetSpeed.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string HeavenHug::MapKeyHeavenHug = "pendulum-blade";

const float HeavenHug::DefaultAngle = 270.0f;
const float HeavenHug::SwingsPerSecondAt480Length = 1.5f;
const float HeavenHug::MinAngle = MathUtils::wrappingNormalize(HeavenHug::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float HeavenHug::MaxAngle = MathUtils::wrappingNormalize(HeavenHug::DefaultAngle + 45.0f, 0.0f, 360.0f);

HeavenHug* HeavenHug::create(ValueMap* initProperties)
{
	HeavenHug* instance = new HeavenHug(initProperties);

	instance->autorelease();

	return instance;
}

HeavenHug::HeavenHug(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->neck = Sprite::create(ObjectResources::Traps_PendulumBlade_Neck);
	this->bladeChain = Node::create();
	this->bladeCollision = CollisionObject::create(this->createBladeCollision(), (CollisionType)PlatformerCollisionType::Damage, false, false);
	this->setDefaultPreview(HeavenHugGenericPreview::create());

	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->targetAngle = HeavenHug::DefaultAngle;
	this->chainHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->bladeChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->registerHackables();
	this->buildChain();

	this->bladeChain->addChild(this->bladeCollision);
	this->addChild(this->neck);
	this->addChild(this->bladeChain);
}

HeavenHug::~HeavenHug()
{
}

void HeavenHug::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->startSwing();
}

void HeavenHug::initializePositions()
{
	super::initializePositions();

	const float neckOfffset = 8.0f;

	this->bladeCollision->setPositionY(-this->chainHeight);
	this->neck->setPositionY(this->chainHeight / 2.0f + neckOfffset);
	this->bladeChain->setPositionY(this->chainHeight / 2.0f);
}

void HeavenHug::update(float dt)
{
	super::update(dt);
}

void HeavenHug::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::LateBindData(
				Strings::Hacking_Objects_HeavenHug_SetSpeed::create(),
				UIResources::Menus_Icons_CrossHair,
				HeavenHugSetSpeedPreview::create(),
				{
					{ HackableCode::Register::eax, Strings::Hacking_Objects_HeavenHug_RegisterEax::create() },
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_HeavenHug_RegisterEbx::create() }
				}
			)
		},
	};

	auto swingFunc = &HeavenHug::swingToAngle;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 HeavenHug::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void HeavenHug::startSwing()
{
	swingToAngle(HeavenHug::MinAngle);
}

void HeavenHug::swingToAngle(float angle)
{
	const float arc = (HeavenHug::MaxAngle - HeavenHug::MinAngle);
	const float minDuration = 0.5f;
	const float maxDuration = 5.0f;

	volatile float previousAngle = this->targetAngle;
	volatile int previousAngleInt = (int)previousAngle;
	volatile int angleInt = (int)angle;

	ASM(push EAX);
	ASM(push EBX);
	ASM_MOV_REG_VAR(EAX, angleInt);
	ASM_MOV_REG_VAR(EBX, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SWING);
	ASM(mov EBX, EAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, EBX);

	ASM(pop EBX);
	ASM(pop EAX);

	this->targetAngle = MathUtils::wrappingNormalize((float)angleInt, 0.0f, 360.0f);

	volatile float speedMultiplier = (this->chainHeight / 480.0f) * HeavenHug::SwingsPerSecondAt480Length;

	volatile float angleDelta = std::abs(previousAngle - this->targetAngle);
	volatile float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / HeavenHug::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	volatile float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + HeavenHug::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->bladeChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				if (this->targetAngle > (HeavenHug::MaxAngle + HeavenHug::MinAngle) / 2.0f)
				{
					this->swingToAngle(HeavenHug::MinAngle);
				}
				else
				{
					this->swingToAngle(HeavenHug::MaxAngle);
				}
			}),
			nullptr
		)
	);

	HACKABLES_STOP_SEARCH();
}

void HeavenHug::buildChain()
{
	float remainingHeight = this->chainHeight;
	int index = 0;

	Sprite* blade = Sprite::create(ObjectResources::Traps_PendulumBlade_Blade);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextChainLink = Sprite::create(ObjectResources::Traps_PendulumBlade_Chain);

		nextChainLink->setAnchorPoint(Vec2(0.5f, 1.0f));

		this->bladeChain->addChild(nextChainLink);

		nextChainLink->setPositionY((float)index++ * -(nextChainLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextChainLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	blade->setPositionY(-this->chainHeight);

	this->bladeChain->addChild(blade);
}

PhysicsBody* HeavenHug::createBladeCollision()
{
	// Polygons can't be concave, so we get around this by building the left and right sides of the blade separately

	std::vector<Vec2> leftPoints = std::vector<Vec2>();

	leftPoints.push_back(Vec2(0.0f, 8.0f));
	leftPoints.push_back(Vec2(-212.0f, 64.0f));
	leftPoints.push_back(Vec2(-160.0f, -32.0f));
	leftPoints.push_back(Vec2(-96.0f, -64.0f));
	leftPoints.push_back(Vec2(0.0f, -80.0f));

	std::vector<Vec2> rightPoints = std::vector<Vec2>();

	rightPoints.push_back(Vec2(0.0f, 8.0f));
	rightPoints.push_back(Vec2(212.0f, 64.0f));
	rightPoints.push_back(Vec2(160.0f, -32.0f));
	rightPoints.push_back(Vec2(96.0f, -64.0f));
	rightPoints.push_back(Vec2(0.0f, -80.0f));

	PhysicsBody* physicsBody = PhysicsBody::createPolygon(leftPoints.data(), leftPoints.size());

	physicsBody->addShape(PhysicsShapePolygon::create(rightPoints.data(), rightPoints.size()));

	return physicsBody;
}
