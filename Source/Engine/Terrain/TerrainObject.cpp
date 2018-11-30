#include "TerrainObject.h"

std::string TerrainObject::MapKeyTypeTerrain = "terrain";

TerrainObject* TerrainObject::deserialize(ValueMap* initProperties)
{
	TerrainObject* instance = new TerrainObject(initProperties);

	instance->autorelease();

	ValueMap* properties = new ValueMap(*initProperties);

	if (!GameUtils::keyExists(properties, SerializableObject::MapKeyPolyLinePoints))
	{
		LogUtils::logError("Missing polyline on terrain");

		return instance;
	}

	ValueVector* polygonPointsRaw = &(properties->at(SerializableObject::MapKeyPolyLinePoints).asValueVector());
	std::vector<Vec2> polygonPoints;

	for (auto it = polygonPointsRaw->begin(); it != polygonPointsRaw->end(); ++it)
	{
		auto point = it->asValueMap();

		float deltaX = point.at(SerializableObject::MapKeyXPosition).asFloat();
		float deltaY = point.at(SerializableObject::MapKeyYPosition).asFloat();

		// Negate the Y since we're operating in a different coordinate system
		polygonPoints.push_back(Vec2(deltaX, -deltaY));
	}

	// Build the terrain from the parsed points
	instance->setPoints(polygonPoints);
	instance->rebuildTerrain();

	return instance;
}

TerrainObject::TerrainObject(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->collisionNode = nullptr;
	this->infillNode = nullptr;
}

TerrainObject::~TerrainObject()
{
}

void TerrainObject::onEnter()
{
	HackableObject::onEnter();
}

void TerrainObject::initializeListeners()
{
	HackableObject::initializeListeners();
}

void TerrainObject::setPoints(std::vector<Vec2> points)
{
	this->points = points;
}

void TerrainObject::rebuildTerrain()
{
	this->removeAllChildren();

	const Color4B brown = Color4B(32, 8, 8, 255);

	this->buildCollisionBounds();
	this->buildInfill(brown);
}

void TerrainObject::buildCollisionBounds()
{
	if (this->collisionNode != nullptr)
	{
		this->removeChild(this->collisionNode);
	}

	this->collisionNode = Node::create();

	ValueMap collisionProperties = ValueMap(*this->properties);

	// Clear x/y position -- this is already handled by this TerrainObject, and would otherwise result in incorrectly placed collision
	collisionProperties[SerializableObject::MapKeyXPosition] = 0.0f;
	collisionProperties[SerializableObject::MapKeyYPosition] = 0.0f;

	// Create collision object
	CategoryName categoryName = collisionProperties.at(SerializableObject::MapKeyName).asString();
	PhysicsBody* physicsBody = PhysicsBody::createEdgePolygon(this->points.data(), this->points.size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	CollisionObject* collisionObject = new CollisionObject(&collisionProperties, physicsBody, categoryName, false, false);

	this->collisionNode->addChild(collisionObject);
	this->addChild(this->collisionNode);
}

void TerrainObject::buildInfill(Color4B infillColor)
{
	if (this->infillNode != nullptr)
	{
		this->removeChild(this->infillNode);
	}

	this->infillNode = Node::create();

	// Building the infill requires breaking up the shape into a series of triangles, and creating a solid color of that triangle
	// This is done because cocos2d-x drawnodes do not support concave shapes

	uint32_t MaxPointCount = this->points.size();
	size_t MemoryRequired = MPE_PolyMemoryRequired(MaxPointCount);
	void* memory = calloc(MemoryRequired, 1);
	MPEPolyContext polyContext;

	if (!MPE_PolyInitContext(&polyContext, memory, MaxPointCount))
	{
		LogUtils::logError("Error initializing terrain. Possible error condition: duplicate point cordinates, bounds checking assert failures");

		return;
	}

	for (auto it = this->points.begin(); it != this->points.end(); ++it)
	{
		Vec2 point = *it;

		// Create a version of this point for our Constrained Delauney Triangulation (CDT) library
		MPEPolyPoint* Point = MPE_PolyPushPoint(&polyContext);
		Point->X = point.x;
		Point->Y = point.y;
	}

	// Add the polyline for the edge. This will consume all points added so far.
	MPE_PolyAddEdge(&polyContext);

	// Triangulate the shape
	MPE_PolyTriangulate(&polyContext);

	// Parse out the triangle and create the in-fill color from that
	for (uxx triangleIndex = 0; triangleIndex < polyContext.TriangleCount; ++triangleIndex)
	{
		MPEPolyTriangle* triangle = polyContext.Triangles[triangleIndex];
		DrawNode* infillTriangle = DrawNode::create();

		Vec2 trianglePointA = Vec2(triangle->Points[0]->X, triangle->Points[0]->Y);
		Vec2 trianglePointB = Vec2(triangle->Points[1]->X, triangle->Points[1]->Y);
		Vec2 trianglePointC = Vec2(triangle->Points[2]->X, triangle->Points[2]->Y);

		infillTriangle->drawTriangle(trianglePointA, trianglePointB, trianglePointC, Color4F(infillColor));
		this->infillNode->addChild(infillTriangle);
	}

	this->addChild(this->infillNode);
}
