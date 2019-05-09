#include "EcxJmp.h"

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

const std::string EcxJmp::MapKeyEcxJmp = "ecx-jmp";

EcxJmp* EcxJmp::create(ValueMap& initProperties)
{
	EcxJmp* instance = new EcxJmp(initProperties);

	instance->autorelease();

	return instance;
}

EcxJmp::EcxJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEcx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRcx::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EcxJmp::~EcxJmp()
{
}

void EcxJmp::onEnter()
{
	super::onEnter();
}

void EcxJmp::initializePositions()
{
	super::initializePositions();
}

int EcxJmp::getJumpDestination()
{
	return RegisterState::getRegisterEcx();
}
