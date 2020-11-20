#include "HelpTotemSwimHack.h"

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

const std::string HelpTotemSwimHack::MapKey = "help-totem-swim-hack";

HelpTotemSwimHack* HelpTotemSwimHack::create(ValueMap& properties)
{
	HelpTotemSwimHack* instance = new HelpTotemSwimHack(properties);

	instance->autorelease();

	return instance;
}

HelpTotemSwimHack::HelpTotemSwimHack(ValueMap& properties) : super(properties)
{
	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemSwimHack::create();
	LocalizedString* helperNameString = Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* shiftString = Strings::Input_Shift::create();

	bracketString1->setStringReplacementVariables(shiftString);
	hintString->setStringReplacementVariables({ helperNameString, bracketString1 });
	
	this->setHint(hintString);
}

HelpTotemSwimHack::~HelpTotemSwimHack()
{
}

void HelpTotemSwimHack::onEnter()
{
	super::onEnter();

	if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookWater, Value(false)).asBool())
	{
		this->deactivate(true);
	}
}
