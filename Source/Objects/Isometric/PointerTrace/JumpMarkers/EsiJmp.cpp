#include "EsiJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsi.h"
#include "Strings/PointerTrace/Assembly/RegisterRsi.h"

using namespace cocos2d;

const std::string EsiJmp::MapKeyEsiJmp = "esi-jmp";

EsiJmp* EsiJmp::create(ValueMap& properties)
{
	EsiJmp* instance = new EsiJmp(properties);

	instance->autorelease();

	return instance;
}

EsiJmp::EsiJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsi::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsi::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EsiJmp::~EsiJmp()
{
}

void EsiJmp::onEnter()
{
	super::onEnter();
}

void EsiJmp::initializePositions()
{
	super::initializePositions();
}

int EsiJmp::getJumpDestination()
{
	return RegisterState::getRegisterEsi();
}
