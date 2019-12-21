#include "HelpTotemHexusCards.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemHexusCards::MapKeyHelpTotemHexusCards = "help-totem-hexus-cards";

HelpTotemHexusCards* HelpTotemHexusCards::create(ValueMap& properties)
{
	HelpTotemHexusCards* instance = new HelpTotemHexusCards(properties);

	instance->autorelease();

	return instance;
}

HelpTotemHexusCards::HelpTotemHexusCards(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemHexusCards::create()->setStringReplacementVariables({ Strings::Hexus_Hexus::create() });
	
	this->setHint(hintString);
}

HelpTotemHexusCards::~HelpTotemHexusCards()
{
}
