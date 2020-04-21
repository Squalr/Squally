#include "IsSwimmingClippyBehavior.h"

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Abilities/IsSwimming/SquallySwimHackBehavior.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IsSwimmingClippyBehavior::MapKey = "is-swimming-clippy";

IsSwimmingClippyBehavior* IsSwimmingClippyBehavior::create(GameObject* owner)
{
	IsSwimmingClippyBehavior* instance = new IsSwimmingClippyBehavior(owner);

	instance->autorelease();

	return instance;
}

IsSwimmingClippyBehavior::IsSwimmingClippyBehavior(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

IsSwimmingClippyBehavior::~IsSwimmingClippyBehavior()
{
}

void IsSwimmingClippyBehavior::onLoad()
{
	this->object->registerClippyOnto(SquallySwimHackBehavior::HackIdentifierIsSwimming, [=]
	{
		return ScrappyClippy::create(Strings::Menus_Hacking_ClippyHelp_Abilities_IsSwimming_IsSwimmingRetVal::create());
	});
}

void IsSwimmingClippyBehavior::onDisable()
{
	super::onDisable();
}
