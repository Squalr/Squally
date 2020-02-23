#include "Airship1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Airship1::MapKeyAirship1 = "airship-1";

Airship1* Airship1::create(ValueMap& properties)
{
	Airship1* instance = new Airship1(properties);

	instance->autorelease();

	return instance;
}

Airship1::Airship1(ValueMap& properties) : super(properties)
{
	this->animations = SmartAnimationNode::create(ObjectResources::Transportation_Airship1_Animations);

	this->animations->setFlippedX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool());
	
	this->addChild(this->animations);
}

Airship1::~Airship1()
{
}

void Airship1::onEnter()
{
	super::onEnter();

	this->animations->playAnimation();

	this->scheduleUpdate();
}

void Airship1::update(float dt)
{
	super::update(dt);

	const float Speed = 256.0f;

	this->animations->setPositionX(this->animations->getPositionX() + (this->animations->getFlippedX() ? Speed : -Speed) * dt);
}
