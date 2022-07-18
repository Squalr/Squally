#include "HelpTotemColdWater.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemColdWater::MapKey = "help-totem-cold-water";

HelpTotemColdWater* HelpTotemColdWater::create(ValueMap& properties)
{
	HelpTotemColdWater* instance = new HelpTotemColdWater(properties);

	instance->autorelease();

	return instance;
}

HelpTotemColdWater::HelpTotemColdWater(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemColdWater::create();
	
	this->setHint(hintString);
}

HelpTotemColdWater::~HelpTotemColdWater()
{
}
