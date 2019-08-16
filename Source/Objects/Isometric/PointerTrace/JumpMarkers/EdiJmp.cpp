#include "EdiJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdi.h"
#include "Strings/PointerTrace/Assembly/RegisterRdi.h"

using namespace cocos2d;

const std::string EdiJmp::MapKeyEdiJmp = "edi-jmp";

EdiJmp* EdiJmp::create(ValueMap& properties)
{
	EdiJmp* instance = new EdiJmp(properties);

	instance->autorelease();

	return instance;
}

EdiJmp::EdiJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdi::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdi::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EdiJmp::~EdiJmp()
{
}

void EdiJmp::onEnter()
{
	super::onEnter();
}

void EdiJmp::initializePositions()
{
	super::initializePositions();
}

int EdiJmp::getJumpDestination()
{
	return RegisterState::getRegisterEdi();
}
