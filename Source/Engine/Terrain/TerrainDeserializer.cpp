#include "TerrainDeserializer.h"

TerrainDeserializer* TerrainDeserializer::instance = nullptr;

void TerrainDeserializer::registerGlobalNode()
{
	if (TerrainDeserializer::instance == nullptr)
	{
		TerrainDeserializer::instance = new TerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(TerrainDeserializer::instance);
	}
}

TerrainDeserializer::TerrainDeserializer()
{
}

TerrainDeserializer::~TerrainDeserializer()
{
}

void TerrainDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void TerrainDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == TerrainObject::MapKeyTypeTerrain)
	{
		ValueMap* properties = new ValueMap(args->properties);
		CategoryName categoryName = properties->at(SerializableObject::MapKeyName).asString();
		float width = properties->at(SerializableObject::MapKeyWidth).asFloat();
		float height = properties->at(SerializableObject::MapKeyHeight).asFloat();
		float x = properties->at(SerializableObject::MapKeyXPosition).asFloat() + width / 2.0f;
		float y = properties->at(SerializableObject::MapKeyYPosition).asFloat() + height / 2.0f;

		if (GameUtils::keyExists(properties, SerializableObject::MapKeyPolyLinePoints))
		{
			ValueVector* polygonPoints = &(properties->at(SerializableObject::MapKeyPolyLinePoints).asValueVector());
			Vec2* points = new Vec2[polygonPoints->size()];
			Vec2* collisionAdjustedPoints = new Vec2[polygonPoints->size()];
			int index = 0;

			// Step 1) Parse the collision points
			for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
			{
				auto point = it->asValueMap();

				float deltaX = point.at(SerializableObject::MapKeyXPosition).asFloat();
				float deltaY = point.at(SerializableObject::MapKeyYPosition).asFloat();

				// Hahahaha but not for collision... (thanks, cocos, for being so consistent)
				collisionAdjustedPoints[index] = Vec2(deltaX, -deltaY);

				index++;
			}

			// Create collision object
			PhysicsBody* physicsBody = PhysicsBody::createEdgePolygon(collisionAdjustedPoints, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
			CollisionObject* collisionObject = new CollisionObject(properties, physicsBody, categoryName, false, false);

			// Step 2) Create black in-fill. Unfortunately cocos does not support concave shapes, so we have to use some library to un-concavify things
			uint32_t MaxPointCount = polygonPoints->size();
			size_t MemoryRequired = MPE_PolyMemoryRequired(MaxPointCount);
			void* memory = calloc(MemoryRequired, 1);
			MPEPolyContext polyContext;

			if (MPE_PolyInitContext(&polyContext, memory, MaxPointCount))
			{
				index = 0;

				for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
				{
					auto point = it->asValueMap();

					float deltaX = point.at(SerializableObject::MapKeyXPosition).asFloat();
					float deltaY = point.at(SerializableObject::MapKeyYPosition).asFloat();

					// Negate the Y since we're operating in a different coordinate system
					points[index] = Vec2(deltaX, -deltaY);

					// Create a version of this point for our Constrained Delauney Triangulation (CDT) library
					MPEPolyPoint* Point = MPE_PolyPushPoint(&polyContext);
					Point->X = points[index].x;
					Point->Y = points[index].y;

					index++;
				}

				// Add the polyline for the edge. This will consume all points added so far.
				MPE_PolyAddEdge(&polyContext);

				// Triangulate the shape
				MPE_PolyTriangulate(&polyContext);

				// Parse out the triangle and create the in-fill color from that
				for (uxx triangleIndex = 0; triangleIndex < polyContext.TriangleCount; ++triangleIndex)
				{
					MPEPolyTriangle* triangle = polyContext.Triangles[triangleIndex];
					DrawNode* infillColor = DrawNode::create();

					Vec2 trianglePointA = Vec2(triangle->Points[0]->X, triangle->Points[0]->Y);
					Vec2 trianglePointB = Vec2(triangle->Points[1]->X, triangle->Points[1]->Y);
					Vec2 trianglePointC = Vec2(triangle->Points[2]->X, triangle->Points[2]->Y);

					const Color4B brown = Color4B(32, 8, 8, 255);
					infillColor->drawTriangle(trianglePointA, trianglePointB, trianglePointC, Color4F(brown));
					collisionObject->addChild(infillColor);
				}
			}

			// Fire an event indicating successful deserialization
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(collisionObject));
		}
	}
}
