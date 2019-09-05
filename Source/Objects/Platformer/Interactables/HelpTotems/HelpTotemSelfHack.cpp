#include "HelpTotemSelfHack.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Input/Shift.h"
#include "Strings/Input/Tab.h"
#include "Strings/Platformer/Help/HelpTotemSelfHack.h"

using namespace cocos2d;

const std::string HelpTotemSelfHack::MapKeyHelpTotemSelfHack = "help-totem-self-hack";

HelpTotemSelfHack* HelpTotemSelfHack::create(ValueMap& properties)
{
	HelpTotemSelfHack* instance = new HelpTotemSelfHack(properties);

	instance->autorelease();

	return instance;
}

HelpTotemSelfHack::HelpTotemSelfHack(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemSelfHack::create();
	
	this->setHint(hintString);
}

HelpTotemSelfHack::~HelpTotemSelfHack()
{
}

void HelpTotemSelfHack::onEnter()
{
	super::onEnter();
}

void HelpTotemSelfHack::initializePositions()
{
	super::initializePositions();
}

void HelpTotemSelfHack::initializeListeners()
{
	super::initializeListeners();
}
