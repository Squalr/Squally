#include "PendulumBlade.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ParticleResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PendulumBlade::MapKeyPendulumBlade = "pendulum-blade";

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
	float width = this->properties->at(SerializableObject::MapKeyWidth).asFloat();
	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();
	this->size = Size(width, height);

	this->chainHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->bladeChain->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->pendulumBladeSpeed = Vec2::ZERO;

	this->registerHackables();
	this->buildChain();

	this->addChild(this->neck);
	this->addChild(this->bladeChain);
}

PendulumBlade::~PendulumBlade()
{
}

void PendulumBlade::registerHackables()
{
	this->pendulumBladeDataSpeedY = HackableData::create("Y Position", &this->pendulumBladeSpeed.y, &typeid(this->pendulumBladeSpeed.y), UIResources::Menus_Icons_AlchemyPot);
	this->registerData(this->pendulumBladeDataSpeedY);
}

Vec2 PendulumBlade::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void PendulumBlade::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void PendulumBlade::initializePositions()
{
	HackableObject::initializePositions();

	const float neckOfffset = 8.0f;

	this->neck->setPositionY(this->chainHeight / 2.0f + neckOfffset);
	this->bladeChain->setPositionY(this->chainHeight / 2.0f);
}

void PendulumBlade::update(float dt)
{
	static float deltaTime = 0.0f;
	float maxAngle = 65.0f;
	float gravity = 9.8f;
	float speed = 5.5f;

	deltaTime += dt;

	// the formula for the angle
	float theta = maxAngle * std::sin(std::sqrt(gravity / this->chainHeight) * deltaTime * speed);

	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	Vec2 tspeed = Vec2::ZERO;
	Vec2 currentSpeed = this->pendulumBladeSpeed;

	ASM(push ebx);
	ASM(mov ebx, currentSpeed.y);

	HACKABLE_CODE_BEGIN(assemblyAddressStart, PendulumBladeSpeedYStart);
	ASM(mov tspeed.y, ebx)
	HACKABLE_CODE_END(assemblyAddressEnd, PendulumBladeSpeedYEnd);

	ASM(pop ebx);

	this->pendulumBladeDataSpeedY->registerCode(assemblyAddressStart, assemblyAddressEnd, "Pendulum Theta", UIResources::Menus_Icons_AxeSlash);

	// set the angle
	this->bladeChain->setRotation(theta);
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
