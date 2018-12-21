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
	this->bladeChain = Node::create();

	float width = this->properties->at(SerializableObject::MapKeyWidth).asFloat();
	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	// I'm actually at a bit of a loss here -- apparently we have to undo the tiled => cocos coordinate mapping done in SerializableObject???
	this->setPositionY(this->getPositionY() + this->properties->at(SerializableObject::MapKeyHeight).asFloat() / 2.0f);

	this->chainHeight = height;

	this->bladeChain->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->size = Size(width, height);
	this->pendulumBladeSpeed = Vec2::ZERO;

	this->registerHackables();
	this->buildChain();

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

void PendulumBlade::update(float dt)
{
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	Vec2 speed = Vec2::ZERO;
	Vec2 currentSpeed = this->pendulumBladeSpeed;

	ASM(push ebx);
	ASM(mov ebx, currentSpeed.y);

	HACKABLE_CODE_BEGIN(assemblyAddressStart, PendulumBladeSpeedYStart);
	ASM(mov speed.y, ebx)
	HACKABLE_CODE_END(assemblyAddressEnd, PendulumBladeSpeedYEnd);

	ASM(pop ebx);

	float angle = speed.x == 0.0f ? (speed.y > 0.0f ? -90.0f : 90.0f) : atan(speed.y / speed.x);

	this->pendulumBladeDataSpeedY->registerCode(assemblyAddressStart, assemblyAddressEnd, "Pendulum Angular Velocity", UIResources::Menus_Icons_AxeSlash);
}

void PendulumBlade::buildChain()
{
	float remainingHeight = this->chainHeight;
	int index = 0;

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextChainLink = Sprite::create(ObjectResources::Traps_CHAIN_HUG);

		this->bladeChain->addChild(nextChainLink);

		nextChainLink->setPositionY((float)index++ * -(nextChainLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextChainLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);
}
