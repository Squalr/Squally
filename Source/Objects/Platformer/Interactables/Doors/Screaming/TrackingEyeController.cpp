#include "TrackingEyeController.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/SmartScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Screaming/TrackingEye.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TrackingEyeController::MapKey = "tracking-eye-controller";
const std::string TrackingEyeController::PropertyEyeGroup = "eye-group";

TrackingEyeController* TrackingEyeController::create(ValueMap& properties)
{
	TrackingEyeController* instance = new TrackingEyeController(properties);

	instance->autorelease();

	return instance;
}

TrackingEyeController::TrackingEyeController(ValueMap& properties) : super(properties)
{
	this->eyeGroup = GameUtils::getKeyOrDefault(properties, TrackingEyeController::PropertyEyeGroup, Value("")).asString();
}

TrackingEyeController::~TrackingEyeController()
{
}

void TrackingEyeController::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::QueryObjects<TrackingEye>([=](TrackingEye* next)
	{
		this->eyes.push_back(EyeData(next, GameUtils::getWorldCoords(next, false)));
	}, this->eyeGroup);

	this->scheduleUpdate();
}

void TrackingEyeController::update(float dt)
{
	super::update(dt);

	this->updateEyeTracking(dt);
}

void TrackingEyeController::updateEyeTracking(float dt)
{
	Vec2 squallyCoords = GameUtils::getWorldCoords(this->squally, false);
	
	TRY_PARALLELIZE(
		this->eyes.begin(),
		this->eyes.end(),
		[=](const EyeData& eyeData)
		{
			eyeData.eye->updateSingleEyeTracking(dt, eyeData.coords, squallyCoords);
		}
	);
}
