#include "DartLauncher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Projectiles/Dart/Dart.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartLauncherGenericPreview.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartLauncherUpdateTimerPreview.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartNopClippy.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SHOOT 1

const std::string DartLauncher::MapKeyDartLauncher = "dart-launcher";

DartLauncher* DartLauncher::create(ValueMap& properties)
{
	DartLauncher* instance = new DartLauncher(properties);

	instance->autorelease();

	return instance;
}

DartLauncher::DartLauncher(ValueMap& properties) : super(properties, ObjectResources::Traps_DartLauncher_Animations)
{
	this->dartNopClippy = DartNopClippy::create();
	
	this->registerClippy(this->dartNopClippy);
}

DartLauncher::~DartLauncher()
{
}

void DartLauncher::initializePositions()
{
	super::initializePositions();
}

HackablePreview* DartLauncher::createDefaultPreview()
{
	return DartLauncherGenericPreview::create();
}

Clippy* DartLauncher::getTimerClippy()
{
	return this->dartNopClippy;
}

HackablePreview* DartLauncher::getTimerPreview()
{
	return DartLauncherUpdateTimerPreview::create();
}

Projectile* DartLauncher::createProjectile()
{
	return Dart::create(this->currentAngle, this->launchSpeed);
}
