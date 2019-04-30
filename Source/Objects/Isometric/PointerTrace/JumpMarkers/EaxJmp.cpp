#include "EaxJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EaxJmp::MapKeyEaxJmp = "eax-jmp";

EaxJmp* EaxJmp::create(ValueMap& initProperties)
{
	EaxJmp* instance = new EaxJmp(initProperties);

	instance->autorelease();

	return instance;
}

EaxJmp::EaxJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxJmp);

	this->addChild(this->marker);
}

EaxJmp::~EaxJmp()
{
}

void EaxJmp::onEnter()
{
	super::onEnter();
}

void EaxJmp::initializePositions()
{
	super::initializePositions();
}
