#include "Collision.h"

Layer* Collision::initializeCollision(ValueVector collisionObjects)
{
	Layer* layer = Layer::create();

	for (int index = 0; index < size(collisionObjects); index++)
	{
		if (collisionObjects[index].getType() != Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = collisionObjects[index].asValueMap();
		ValueVector* polygonPoints = nullptr;

		std::string type = object.at("type").asString();
		bool isPolygon = false;
		float width = object.at("width").asFloat();
		float height = object.at("height").asFloat();
		float x = object.at("x").asFloat() + width / 2.0f;
		float y = object.at("y").asFloat() + height / 2.0f;

		if (Utils::keyExists(object, "points"))
		{
			isPolygon = true;
			polygonPoints = &(object.at("points").asValueVector());
		}

		Node* node = Node::create();
		PhysicsBody* collisionBox = nullptr;

		if (isPolygon)
		{
			Vec2* points = new Vec2[polygonPoints->size()];
			int index = 0;

			for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
			{
				auto point = it->asValueMap();

				float deltaX = point.at("x").asFloat();
				float deltaY = point.at("y").asFloat();

				points[index++] = Vec2(x + deltaX, y - deltaY);
			}

			collisionBox = PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		}
		else
		{
			collisionBox = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f));
			node->setPosition(x, y);
		}

		if (type == "solid")
		{
			collisionBox->setContactTestBitmask(Collision::CollisionGroup::Solid);
		}
		else if (type == "water")
		{
			collisionBox->setContactTestBitmask(Collision::CollisionGroup::Water);
		}
		else if (type == "npc")
		{
			collisionBox->setContactTestBitmask(Collision::CollisionGroup::SolidNpc);
		}
		else
		{
			throw new exception("Invalid type");
		}

		collisionBox->setDynamic(false);
		node->addComponent(collisionBox);
		layer->addChild(node);
	}

	return layer;
}

PhysicsShape* Collision::getCollidingObject(PhysicsBody* self, PhysicsContact& contact)
{
	if (contact.getShapeA()->getBody() != self && contact.getShapeB()->getBody() != self)
	{
		return false;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() == self)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return other;
}

bool Collision::isContactBelow(Node* node, PhysicsContact& contact)
{
	for (int index = 0; index < contact.getContactData()->count; index++)
	{
		if (contact.getContactData()->points[index].y < node->getPositionY())
		{
			return true;
		}
	}

	return false;
}
