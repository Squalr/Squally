#include "HelpTotemRequiredLevel.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemRequiredLevel::MapKeyHelpTotemRequiredLevel = "help-totem-required-level";

HelpTotemRequiredLevel* HelpTotemRequiredLevel::create(ValueMap& properties)
{
	HelpTotemRequiredLevel* instance = new HelpTotemRequiredLevel(properties);

	instance->autorelease();

	return instance;
}

HelpTotemRequiredLevel::HelpTotemRequiredLevel(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemRequiredLevel::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* bracketString2 = Strings::Common_Brackets::create();
	LocalizedString* shiftString = Strings::Input_Shift::create();
	LocalizedString* tabString = Strings::Input_Tab::create();

	bracketString1->setStringReplacementVariables(shiftString);
	bracketString2->setStringReplacementVariables(tabString);
	hintString->setStringReplacementVariables({ bracketString1, bracketString2 });
	
	this->setHint(hintString);
}

HelpTotemRequiredLevel::~HelpTotemRequiredLevel()
{
}

void HelpTotemRequiredLevel::onEnter()
{
	super::onEnter();
}

void HelpTotemRequiredLevel::initializePositions()
{
	super::initializePositions();
}

void HelpTotemRequiredLevel::initializeListeners()
{
	super::initializeListeners();
}
