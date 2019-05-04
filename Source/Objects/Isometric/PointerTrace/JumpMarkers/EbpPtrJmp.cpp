#include "EbpPtrJmp.h"

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

const std::string EbpPtrJmp::MapKeyEbpPtrJmp = "ebp-ptr-jmp";

EbpPtrJmp* EbpPtrJmp::create(ValueMap& initProperties)
{
	EbpPtrJmp* instance = new EbpPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EbpPtrJmp::EbpPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbp::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EbpPtrJmp::~EbpPtrJmp()
{
}

void EbpPtrJmp::onEnter()
{
	super::onEnter();
}

void EbpPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EbpPtrJmp::getJumpDestination()
{
	return RegisterState::getRegisterEbp();
}
