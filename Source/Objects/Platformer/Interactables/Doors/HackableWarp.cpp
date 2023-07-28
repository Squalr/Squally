#include "HackableWarp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableHackNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HackableWarp::MapKey = "hackable-warp";

HackableWarp* HackableWarp::create(ValueMap& properties)
{
	HackableWarp* instance = new HackableWarp(properties);

	instance->autorelease();

	return instance;
}

HackableWarp::HackableWarp(ValueMap& properties) : super(
	properties,
	CSize(166.0f, 166.0f),
	Vec2::ZERO,
	Color3B(16, 23, 57))
{
	this->warpHitbox = ClickableHackNode::create(ObjectResources::Interactive_Help_TotemGlow, ObjectResources::Interactive_Help_TotemGlow);

	this->setInteractType(InteractType::None);

	this->addChild(this->warpHitbox);
}

HackableWarp::~HackableWarp()
{
}

void HackableWarp::onEnter()
{
	super::onEnter();
}

void HackableWarp::initializePositions()
{
	super::initializePositions();
}

void HackableWarp::initializeListeners()
{
	super::initializeListeners();

	this->warpHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->doRelayer();
		PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(squally, GameUtils::getWorldCoords3D(this), false));
	});
}

void HackableWarp::loadMap()
{
}

void HackableWarp::doRelayer()
{
	MapLayer* mapLayer = GameUtils::GetFirstParentOfType<MapLayer>(this);

	if (mapLayer != nullptr)
	{
		GameUtils::changeParent(squally, mapLayer, true);
		mapLayer->setHackable();
	}
}
