#include "TerrainObject.h"

std::string TerrainObject::KeyTypeTerrain = "terrain";

const std::string TerrainObject::RequestTerrainMappingEvent = "request_terrain_mapping";

void TerrainObject::requestTerrainMapping(TerrainMapRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		TerrainObject::RequestTerrainMappingEvent,
		&args
	);
}

TerrainObject::TerrainObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CategoryName initCategoryName, bool isDynamic, bool canRotate) : HackableObject(initProperties)
{
	this->physicsBody = initPhysicsBody;
	this->categoryName = initCategoryName;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->setPhysicsBody(initPhysicsBody);
	}

	// Fire event, allowing for the game to map what this collision object collides with
	TerrainObject::requestTerrainMapping(TerrainObject::TerrainMapRequestArgs(this->categoryName, this));
}

TerrainObject::~TerrainObject()
{
}

void TerrainObject::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void TerrainObject::initializeListeners()
{
	HackableObject::initializeListeners();

	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(TerrainObject::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(TerrainObject::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(TerrainObject::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(TerrainObject::onContactEnd, this);

	this->addEventListener(contactListener);
}

void TerrainObject::setTerrainGroups(CategoryGroup categoryGroup, std::vector<CategoryGroup>* collidesWith)
{
	if (this->physicsBody != nullptr)
	{
		int collidesWithBitmask = 0;

		if (collidesWith != nullptr)
		{
			for (auto it = collidesWith->begin(); it != collidesWith->end(); it++)
			{
				collidesWithBitmask |= *it;
			}
		}

		this->physicsBody->setCategoryBitmask(categoryGroup);
		this->physicsBody->setTerrainBitmask(collidesWithBitmask);
		this->physicsBody->setContactTestBitmask(0xFFFFFFFF);
	}
}

void TerrainObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 pos = this->getPosition();
	const float STOP_PHYSICS_OFFSET = 1024.0f;

	if (this->physicsBody != nullptr && this->physicsBody->isDynamic())
	{
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

		if (pos.x > cameraPosition.x + visibleSize.width + STOP_PHYSICS_OFFSET ||
			pos.x < cameraPosition.x - STOP_PHYSICS_OFFSET ||
			pos.y > cameraPosition.y + visibleSize.height + STOP_PHYSICS_OFFSET ||
			pos.y < cameraPosition.y - STOP_PHYSICS_OFFSET)
		{
			// Bypass setter to force disable physics for this object
			this->physicsBody->setEnabled(false);
		}
		else
		{
			// Use setter such that if physics was disabled for a reason other than being off-screen, we do not overwrite that
			this->setPhysicsEnabled(this->physicsEnabled);
		}
	}
}

void TerrainObject::setPhysicsEnabled(bool enabled)
{
	this->physicsEnabled = enabled;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
}

Vec2 TerrainObject::getVelocity()
{
	return this->physicsBody == nullptr ? Vec2::ZERO : this->physicsBody->getVelocity();
}

void TerrainObject::setVelocity(Vec2 velocity)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setVelocity(velocity);
	}
}

CategoryName TerrainObject::getCategoryName()
{
	return this->categoryName;
}

CategoryGroup TerrainObject::getCategoryGroup()
{
	return this->physicsBody == nullptr ? 0 : this->physicsBody->getCategoryBitmask();
}

bool TerrainObject::contactBegin(TerrainData data)
{
	return true;
}

bool TerrainObject::contactUpdate(TerrainData data)
{
	return true;
}

bool TerrainObject::contactEnd(TerrainData data)
{
	return true;
}

bool TerrainObject::onContactBegin(PhysicsContact &contact)
{
	TerrainData data = this->constructTerrainData(contact);

	if (data.other == nullptr)
	{
		return true;
	}

	return this->contactBegin(data);
}

bool TerrainObject::onContactUpdate(PhysicsContact &contact)
{
	TerrainData data = this->constructTerrainData(contact);

	if (data.other == nullptr)
	{
		return true;
	}

	return this->contactUpdate(data);
}

bool TerrainObject::onContactEnd(PhysicsContact &contact)
{
	TerrainData data = this->constructTerrainData(contact);

	if (data.other == nullptr)
	{
		return true;
	}

	return this->contactEnd(data);
}

TerrainObject::TerrainData TerrainObject::constructTerrainData(PhysicsContact& contact)
{
	TerrainObject::TerrainData collisionData = TerrainObject::TerrainData(nullptr, Vec2::ZERO, TerrainObject::TerrainDirection::None, nullptr, 0);
	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() != this->physicsBody && contact.getShapeB()->getBody() != this->physicsBody)
	{
		return collisionData;
	}

	if (contact.getShapeA()->getBody() == this->physicsBody)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	if (other == nullptr)
	{
		return collisionData;
	}

	collisionData.other = (TerrainObject*)other->getBody()->getNode();
	collisionData.normal = contact.getContactData()->normal;
	collisionData.pointCount = contact.getContactData()->count;
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	// Convert collision coordinates to level coordinates
	for (int index = 0; index < collisionData.pointCount; index++)
	{
		collisionData.points[index] = Vec2(contact.getContactData()->points[index].x + cameraPosition.x, contact.getContactData()->points[index].y + cameraPosition.y);
	}

	// Determines how large the
	const float sensitivity = 16.0f;

	// Determine direction of collision
	if (collisionData.pointCount == 2)
	{
		// Horizontal collision
		if (collisionData.points[0].x == collisionData.points[1].x)
		{
			if (abs(collisionData.points[0].y - collisionData.points[1].y) > sensitivity)
			{
				if (this->getPositionX() < collisionData.other->getPositionX())
				{
					collisionData.direction = TerrainDirection::Right;
				}
				else
				{
					collisionData.direction = TerrainDirection::Left;
				}
			}
			else if (this->getPositionY() >= std::max(collisionData.points[0].y, collisionData.points[1].y))
			{
				if (this->getPositionX() < collisionData.other->getPositionX())
				{
					collisionData.direction = TerrainDirection::StepRight;
				}
				else
				{
					collisionData.direction = TerrainDirection::StepLeft;
				}
			}
		}
		// Vertical collision
		else if (collisionData.points[0].y == collisionData.points[1].y &&
			abs(collisionData.points[0].x - collisionData.points[1].x) > sensitivity)
		{
			if (this->getPositionY() < collisionData.other->getPositionY())
			{
				collisionData.direction = TerrainDirection::Up;
			}
			else
			{
				collisionData.direction = TerrainDirection::Down;
			}
		}
	}

	return collisionData;
}
