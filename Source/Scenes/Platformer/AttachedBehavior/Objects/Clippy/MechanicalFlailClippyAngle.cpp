#include "MechanicalFlailClippyAngle.h"

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlail.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MechanicalFlailClippyAngle::MapKey = "mechanical-flail-clippy-angle";

MechanicalFlailClippyAngle* MechanicalFlailClippyAngle::create(GameObject* owner)
{
	MechanicalFlailClippyAngle* instance = new MechanicalFlailClippyAngle(owner);

	instance->autorelease();

	return instance;
}

MechanicalFlailClippyAngle::MechanicalFlailClippyAngle(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

MechanicalFlailClippyAngle::~MechanicalFlailClippyAngle()
{
}

void MechanicalFlailClippyAngle::onLoad()
{
	this->object->registerClippyOnto(MechanicalFlail::HackIdentifierTargetAngle, [=]
	{
		LocalizedString* localizedString = Strings::Menus_Hacking_ClippyHelp_Objects_MechanicalFlail_MechanicalFlailMov::create();

		if (sizeof(void*) == 8)
		{
			localizedString->setStringReplacementVariables(Strings::Menus_Hacking_RegisterRax::create());
		}
		else
		{
			localizedString->setStringReplacementVariables(Strings::Menus_Hacking_RegisterEax::create());
		}

		return ScrappyClippy::create(localizedString);
	});
}

void MechanicalFlailClippyAngle::onDisable()
{
	super::onDisable();
}
