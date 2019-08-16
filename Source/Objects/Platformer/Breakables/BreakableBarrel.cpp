#include "BreakableBarrel.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string BreakableBarrel::MapKeyBreakableBarrel = "breakable-barrel";

BreakableBarrel* BreakableBarrel::create(ValueMap& properties)
{
	BreakableBarrel* instance = new BreakableBarrel(properties);

	instance->autorelease();

	return instance;
}

BreakableBarrel::BreakableBarrel(ValueMap& properties) : super(properties, Size(128.0f, 212.0f), 1)
{
	this->barrelSprite = Sprite::create(ObjectResources::Doors_Tent_BARREL);
	this->explosion = SmartAnimationSequenceNode::create();

	this->addChild(this->barrelSprite);
	this->addChild(this->explosion);
}

BreakableBarrel::~BreakableBarrel()
{
}

void BreakableBarrel::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void BreakableBarrel::initializePositions()
{
	super::initializePositions();
}

void BreakableBarrel::initializeListeners()
{
	super::initializeListeners();
}

void BreakableBarrel::onBreak()
{
	this->explosion->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	this->barrelSprite->setVisible(false);
}
