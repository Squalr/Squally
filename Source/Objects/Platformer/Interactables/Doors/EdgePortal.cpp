#include "EdgePortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string EdgePortal::MapKeyEdgePortal = "edge-portal";
const int EdgePortal::ArrowCount = 5;

EdgePortal* EdgePortal::create(ValueMap& properties)
{
	EdgePortal* instance = new EdgePortal(properties);

	instance->autorelease();

	return instance;
}

EdgePortal::EdgePortal(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	Size arrowHintSize = Size(properties.at(GameObject::MapKeyWidth).asFloat() + 256.0f, properties.at(GameObject::MapKeyHeight).asFloat() + 128.0f);
	this->edgeArrows = std::vector<Sprite*>();
	this->requiresInteraction = false;
	this->arrowHintCollision = CollisionObject::create(PhysicsBody::createBox(arrowHintSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);

	for (int index = 0; index < EdgePortal::ArrowCount; index++)
	{
		this->edgeArrows.push_back(Sprite::create(ObjectResources::Doors_EdgePortal_EdgeArrow));
	}

	for (auto arrow : this->edgeArrows)
	{
		if (GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool())
		{
			arrow->setFlippedX(true);
		}

		this->addChild(arrow);
	}

	this->addChild(this->arrowHintCollision);
}

EdgePortal::~EdgePortal()
{
}

void EdgePortal::onEnter()
{
	super::onEnter();

	for (auto arrow : this->edgeArrows)
	{
		arrow->setOpacity(0);
	}
}

void EdgePortal::initializePositions()
{
	super::initializePositions();
	
	const float spacing = 72.0f;
	int centerIndex = EdgePortal::ArrowCount / 2;
	int index = 0;

	for (auto arrow : this->edgeArrows)
	{
		int distance = (centerIndex - index++);

		arrow->setPosition(Vec2(0.0f, float(distance) * spacing));
	}
}

void EdgePortal::initializeListeners()
{
	super::initializeListeners();

	for (auto arrow : this->edgeArrows)
	{
		arrow->runAction(RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(0.75f, Vec2(arrow->isFlippedX() ? -16.0f : 16.0f, arrow->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(0.75f, Vec2(0.0f, arrow->getPositionY()))),
			nullptr
		)));
	}

	this->arrowHintCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		for (auto arrow : this->edgeArrows)
		{
			arrow->runAction(FadeTo::create(0.25f, 255));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->arrowHintCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		for (auto arrow : this->edgeArrows)
		{
			arrow->runAction(FadeTo::create(0.25f, 0));
		}
		return CollisionObject::CollisionResult::DoNothing;
	});
}
