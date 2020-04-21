#include "PendulumBladeClippyAngleBehavior.h"

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBlade.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PendulumBladeClippyAngleBehavior::MapKey = "pendulum-blade-clippy-angle";

PendulumBladeClippyAngleBehavior* PendulumBladeClippyAngleBehavior::create(GameObject* owner)
{
	PendulumBladeClippyAngleBehavior* instance = new PendulumBladeClippyAngleBehavior(owner);

	instance->autorelease();

	return instance;
}

PendulumBladeClippyAngleBehavior::PendulumBladeClippyAngleBehavior(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

PendulumBladeClippyAngleBehavior::~PendulumBladeClippyAngleBehavior()
{
}

void PendulumBladeClippyAngleBehavior::onLoad()
{
	this->object->registerClippyOnto(PendulumBlade::HackIdentifierTargetAngle, [=]
	{
		LocalizedString* localizedString = Strings::Menus_Hacking_ClippyHelp_Objects_PendulumBlade_PendulumBladeMov::create();

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

void PendulumBladeClippyAngleBehavior::onDisable()
{
	super::onDisable();
}
