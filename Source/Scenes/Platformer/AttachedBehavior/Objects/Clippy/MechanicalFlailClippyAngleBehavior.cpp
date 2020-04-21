#include "MechanicalFlailClippyAngleBehavior.h"

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlail.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MechanicalFlailClippyAngleBehavior::MapKey = "mechanical-flail-clippy-angle";

MechanicalFlailClippyAngleBehavior* MechanicalFlailClippyAngleBehavior::create(GameObject* owner)
{
	MechanicalFlailClippyAngleBehavior* instance = new MechanicalFlailClippyAngleBehavior(owner);

	instance->autorelease();

	return instance;
}

MechanicalFlailClippyAngleBehavior::MechanicalFlailClippyAngleBehavior(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

MechanicalFlailClippyAngleBehavior::~MechanicalFlailClippyAngleBehavior()
{
}

void MechanicalFlailClippyAngleBehavior::onLoad()
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

void MechanicalFlailClippyAngleBehavior::onDisable()
{
	super::onDisable();
}
