#include "HelpTotemEndOfDemo.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Input/Shift.h"
#include "Strings/Input/Tab.h"
#include "Strings/Platformer/Help/HelpTotemEndOfDemo.h"

using namespace cocos2d;

const std::string HelpTotemEndOfDemo::MapKeyHelpTotemEndOfDemo = "help-totem-end-of-demo";

HelpTotemEndOfDemo* HelpTotemEndOfDemo::create(ValueMap& properties)
{
	HelpTotemEndOfDemo* instance = new HelpTotemEndOfDemo(properties);

	instance->autorelease();

	return instance;
}

HelpTotemEndOfDemo::HelpTotemEndOfDemo(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemEndOfDemo::create();
	
	this->setHint(hintString);
}

HelpTotemEndOfDemo::~HelpTotemEndOfDemo()
{
}

void HelpTotemEndOfDemo::onEnter()
{
	super::onEnter();
}

void HelpTotemEndOfDemo::initializePositions()
{
	super::initializePositions();
}

void HelpTotemEndOfDemo::initializeListeners()
{
	super::initializeListeners();
}
