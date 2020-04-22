#include "HelpTotemPickPocket.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HelpTotemPickPocket::MapKey = "help-totem-pick-pocket";

HelpTotemPickPocket* HelpTotemPickPocket::create(ValueMap& properties)
{
	HelpTotemPickPocket* instance = new HelpTotemPickPocket(properties);

	instance->autorelease();

	return instance;
}

HelpTotemPickPocket::HelpTotemPickPocket(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemPickPocket::create();
	LocalizedString* helperNameString = Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* shiftString = Strings::Input_Shift::create();

	bracketString1->setStringReplacementVariables(shiftString);
	hintString->setStringReplacementVariables({ helperNameString, bracketString1 });
	
	this->setHint(hintString);
}

HelpTotemPickPocket::~HelpTotemPickPocket()
{
}

void HelpTotemPickPocket::onEnter()
{
	super::onEnter();

	if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString() != Guano::MapKey)
	{
		this->deactivate(true);
	}
}
