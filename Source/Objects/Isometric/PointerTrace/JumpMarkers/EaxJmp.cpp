#include "EaxJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEax.h"
#include "Strings/PointerTrace/Assembly/RegisterRax.h"

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
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEax::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRax::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
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

int EaxJmp::getJumpDestination()
{
	return 0;
}
