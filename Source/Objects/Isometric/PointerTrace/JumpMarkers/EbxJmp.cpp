#include "EbxJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EbxJmp::MapKey = "ebx-jmp";

EbxJmp* EbxJmp::create(ValueMap& properties)
{
	EbxJmp* instance = new EbxJmp(properties);

	instance->autorelease();

	return instance;
}

EbxJmp::EbxJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbx::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EbxJmp::~EbxJmp()
{
}

void EbxJmp::onEnter()
{
	super::onEnter();
}

void EbxJmp::initializePositions()
{
	super::initializePositions();
}

int EbxJmp::getJumpDestination()
{
	return RegisterState::getRegisterEbx();
}
