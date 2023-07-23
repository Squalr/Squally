#include "Smoke.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Smoke::MapKey = "smoke";

Smoke* Smoke::create(ValueMap& properties)
{
	Smoke* instance = new Smoke(properties);

	instance->autorelease();

	return instance;
}

Smoke::Smoke(ValueMap& properties) : super(properties)
{
	this->smoke = SmartAnimationSequenceNode::create(FXResources::Smoke_Smoke_0000);

	this->addChild(this->smoke);
}

Smoke::~Smoke()
{
}

void Smoke::onEnter()
{
	super::onEnter();

	this->smoke->playAnimationRepeat(FXResources::Smoke_Smoke_0000, 0.07f);
}

void Smoke::initializePositions()
{
	super::initializePositions();

	this->smoke->setPosition(Vec2(0.0f, 0.0f));
}
