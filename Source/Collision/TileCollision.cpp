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
		bool isPolygon = false;
		float width = object.at("width").asFloat();
		float height = object.at("height").asFloat();
		float x = object.at("x").asFloat() + width / 2.0f;
		float y = object.at("y").asFloat() + height / 2.0f;

		if (Utils::KeyExists(object, "points"))
		{
			isPolygon = true;
			polygonPoints = &(object.at("points").asValueVector());
		}

		CollisionObject* collisionBox = nullptr;

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

			collisionBox = CollisionObject::create(points, polygonPoints->size());
		}
		else
		{
			collisionBox = CollisionObject::create(Size(width, height));
			collisionBox->setPosition(x, y);
		}

		if (type == "solid")
		{
			collisionBox->SetCollisionGroup(CollisionObject::CollisionGroup::Solid);
		}
		else if (type == "water")
		{
			collisionBox->SetCollisionGroup(CollisionObject::CollisionGroup::Water);
		}

		layer->addChild(collisionBox);
	}

	return layer;
}
