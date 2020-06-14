#include "HelpTotemEquipment.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemEquipment::MapKey = "help-totem-equipment";

HelpTotemEquipment* HelpTotemEquipment::create(ValueMap& properties)
{
	HelpTotemEquipment* instance = new HelpTotemEquipment(properties);

	instance->autorelease();

	return instance;
}

HelpTotemEquipment::HelpTotemEquipment(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemEquipment::create();
	
	this->setHint(hintString);
}

HelpTotemEquipment::~HelpTotemEquipment()
{
}
