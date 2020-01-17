#include "FireLauncher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string FireLauncher::MapKeyFireLauncher = "fire-launcher";

FireLauncher* FireLauncher::create(ValueMap& properties)
{
	FireLauncher* instance = new FireLauncher(properties);

	instance->autorelease();

	return instance;
}

FireLauncher::FireLauncher(ValueMap& properties) : super(properties, ObjectResources::Traps_FireLauncher_Animations)
{
}

FireLauncher::~FireLauncher()
{
}

void FireLauncher::initializePositions()
{
	super::initializePositions();
}
