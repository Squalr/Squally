#include "EbxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEbx.h"
#include "Strings/PointerTrace/Assembly/RegisterRbx.h"

using namespace cocos2d;

const std::string EbxPtrJmp::MapKeyEbxPtrJmp = "ebx-ptr-jmp";

EbxPtrJmp* EbxPtrJmp::create(ValueMap& initProperties)
{
	EbxPtrJmp* instance = new EbxPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EbxPtrJmp::EbxPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbx::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EbxPtrJmp::~EbxPtrJmp()
{
}

void EbxPtrJmp::onEnter()
{
	super::onEnter();
}

void EbxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EbxPtrJmp::getJumpDestination()
{
	return RegisterState::getRegisterEbx();
}
