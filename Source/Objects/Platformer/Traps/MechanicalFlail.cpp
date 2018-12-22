#include "MechanicalFlail.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"

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
	this->pendulumBladeDataSpeedY = HackableData::create("Y Position", &this->pendulumBladeSpeed.y, &typeid(this->pendulumBladeSpeed.y), UIResources::Menus_Icons_AlchemyPot);
	this->registerData(this->pendulumBladeDataSpeedY);
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
	static float deltaTime = 0.0f;
	float maxAngle = 90.0f;
	float gravity = 9.8f;
	float speed = 4.0f;

	deltaTime += dt;

	// the formula for the angle
	float theta = maxAngle * std::sin(std::sqrt(gravity / this->flailHeight) * deltaTime * speed);

	// set the angle
	this->flailChain->setRotation(180.0f + theta);

	/*
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	Vec2 speed = Vec2::ZERO;
	Vec2 currentSpeed = this->pendulumBladeSpeed;

	ASM(push ebx);
	ASM(mov ebx, currentSpeed.y);

	HACKABLE_CODE_BEGIN(assemblyAddressStart, MechanicalFlailSpeedYStart);
	ASM(mov speed.y, ebx)
	HACKABLE_CODE_END(assemblyAddressEnd, MechanicalFlailSpeedYEnd);

	ASM(pop ebx);

	float angle = speed.x == 0.0f ? (speed.y > 0.0f ? -90.0f : 90.0f) : atan(speed.y / speed.x);

	this->pendulumBladeDataSpeedY->registerCode(assemblyAddressStart, assemblyAddressEnd, "Pendulum Angular Velocity", UIResources::Menus_Icons_AxeSlash);*/
}

void MechanicalFlail::buildChain()
{
	float remainingHeight = this->flailHeight;
	int index = 0;

	Sprite* flail = Sprite::create(ObjectResources::Traps_MechanicalFlail_STEEL_BALL);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextChainLink = Sprite::create(ObjectResources::Traps_MechanicalFlail_Shaft);

		nextChainLink->setAnchorPoint(Vec2(0.5f, 1.0f));

		this->flailChain->addChild(nextChainLink);

		nextChainLink->setPositionY((float)index++ * -(nextChainLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextChainLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	flail->setPositionY(-this->flailHeight);

	this->flailChain->addChild(flail);
}
