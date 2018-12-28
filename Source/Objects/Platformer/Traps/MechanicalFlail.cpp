#include "MechanicalFlail.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ParticleResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string MechanicalFlail::MapKeyMechanicalFlail = "mechanical-flail";

const float MechanicalFlail::DefaultAngle = 90.0f;
const float MechanicalFlail::SwingsPerSecondAt480Length = 1.5f;
const float MechanicalFlail::MinAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float MechanicalFlail::MaxAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle + 45.0f, 0.0f, 360.0f);

MechanicalFlail* MechanicalFlail::create(ValueMap* initProperties)
{
	MechanicalFlail* instance = new MechanicalFlail(initProperties);

	instance->autorelease();

	return instance;
}

MechanicalFlail::MechanicalFlail(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->joint = Sprite::create(ObjectResources::Traps_MechanicalFlail_Joint);
	this->flailChain = Node::create();

	float width = this->properties->at(SerializableObject::MapKeyWidth).asFloat();
	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();
	this->size = Size(width, height);

	this->targetAngle = MechanicalFlail::DefaultAngle;
	this->flailHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->flailChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->registerHackables();
	this->buildChain();

	this->addChild(this->flailChain);
	this->addChild(this->joint);
}

MechanicalFlail::~MechanicalFlail()
{
}

void MechanicalFlail::registerHackables()
{
	this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, &typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	this->registerData(this->hackableDataTargetAngle);

	auto swingFunc = &MechanicalFlail::swingToAngle;
	void* swingFuncPtr = (void*&)swingFunc;
	std::vector<HackableCode*> hackables = HackableCode::create(swingFuncPtr);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->hackableDataTargetAngle->registerCode(*it);
	}
}

Vec2 MechanicalFlail::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void MechanicalFlail::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
	this->startSwing();
}

void MechanicalFlail::initializePositions()
{
	HackableObject::initializePositions();

	this->joint->setPositionY(-this->flailHeight / 2.0f);
	this->flailChain->setPositionY(-this->flailHeight / 2.0f);
}

void MechanicalFlail::update(float dt)
{
	HackableObject::update(dt);
}

void MechanicalFlail::startSwing()
{
	swingToAngle(MechanicalFlail::MinAngle);
}

void MechanicalFlail::swingToAngle(float angle)
{
	const float arc = (MechanicalFlail::MaxAngle - MechanicalFlail::MinAngle);
	const float minDuration = 0.5f;
	const float maxDuration = 5.0f;

	float previousAngle = this->targetAngle;
	int angleInt = (int)angle;

	ASM(push EAX);
	ASM(push EBX);
	ASM(mov EAX, angleInt);

	HACKABLE_CODE_BEGIN();
	ASM(mov EBX, EAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM(mov angleInt, EBX);

	ASM(pop EBX);
	ASM(pop EAX);

	this->targetAngle = MathUtils::wrappingNormalize((float)angleInt, 0.0f, 360.0f);

	float speedMultiplier = (this->flailHeight / 480.0f) * MechanicalFlail::SwingsPerSecondAt480Length;

	float angleDelta = std::abs(previousAngle - this->targetAngle);
	float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / MechanicalFlail::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + MechanicalFlail::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->flailChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				if (this->targetAngle > (MechanicalFlail::MaxAngle + MechanicalFlail::MinAngle) / 2.0f)
				{
					this->swingToAngle(MechanicalFlail::MinAngle);
				}
				else
				{
					this->swingToAngle(MechanicalFlail::MaxAngle);
				}
			}),
			nullptr
		)
	);

	HACKABLES_STOP_SEARCH();
}

void MechanicalFlail::buildChain()
{
	float remainingHeight = this->flailHeight;
	int index = 0;

	Sprite* flail = Sprite::create(ObjectResources::Traps_MechanicalFlail_STEEL_BALL);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextPipeLink = Sprite::create(ObjectResources::Traps_MechanicalFlail_Shaft);

		nextPipeLink->setAnchorPoint(Vec2(0.5f, 0.0f));

		this->flailChain->addChild(nextPipeLink);

		nextPipeLink->setPositionY((float)index++ * (nextPipeLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextPipeLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	flail->setPositionY(this->flailHeight);

	this->flailChain->addChild(flail);
}
