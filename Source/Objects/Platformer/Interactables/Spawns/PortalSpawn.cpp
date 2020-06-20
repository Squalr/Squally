#include "PortalSpawn.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/UI/MapTitleBanner.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Deserializers/Platformer/PlatformerBannerDeserializer.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PortalSpawn::MapKey = "spawn";
const std::string PortalSpawn::PropertyPortalSpawnTransition = "transition";
const std::string PortalSpawn::PropertyMapBanner = "map-banner";
const std::string PortalSpawn::PropertyZoom = "zoom";

PortalSpawn* PortalSpawn::create(ValueMap& properties)
{
	PortalSpawn* instance = new PortalSpawn(properties);

	instance->autorelease();

	return instance;
}

PortalSpawn::PortalSpawn(ValueMap& properties) : super(properties)
{
	this->transition = GameUtils::getKeyOrDefault(this->properties, PortalSpawn::PropertyPortalSpawnTransition, Value("")).asString();
	this->bannerName = GameUtils::getKeyOrDefault(this->properties, PortalSpawn::PropertyMapBanner, Value("")).asString();
	this->flipX = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool();
	this->zoomOverride = GameUtils::getKeyOrDefault(this->properties, PortalSpawn::PropertyZoom, Value(0.0f)).asFloat();
}

PortalSpawn::~PortalSpawn()
{
}

void PortalSpawn::onEnter()
{
	super::onEnter();
}

void PortalSpawn::initializePositions()
{
	super::initializePositions();
}

void PortalSpawn::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventSpawnToTransitionLocation, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TransitionArgs* args = static_cast<PlatformerEvents::TransitionArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->transition == this->transition)
		{
			this->onPlayerSpawn();
		}
	}));
}

void PortalSpawn::onPlayerSpawn()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
	{
		this->doRelayer(squally);
		this->applyZoomOverride();

		PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(squally, GameUtils::getWorldCoords3D(this)));
		
		this->tryShowBanner();
		
		if (squally->getAnimations() != nullptr)
		{
			squally->getAnimations()->setFlippedX(this->flipX);
		}

	}), Squally::MapKey);
}

void PortalSpawn::doRelayer(Squally* squally)
{
	// Relayer to the spawn object layer
	MapLayer* layer = GameUtils::getFirstParentOfType<MapLayer>(this);

	if (layer != nullptr)
	{
		GameUtils::changeParent(squally, layer, true);
	}
}

void PortalSpawn::applyZoomOverride()
{
	if (this->zoomOverride == 0.0f)
	{
		return;
	}

	CameraTrackingData* data = GameCamera::getInstance()->getCurrentTrackingData();

	if (data != nullptr)
	{
		data->zoom = this->zoomOverride;
	}
}

void PortalSpawn::tryShowBanner()
{
	if (this->bannerName.empty())
	{
		return;
	}

	PlatformerBannerDeserializer* deserializer = PlatformerBannerDeserializer::create();

	ValueMap properties = ValueMap();

	properties[BannerDeserializer::MapKey] = this->bannerName;

	MapTitleBanner* banner = deserializer->deserializeProperties(properties);

	if (banner != nullptr)
	{
		this->addChild(banner);
	}
}
