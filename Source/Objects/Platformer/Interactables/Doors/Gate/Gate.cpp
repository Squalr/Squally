#include "Gate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Gate::MapKey = "gate";
const Vec2 Gate::GateLeftClosedOffset = Vec2(-128.0f, 16.0f);
const Vec2 Gate::GateRightClosedOffset = Vec2(128.0f, 16.0f);
const Vec2 Gate::GateLeftOpenedOffset = Vec2(-356.0f, 16.0f);
const Vec2 Gate::GateRightOpenedOffset = Vec2(356.0f, 16.0f);

Gate* Gate::create(ValueMap& properties)
{
	Gate* instance = new Gate(properties);

	instance->autorelease();

	return instance;
}

Gate::Gate(ValueMap& properties) : super(properties, Size(512.0f, 512.0f), Vec2(0.0f, 48.0f))
{
	this->gateRight = Sprite::create(ObjectResources::Doors_Gate_GateRight);
	this->gateLeft = Sprite::create(ObjectResources::Doors_Gate_GateLeft);

	this->contentNode->addChild(this->gateRight);
	this->contentNode->addChild(this->gateLeft);
}

Gate::~Gate()
{
}

void Gate::onEnter()
{
	super::onEnter();
}

void Gate::initializePositions()
{
	super::initializePositions();

	this->gateLeft->setPosition(Gate::GateLeftClosedOffset);
	this->gateRight->setPosition(Gate::GateRightClosedOffset);
}

void Gate::initializeListeners()
{
	super::initializeListeners();
}

Vec2 Gate::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* Gate::createDefaultPreview()
{
	return nullptr;
}

void Gate::lock(bool animate)
{
	super::lock(animate);

	this->gateLeft->setPosition(Gate::GateLeftClosedOffset);
	this->gateRight->setPosition(Gate::GateRightClosedOffset);

	this->gateLeft->setFlippedX(false);
	this->gateRight->setFlippedX(false);
}

void Gate::unlock(bool animate)
{
	super::unlock(animate);

	this->gateLeft->setPosition(Gate::GateLeftOpenedOffset);
	this->gateRight->setPosition(Gate::GateRightOpenedOffset);

	this->gateLeft->setFlippedX(true);
	this->gateRight->setFlippedX(true);
}
