#include "DartTripodLauncher.h"

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

const std::string DartTripodLauncher::MapKeyDartTripodLauncher = "dart-tripod-launcher";

DartTripodLauncher* DartTripodLauncher::create(ValueMap& properties)
{
	DartTripodLauncher* instance = new DartTripodLauncher(properties);

	instance->autorelease();

	return instance;
}

DartTripodLauncher::DartTripodLauncher(ValueMap& properties) : super(properties, ObjectResources::Traps_DartTripodLauncher_Animations)
{
}

DartTripodLauncher::~DartTripodLauncher()
{
}

void DartTripodLauncher::initializePositions()
{
	super::initializePositions();
}
