#include "TileCollision.h"

Layer* TileCollision::InitializeCollision(ValueVector collisionObjects)
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
		auto pointsIterator = object.find("points");
		bool isPolygon = false;
		float width = object.at("width").asFloat();
		float height = object.at("height").asFloat();
		float x = object.at("x").asFloat() + width / 2.0f;
		float y = object.at("y").asFloat() + height / 2.0f;

		if (pointsIterator != object.end())
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
			collisionBox->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Solid);
		}
		else if (type == "water")
		{
			collisionBox->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Water);
		}

		collisionBox->setDynamic(false);
		node->addComponent(collisionBox);
		layer->addChild(node);
	}

	return layer;
}
