#include "MechanicalFlail.h"

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

	this->flailHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->flailChain->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->pendulumBladeSpeed = Vec2::ZERO;

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
	this->pendulumBladeDataSpeedY = HackableData::create("Y Position", &this->pendulumBladeSpeed.y, &typeid(this->pendulumBladeSpeed.y), UIResources::Menus_Icons_AxeSlash);
	this->registerData(this->pendulumBladeDataSpeedY);

	auto swingFunc = &MechanicalFlail::updateSwing;
	void* swingFuncPtr = (void*&)swingFunc;
	std::vector<HackableCode*> hackables = HackableCode::create(swingFuncPtr);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->pendulumBladeDataSpeedY->registerCode(*it);
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

	this->updateSwing(dt);
}

void MechanicalFlail::updateSwing(float dt)
{
	static float deltaTime = 0.0f;
	const float defaultAngle = 90.0f;
	float maxAngle = 65.0f;
	float gravity = 9.8f;
	float speed = 5.5f;

	deltaTime += dt;

	float theta = MathUtils::wrappingNormalize(180.0f + maxAngle * std::sin(std::sqrt(gravity / this->flailHeight) * deltaTime * speed) - defaultAngle, 0.0f, 360.0f);
	int thetaInt = (int)theta;

	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	ASM(push EAX);
	ASM(push EBX);
	ASM(mov EAX, thetaInt);

	HACKABLE_CODE_BEGIN();
	ASM(mov EBX, EAX);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM(mov thetaInt, EBX);

	ASM(pop EBX);
	ASM(pop EAX);

	HACKABLES_STOP_SEARCH();

	theta = MathUtils::wrappingNormalize((float)thetaInt + defaultAngle, 0.0f, 360.0f);

	// set the angle
	this->flailChain->setRotation(theta);
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

		nextPipeLink->setAnchorPoint(Vec2(0.5f, 1.0f));

		this->flailChain->addChild(nextPipeLink);

		nextPipeLink->setPositionY((float)index++ * -(nextPipeLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextPipeLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	flail->setPositionY(-this->flailHeight);

	this->flailChain->addChild(flail);
}
