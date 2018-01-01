#include "LevelParser.h"

Layer* LevelParser::initializeBackground(experimental::TMXTiledMap* map)
{
	Layer* layer = Layer::create();

	layer->addChild(JungleBackground::create());

	return layer;
}

Layer* LevelParser::initializeEnvironment(experimental::TMXTiledMap* map)
{
	Layer* layer = Layer::create();

	ParticleSystem* particles = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	layer->addChild(particles);

	return layer;
}

Layer* LevelParser::initializeBackgroundTiles(experimental::TMXTiledMap* map)
{
	return LevelParser::extractTileLayer(map, "background");
}

Layer* LevelParser::initializeMidgroundTiles(experimental::TMXTiledMap* map)
{
	return LevelParser::extractTileLayer(map, "midground");
}

Layer* LevelParser::initializeForegroundTiles(experimental::TMXTiledMap* map)
{
	return LevelParser::extractTileLayer(map, "foreground");
}

Layer* LevelParser::initializeObjects(experimental::TMXTiledMap* map)
{
	Layer* layer = Layer::create();
	ValueVector objects = map->getObjectGroup("objects")->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		string type = object.at("type").asString();

		Node* newObject = nullptr;

		if (type == "spawn")
		{
			newObject = Player::create();
		}
		else if (type == "bat")
		{
			newObject = Bat::create();
		}
		else if (type == "shroom")
		{
			newObject = Shroom::create();
		}
		else if (type == "snail")
		{
			newObject = Snail::create();
		}
		else if (type == "poly")
		{
			newObject = Poly::create();
		}
		else
		{
			throw exception("invalid object");
		}

		newObject->setPosition(Vec2(object.at("x").asFloat() + object.at("width").asFloat() / 2, object.at("y").asFloat() + object.at("height").asFloat() / 2));
		layer->addChild(newObject);
	}

	return layer;
}

Layer* LevelParser::initializeCollision(experimental::TMXTiledMap* map)
{
	ValueVector collisionObjects = map->getObjectGroup("collision")->getObjects();
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
		CategoryGroup collisionGroup = CategoryGroup::G_None;

		if (type == "solid")
		{
			collisionGroup = CategoryGroup::G_Solid;
		}
		else if (type == "water")
		{
			collisionGroup = CategoryGroup::G_Water;
		}
		else if (type == "npc")
		{
			collisionGroup = CategoryGroup::G_SolidNpc;
		}
		else if (type == "npc-flying")
		{
			collisionGroup = CategoryGroup::G_SolidFlyingNpc;
		}
		else
		{
			throw exception("Invalid type");
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

			collisionBox->init(PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup, false, false);
		}
		else
		{
			collisionBox->init(PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup, false, false);
			collisionBox->setPosition(x, y);
		}

		layer->addChild(collisionBox);
	}

	return layer;
}

Layer* LevelParser::extractTileLayer(experimental::TMXTiledMap* map, std::string tileLayer)
{
	Layer* layer = Layer::create();
	Layer* decorLayer = LevelParser::initializeDecor(map, "decor-" + tileLayer);
	experimental::TMXLayer* background = map->getLayer(tileLayer);

	map->removeChild(background);
	layer->addChild(background);
	layer->addChild(decorLayer);

	return layer;
}

Layer* LevelParser::initializeDecor(experimental::TMXTiledMap* map, std::string decorLayer)
{
	Layer* layer = Layer::create();
	ValueVector objects = map->getObjectGroup(decorLayer)->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		string type = object.at("type").asString();

		// For decor, simply grab the resource of the same name of the object type
		Sprite* newObject = Sprite::create("Ingame\\Decor\\" + type + ".png");

		if (newObject == nullptr)
		{
			throw exception("Non-existant decor");
		}

		float width = object.at("width").asFloat();
		float height = object.at("height").asFloat();
		float x = object.at("x").asFloat() + width / 2.0f;
		float y = object.at("y").asFloat() + height / 2.0f;

		// Scale decor based on rectangle size (only using height for simplicity)
		newObject->setScale(height / newObject->getContentSize().height);

		// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
		newObject->setAnchorPoint(Vec2(0.0f, 1.0f));
		newObject->setPosition(Vec2(x - width / 2.0f, y + height / 2.0f));

		if (Utils::keyExists(object, "rotation"))
		{
			float rotation = object.at("rotation").asFloat();
			newObject->setRotation(rotation);
		}

		if (Utils::keyExists(object, "flip-x"))
		{
			bool flipX = object.at("flip-x").asBool();
			newObject->setFlippedX(flipX);
		}

		if (Utils::keyExists(object, "flip-y"))
		{
			bool flipY = object.at("flip-y").asBool();
			newObject->setFlippedY(flipY);
		}

		layer->addChild(newObject);
	}

	return layer;
}
