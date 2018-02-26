#include "Parser.h"

Layer* Parser::initializeBackground(cocos_experimental::TMXTiledMap* map)
{
	Layer* layer = Layer::create();

	layer->addChild(JungleBackground::create());

	return layer;
}

Layer* Parser::initializeEnvironment(cocos_experimental::TMXTiledMap* map)
{
	Layer* layer = Layer::create();

	JungleEnvironment* environment = JungleEnvironment::create();

	layer->addChild(environment);

	return layer;
}

Layer* Parser::initializeObjects(cocos_experimental::TMXTiledMap* map, std::function<void(HackableObject*)> registerHackableCallback)
{
	Layer* layer = Layer::create();
	ValueVector objects = map->getObjectGroup("objects")->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		string type = object.at("type").asString();

		HackableObject* newObject = nullptr;

		if (type == "warp-gate")
		{
			newObject = WarpGate::create();
		}
		else if (type == "warp-gate-exact-scan-1")
		{
			newObject = WarpGateExactScanTutorial::create();
		}
		else if (type == "monitor")
		{
			string dialog = object.at("dialog").asString();

			newObject = Monitor::create("Dialog\\" + dialog + ".json");
		}
		else
		{
			throw std::invalid_argument("Invalid object");
		}

		registerHackableCallback(newObject);

		newObject->setPosition(Vec2(object.at("x").asFloat() + object.at("width").asFloat() / 2, object.at("y").asFloat() + object.at("height").asFloat() / 2));
		layer->addChild(newObject);
	}

	return layer;
}

Layer* Parser::initializeEntities(cocos_experimental::TMXTiledMap* map, std::function<void(HackableObject*)> registerHackableCallback)
{
	Layer* layer = Layer::create();
	ValueVector entities = map->getObjectGroup("entities")->getObjects();

	// Create entities
	for (int index = 0; index < size(entities); index++)
	{
		if (entities[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap entity = entities[index].asValueMap();
		string type = entity.at("type").asString();

		HackableObject* newEntity = nullptr;

		if (type == "spawn")
		{
			newEntity = Player::create();
		}
		else if (type == "bat")
		{
			newEntity = Bat::create();
		}
		else if (type == "shroom")
		{
			newEntity = Shroom::create();
		}
		else if (type == "snail")
		{
			newEntity = Snail::create();
		}
		else if (type == "poly")
		{
			newEntity = Poly::create();
		}
		else if (type == "knight")
		{
			newEntity = Knight::create();
		}
		else if (type == "skeleton")
		{
			newEntity = Skeleton::create();
		}
		else
		{
			const std::string error = "Invalid entity: " + type;

			throw std::invalid_argument(error);
		}

		registerHackableCallback(newEntity);

		newEntity->setPosition(Vec2(entity.at("x").asFloat() + entity.at("width").asFloat() / 2, entity.at("y").asFloat() + entity.at("height").asFloat() / 2));
		layer->addChild(newEntity);
	}

	return layer;
}

Layer* Parser::initializeCollision(cocos_experimental::TMXTiledMap* map)
{
	ValueVector collisionObjects = map->getObjectGroup("collision")->getObjects();
	Layer* layer = Layer::create();

	for (int index = 0; index < size(collisionObjects); index++)
	{
		if (collisionObjects[index].getType() != cocos2d::Value::Type::MAP)
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

		if (GameUtils::keyExists(object, "points"))
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
			throw std::invalid_argument("Invalid type");
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

Layer* Parser::initializeTileLayer(cocos_experimental::TMXTiledMap* map, std::string tileLayer)
{
	Layer* layer = Layer::create();
	cocos_experimental::TMXLayer* tileMap = map->getLayer(tileLayer);

	// Can be a nullptr if the layer is empty
	if (tileMap != nullptr)
	{
		map->removeChild(tileMap);
		layer->addChild(tileMap);
	}

	return layer;
}

Layer* Parser::initializeParallaxObjects(cocos_experimental::TMXTiledMap* map, std::string parallaxLayer)
{
	Layer* layer = Layer::create();
	ValueVector objects = map->getObjectGroup(parallaxLayer)->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();

		if (!GameUtils::keyExists(object, "speed-x") && !GameUtils::keyExists(object, "speed-y"))
		{
			throw std::invalid_argument("Parallax objects must have speed properties");
		}

		float speedX = object.at("speed-x").asFloat();
		float speedY = object.at("speed-y").asFloat();

		Sprite* sprite = Parser::loadObject(object);
		Vec2 position = sprite->getPosition();
		Node *node = Node::create();

		sprite->setPosition(Vec2::ZERO);
		node->addChild(sprite);

		ParallaxObject* parallaxObject = ParallaxObject::create(node, position, Vec2(speedX, speedY));

		layer->addChild(parallaxObject);
	}

	return layer;
}

Layer* Parser::initializeDecor(cocos_experimental::TMXTiledMap* map, std::string decorLayer)
{
	Layer* layer = Layer::create();
	ValueVector objects = map->getObjectGroup(decorLayer)->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		Sprite* sprite = Parser::loadObject(object);

		layer->addChild(sprite);
	}

	return layer;
}

Sprite* Parser::loadObject(ValueMap object)
{
	string type = object.at("type").asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* newObject = Sprite::create("Ingame/Decor/" + type + ".png");

	if (newObject == nullptr)
	{
		throw std::invalid_argument("Non-existant decor");
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

	if (GameUtils::keyExists(object, "rotation"))
	{
		float rotation = object.at("rotation").asFloat();
		newObject->setRotation(rotation);
	}

	if (GameUtils::keyExists(object, "flip-x"))
	{
		bool flipX = object.at("flip-x").asBool();
		newObject->setFlippedX(flipX);
	}

	if (GameUtils::keyExists(object, "flip-y"))
	{
		bool flipY = object.at("flip-y").asBool();
		newObject->setFlippedY(flipY);
	}

	if (GameUtils::keyExists(object, "float-x"))
	{
		float floatX = object.at("float-x").asFloat();
		float timeX = 1.0f;

		if (GameUtils::keyExists(object, "float-time-x"))
		{
			timeX = object.at("float-time-x").asFloat();
		}

		FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(floatX, 0.0f)));
		FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(-floatX, 0.0f)));

		newObject->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	}

	if (GameUtils::keyExists(object, "float-y"))
	{
		float floatY = object.at("float-y").asFloat();
		float timeY = 1.0f;

		if (GameUtils::keyExists(object, "float-time-y"))
		{
			timeY = object.at("float-time-y").asFloat();
		}

		FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, floatY)));
		FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, -floatY)));
		newObject->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
	}

	return newObject;
}