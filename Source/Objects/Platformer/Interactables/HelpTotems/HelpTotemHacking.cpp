#include "HelpTotemHacking.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Input/Tab.h"
#include "Strings/Platformer/Help/HelpTotemHacking.h"

using namespace cocos2d;

const std::string HelpTotemHacking::MapKeyHelpTotemHacking = "help-totem-hacking";

HelpTotemHacking* HelpTotemHacking::create(ValueMap& properties)
{
	HelpTotemHacking* instance = new HelpTotemHacking(properties);

	instance->autorelease();

	return instance;
}

HelpTotemHacking::HelpTotemHacking(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemHacking::create();
	LocalizedString* bracketString = Strings::Common_Brackets::create();
	LocalizedString* tabString = Strings::Input_Tab::create();

	bracketString->setStringReplacementVariables(tabString);
	hintString->setStringReplacementVariables(bracketString);
	
	this->setHint(hintString);
}

HelpTotemHacking::~HelpTotemHacking()
{
}

void HelpTotemHacking::onEnter()
{
	super::onEnter();
}

void HelpTotemHacking::initializePositions()
{
	super::initializePositions();
}

void HelpTotemHacking::initializeListeners()
{
	super::initializeListeners();
}
