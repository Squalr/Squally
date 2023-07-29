#include "HackableWarp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableHackNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Mounts/MountBase.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMountBehavior.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HackableWarp::MapKey = "hackable-warp";
const std::string HackableWarp::PropertyShowHelpArrow = "show-help-arrow";

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
	this->showHelpArrow = GameUtils::getKeyOrDefault(this->properties, HackableWarp::PropertyShowHelpArrow, Value(false)).asBool();
	this->warpSfx = Sound::create(SoundResources::Platformer_FX_Woosh_WooshFire2);

	// No need to create if disabled
	if (this->showHelpArrow)
	{
 		this->helpArrow = HelpArrow::create();
 		this->helpArrow->setPositionY(192.0f);
		this->helpArrow->showPointer();
		this->helpArrow->setVisible(false);
	}

	this->setInteractType(InteractType::None);
	this->warpHitbox->disableInteraction();

	this->addChild(this->warpHitbox);
	this->addChild(this->warpSfx);

	if (this->showHelpArrow)
	{
		this->addChild(this->helpArrow);
	}
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
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->warpHitbox->disableInteraction();

		if (this->showHelpArrow)
		{
			this->helpArrow->setVisible(false);
		}
	}));
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->warpHitbox->enableInteraction();

		if (this->showHelpArrow)
		{
			this->helpArrow->setVisible(true);
		}
	}));

	this->warpHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->warpSfx->play();
		this->doRelayer();
		PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(this->squally, GameUtils::getWorldCoords3D(this), false));
	});
}

void HackableWarp::loadMap()
{
}

bool HackableWarp::forceHackParticles()
{
	return true;
}

void HackableWarp::doRelayer()
{
	this->squally->getComponent<EntityMountBehavior>([=](EntityMountBehavior* mountBehavior)
	{
		MountBase* mount = mountBehavior->getMountTarget();
		
		if (mount)
		{
			mount->dismountAll();
		}
	});
	
	MapLayer* mapLayer = GameUtils::GetFirstParentOfType<MapLayer>(this);

	if (mapLayer != nullptr)
	{
		GameUtils::changeParent(this->squally, mapLayer, true);
		mapLayer->setHackable();
	}

	HackableEvents::TriggerHackerModeDisable();
}
