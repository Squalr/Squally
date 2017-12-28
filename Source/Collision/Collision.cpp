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

		CollisionObject* collisionBox = new CollisionObject();
		CollisionGroup collisionGroup;

		if (type == "solid")
		{
			collisionGroup = CollisionGroup::G_Solid;
		}
		else if (type == "water")
		{
			collisionGroup = CollisionGroup::G_Water;
		}
		else if (type == "npc")
		{
			collisionGroup = CollisionGroup::G_SolidNpc;
		}
		else
		{
			throw new exception("Invalid type");
		}

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

			collisionBox->init(PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup);
		}
		else
		{
			collisionBox->init(PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup);
			collisionBox->setPosition(x, y);
		}

		layer->addChild(collisionBox);
	}

	return layer;
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
