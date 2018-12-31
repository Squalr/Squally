#include "PendulumBlade.h"

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
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Objects/Hackables/PendulumBlade/PendulumTargetAngle.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string PendulumBlade::MapKeyPendulumBlade = "pendulum-blade";

const float PendulumBlade::DefaultAngle = 270.0f;
const float PendulumBlade::SwingsPerSecondAt480Length = 1.5f;
const float PendulumBlade::MinAngle = MathUtils::wrappingNormalize(PendulumBlade::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float PendulumBlade::MaxAngle = MathUtils::wrappingNormalize(PendulumBlade::DefaultAngle + 45.0f, 0.0f, 360.0f);

PendulumBlade* PendulumBlade::create(ValueMap* initProperties)
{
	PendulumBlade* instance = new PendulumBlade(initProperties);

	instance->autorelease();

	return instance;
}

PendulumBlade::PendulumBlade(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->neck = Sprite::create(ObjectResources::Traps_PendulumBlade_Neck);
	this->bladeChain = Node::create();
	this->bladeCollision = CollisionObject::create(this->createBladeCollision(), (CollisionType)PlatformerCollisionType::Damage, false, false);

	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->targetAngle = PendulumBlade::DefaultAngle;
	this->chainHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->bladeChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->registerHackables();
	this->buildChain();

	this->bladeChain->addChild(this->bladeCollision);
	this->addChild(this->neck);
	this->addChild(this->bladeChain);
}

PendulumBlade::~PendulumBlade()
{
}

void PendulumBlade::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->startSwing();
}

void PendulumBlade::initializePositions()
{
	super::initializePositions();

	const float neckOfffset = 8.0f;

	this->bladeCollision->setPositionY(-this->chainHeight);
	this->neck->setPositionY(this->chainHeight / 2.0f + neckOfffset);
	this->bladeChain->setPositionY(this->chainHeight / 2.0f);
}

void PendulumBlade::update(float dt)
{
	super::update(dt);
}

void PendulumBlade::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{ LOCAL_FUNC_ID_SWING, HackableCode::LateBindData(LocaleStrings::PendulumTargetAngle::create(), UIResources::Menus_Icons_CrossHair)},
	};

	auto swingFunc = &PendulumBlade::swingToAngle;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 PendulumBlade::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void PendulumBlade::startSwing()
{
	swingToAngle(PendulumBlade::MinAngle);
}

void PendulumBlade::swingToAngle(float angle)
{
	const float arc = (PendulumBlade::MaxAngle - PendulumBlade::MinAngle);
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

	volatile float speedMultiplier = (this->chainHeight / 480.0f) * PendulumBlade::SwingsPerSecondAt480Length;

	volatile float angleDelta = std::abs(previousAngle - this->targetAngle);
	volatile float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / PendulumBlade::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	volatile float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + PendulumBlade::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->bladeChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				if (this->targetAngle > (PendulumBlade::MaxAngle + PendulumBlade::MinAngle) / 2.0f)
				{
					this->swingToAngle(PendulumBlade::MinAngle);
				}
				else
				{
					this->swingToAngle(PendulumBlade::MaxAngle);
				}
			}),
			nullptr
		)
	);

	HACKABLES_STOP_SEARCH();
}

void PendulumBlade::buildChain()
{
	float remainingHeight = this->chainHeight;
	int index = 0;

	Sprite* blade = Sprite::create(ObjectResources::Traps_PendulumBlade_Blade);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextChainLink = Sprite::create(ObjectResources::Traps_CHAIN_HUG);

		nextChainLink->setAnchorPoint(Vec2(0.5f, 1.0f));

		this->bladeChain->addChild(nextChainLink);

		nextChainLink->setPositionY((float)index++ * -(nextChainLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextChainLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	blade->setPositionY(-this->chainHeight);

	this->bladeChain->addChild(blade);
}

PhysicsBody* PendulumBlade::createBladeCollision()
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
