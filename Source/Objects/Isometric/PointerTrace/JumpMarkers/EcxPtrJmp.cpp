#include "EcxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEcx.h"
#include "Strings/PointerTrace/Assembly/RegisterRcx.h"

using namespace cocos2d;

const std::string EcxPtrJmp::MapKeyEcxPtrJmp = "ecx-ptr-jmp";

EcxPtrJmp* EcxPtrJmp::create(ValueMap& initProperties)
{
	EcxPtrJmp* instance = new EcxPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EcxPtrJmp::EcxPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEcx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRcx::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EcxPtrJmp::~EcxPtrJmp()
{
}

void EcxPtrJmp::onEnter()
{
	super::onEnter();
}

void EcxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EcxPtrJmp::getJumpDestination()
{
	return RegisterState::getRegisterEcx();
}
