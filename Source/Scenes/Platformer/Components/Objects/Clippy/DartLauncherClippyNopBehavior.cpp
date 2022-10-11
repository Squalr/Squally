#include "DartLauncherClippyNopBehavior.h"

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartLauncher.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DartLauncherClippyNopBehavior::MapKey = "dart-launcher-clippy-nop";

DartLauncherClippyNopBehavior* DartLauncherClippyNopBehavior::create(GameObject* owner)
{
	DartLauncherClippyNopBehavior* instance = new DartLauncherClippyNopBehavior(owner);

	instance->autorelease();

	return instance;
}

DartLauncherClippyNopBehavior::DartLauncherClippyNopBehavior(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

DartLauncherClippyNopBehavior::~DartLauncherClippyNopBehavior()
{
}

void DartLauncherClippyNopBehavior::onLoad()
{
	this->object->registerClippyOnto(DartLauncher::HackIdentifierLaunchTimer, [=]
	{
		return ScrappyClippy::create(Strings::Menus_Hacking_ClippyHelp_Objects_DartGun_DartNop::create(), "dart-launcher-nop");
	});
}

void DartLauncherClippyNopBehavior::onDisable()
{
	super::onDisable();
}
