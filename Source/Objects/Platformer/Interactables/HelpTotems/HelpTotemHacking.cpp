#include "HelpTotemHacking.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemHacking::MapKey = "help-totem-hacking";

HelpTotemHacking* HelpTotemHacking::create(ValueMap& properties)
{
	HelpTotemHacking* instance = new HelpTotemHacking(properties);

	instance->autorelease();

	return instance;
}

HelpTotemHacking::HelpTotemHacking(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemHacking::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* tabString = Strings::Input_Tab::create();

	bracketString1->setStringReplacementVariables(tabString);
	hintString->setStringReplacementVariables(bracketString1);
	
	this->setHint(hintString);
}

HelpTotemHacking::~HelpTotemHacking()
{
}
