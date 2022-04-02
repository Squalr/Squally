#include "Airship.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Airship::MapKey = "airship";
const std::string Airship::PropertyVariant = "variant";
const std::string Airship::PropertySpeed = "speed";

Airship* Airship::create(ValueMap& properties)
{
	Airship* instance = new Airship(properties);

	instance->autorelease();

	return instance;
}

Airship::Airship(ValueMap& properties) : super(properties)
{
	int variant = GameUtils::getKeyOrDefault(this->properties, Airship::PropertyVariant, Value(0)).asInt();

	switch(variant)
	{
		default:
		case 0:
		{
			this->animations = SmartAnimationNode::create(ObjectResources::Transportation_Airship1_Animations);
			break;
		}
		case 1:
		{
			this->animations = SmartAnimationNode::create(ObjectResources::Transportation_Airship2_Animations);
			break;
		}
	}

	this->speed = GameUtils::getKeyOrDefault(this->properties, Airship::PropertySpeed, Value(this->speed)).asFloat();

	this->animations->setFlippedX(this->speed < 0.0f);
	
	this->addChild(this->animations);
}

Airship::~Airship()
{
}

void Airship::onEnter()
{
	super::onEnter();

	this->animations->playAnimation();

	if (this->speed != 0.0f)
	{
		this->scheduleUpdate();
	}
}

void Airship::update(float dt)
{
	super::update(dt);

	const CRect MapBounds = GameCamera::getInstance()->getMapBounds();
	const float Buffer = 4096.0f;
	const float LeftWrap = MapBounds.origin.x - Buffer;
	const float RightWrap = MapBounds.origin.x + MapBounds.size.width + Buffer;

	this->setPositionX(this->getPositionX() + this->speed * dt);

	if (this->speed < 0.0f && this->getPositionX() < LeftWrap)
	{
		this->setPositionX(RightWrap);
	}
	else if (this->speed > 0.0f && this->getPositionX() > RightWrap)
	{
		this->setPositionX(LeftWrap);
	}
}
