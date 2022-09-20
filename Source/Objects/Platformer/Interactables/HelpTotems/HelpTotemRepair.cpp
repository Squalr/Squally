#include "HelpTotemRepair.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemRepair::MapKey = "help-totem-repair";

HelpTotemRepair* HelpTotemRepair::create(ValueMap& properties)
{
	HelpTotemRepair* instance = new HelpTotemRepair(properties);

	instance->autorelease();

	return instance;
}

HelpTotemRepair::HelpTotemRepair(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemGecky::create();
	LocalizedString* helperNameString = Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* shiftString = Strings::Input_Shift::create();

	bracketString1->setStringReplacementVariables(shiftString);
	hintString->setStringReplacementVariables({ helperNameString, bracketString1 });
	
	this->setHint(hintString);
}

HelpTotemRepair::~HelpTotemRepair()
{
}

void HelpTotemRepair::onEnter()
{
	super::onEnter();

	if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGeckyFound, Value(false)).asBool())
	{
		this->deactivate(true);
	}
}
