#include "EdgePortal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EdgePortal::MapKeyEdgePortal = "edge-portal";
const std::string EdgePortal::MapKeyEdgePortalArgs = "args";
const std::string EdgePortal::MapKeyEdgePortalDirection = "direction";
const std::string EdgePortal::MapKeyEdgePortalMap = "map";

EdgePortal* EdgePortal::create(ValueMap& initProperties)
{
	EdgePortal* instance = new EdgePortal(initProperties);

	instance->autorelease();

	return instance;
}

EdgePortal::EdgePortal(ValueMap& initProperties) : super(initProperties)
{
	Size portalSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	
	this->edgePortalCollision = CollisionObject::create(PhysicsBody::createBox(portalSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->edgePortalHintCollision = CollisionObject::create(PhysicsBody::createBox(portalSize + Size(512.0f, 512.0f)), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->wasTripped = false;
	this->mapArgs = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, EdgePortal::MapKeyEdgePortalArgs, Value("")).asString(), ", ");
	this->mapFile = GameUtils::getKeyOrDefault(this->properties, EdgePortal::MapKeyEdgePortalMap, Value("")).asString();
	this->isLocked = !this->mapEvent.empty();

	std::string direction = GameUtils::getKeyOrDefault(this->properties, EdgePortal::MapKeyEdgePortalDirection, Value("")).asString();

	// parse & set direction helper arrows

	this->addChild(this->edgePortalCollision);
	this->addChild(this->edgePortalHintCollision);
}

EdgePortal::~EdgePortal()
{
}

void EdgePortal::onEnter()
{
	super::onEnter();
}

void EdgePortal::initializePositions()
{
	super::initializePositions();
}

void EdgePortal::initializeListeners()
{
	super::initializeListeners();

	if (!this->mapEvent.empty())
	{
		this->listenForMapEvent(this->mapEvent, [=](ValueMap args)
		{
			this->isLocked = false;
		});
	}

	this->edgePortalCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		if (!this->wasTripped && !this->isLocked)
		{
			this->wasTripped = true;

			// Load new map after a short delay -- changing scenes in the middle of a collision causes a crash
			// (not sure why, changing to a combat map is fine)
			this->runAction(Sequence::create(
				DelayTime::create(0.1f),
				CallFunc::create([=]()
				{
					NavigationEvents::navigatePlatformerMap(NavigationEvents::NavigateMapArgs("Platformer/Maps/" + this->mapFile + ".tmx", this->mapArgs, false));
				}),
				nullptr
			));
			
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->edgePortalHintCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
