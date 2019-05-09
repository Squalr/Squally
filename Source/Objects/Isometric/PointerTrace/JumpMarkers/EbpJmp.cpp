#include "EbpJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEbp.h"
#include "Strings/PointerTrace/Assembly/RegisterRbp.h"

using namespace cocos2d;

const std::string EbpJmp::MapKeyEbpJmp = "ebp-jmp";

EbpJmp* EbpJmp::create(ValueMap& initProperties)
{
	EbpJmp* instance = new EbpJmp(initProperties);

	instance->autorelease();

	return instance;
}

EbpJmp::EbpJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbp::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EbpJmp::~EbpJmp()
{
}

void EbpJmp::onEnter()
{
	super::onEnter();
}

void EbpJmp::initializePositions()
{
	super::initializePositions();
}

int EbpJmp::getJumpDestination()
{
	return RegisterState::getRegisterEbp();
}
