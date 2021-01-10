#include "LanternGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string LanternGate::MapKey = "lantern-gate";

LanternGate* LanternGate::create(ValueMap& properties)
{
	LanternGate* instance = new LanternGate(properties);

	instance->autorelease();

	return instance;
}

LanternGate::LanternGate(ValueMap& properties) : super(properties, Size(356.0f, 320.0f), Vec2(0.0f, 0.0f))
{
	this->gateRight = Sprite::create(ObjectResources::Doors_LanternGate_LanternOrangeRight);
	this->gateLeft = Sprite::create(ObjectResources::Doors_LanternGate_LanternOrangeLeft);

	this->contentNode->addChild(this->gateRight);
	this->contentNode->addChild(this->gateLeft);
}

LanternGate::~LanternGate()
{
}

void LanternGate::onEnter()
{
	super::onEnter();
}

void LanternGate::initializePositions()
{
	super::initializePositions();

	this->gateLeft->setPosition(Vec2(-160.0f, 16.0f));
	this->gateRight->setPosition(Vec2(160.0f, 16.0f));
}

void LanternGate::initializeListeners()
{
	super::initializeListeners();
}

Vec2 LanternGate::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* LanternGate::createDefaultPreview()
{
	return nullptr;
}
