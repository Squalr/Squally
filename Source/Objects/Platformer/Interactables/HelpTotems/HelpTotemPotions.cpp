#include "HelpTotemPotions.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemPotions::MapKey = "help-totem-potions";

HelpTotemPotions* HelpTotemPotions::create(ValueMap& properties)
{
	HelpTotemPotions* instance = new HelpTotemPotions(properties);

	instance->autorelease();

	return instance;
}

HelpTotemPotions::HelpTotemPotions(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemPotions::create();
	
	this->setHint(hintString);
}

HelpTotemPotions::~HelpTotemPotions()
{
}
