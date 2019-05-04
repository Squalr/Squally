#include "EdxJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdx.h"
#include "Strings/PointerTrace/Assembly/RegisterRdx.h"

using namespace cocos2d;

const std::string EdxJmp::MapKeyEdxJmp = "edx-jmp";

EdxJmp* EdxJmp::create(ValueMap& initProperties)
{
	EdxJmp* instance = new EdxJmp(initProperties);

	instance->autorelease();

	return instance;
}

EdxJmp::EdxJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdx::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EdxJmp::~EdxJmp()
{
}

void EdxJmp::onEnter()
{
	super::onEnter();
}

void EdxJmp::initializePositions()
{
	super::initializePositions();
}

int EdxJmp::getJumpDestination()
{
	return RegisterState::getRegisterEdx();
}
