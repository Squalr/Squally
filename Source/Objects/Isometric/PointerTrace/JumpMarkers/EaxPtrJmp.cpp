#include "EaxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEax.h"
#include "Strings/PointerTrace/Assembly/RegisterRax.h"

using namespace cocos2d;

const std::string EaxPtrJmp::MapKeyEaxPtrJmp = "eax-ptr-jmp";

EaxPtrJmp* EaxPtrJmp::create(ValueMap& initProperties)
{
	EaxPtrJmp* instance = new EaxPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EaxPtrJmp::EaxPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEax::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRax::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
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

int EaxPtrJmp::getJumpDestination()
{
	return RegisterState::getRegisterEax();
}
