#include "Airship2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Airship2::MapKey = "airship-2";

Airship2* Airship2::create(ValueMap& properties)
{
	Airship2* instance = new Airship2(properties);

	instance->autorelease();

	return instance;
}

Airship2::Airship2(ValueMap& properties) : super(properties)
{
	this->animations = SmartAnimationNode::create(ObjectResources::Transportation_Airship2_Animations);

	this->animations->setFlippedX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool());
	
	this->addChild(this->animations);
}

Airship2::~Airship2()
{
}

void Airship2::onEnter()
{
	super::onEnter();

	this->animations->playAnimation();

	this->scheduleUpdate();
}

void Airship2::update(float dt)
{
	super::update(dt);

	const float Speed = 312.0f;

	this->animations->setPositionX(this->animations->getPositionX() + (this->animations->getFlippedX() ? Speed : -Speed) * dt);
}
