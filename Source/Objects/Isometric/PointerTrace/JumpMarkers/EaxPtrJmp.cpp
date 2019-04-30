#include "EaxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EaxPtrJmp::MapKeyEaxPtrJmp = "eax-ptr-jmp";

EaxPtrJmp* EaxPtrJmp::create(ValueMap& initProperties)
{
	EaxPtrJmp* instance = new EaxPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EaxPtrJmp::EaxPtrJmp(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxPtrJmp);

	this->addChild(this->marker);
}

EaxPtrJmp::~EaxPtrJmp()
{
}

void EaxPtrJmp::onEnter()
{
	super::onEnter();
}

void EaxPtrJmp::initializePositions()
{
	super::initializePositions();
}
