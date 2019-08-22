#include "HelpTotemAttacking.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Input/Spacebar.h"
#include "Strings/Platformer/Help/HelpTotemAttacking.h"

using namespace cocos2d;

const std::string HelpTotemAttacking::MapKeyHelpTotemAttacking = "help-totem-attacking";

HelpTotemAttacking* HelpTotemAttacking::create(ValueMap& properties)
{
	HelpTotemAttacking* instance = new HelpTotemAttacking(properties);

	instance->autorelease();

	return instance;
}

HelpTotemAttacking::HelpTotemAttacking(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemAttacking::create();
	LocalizedString* bracketString = Strings::Common_Brackets::create();
	LocalizedString* spaceString = Strings::Input_Spacebar::create();

	bracketString->setStringReplacementVariables(spaceString);
	hintString->setStringReplacementVariables(bracketString);
	
	this->setHint(hintString);
}

HelpTotemAttacking::~HelpTotemAttacking()
{
}

void HelpTotemAttacking::onEnter()
{
	super::onEnter();
}

void HelpTotemAttacking::initializePositions()
{
	super::initializePositions();
}

void HelpTotemAttacking::initializeListeners()
{
	super::initializeListeners();
}
