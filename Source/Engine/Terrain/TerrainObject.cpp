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
	this->points = std::vector<Vec2>();
	this->segments = std::vector<std::tuple<Vec2, Vec2>>();
	
	this->collisionNode = nullptr;
	this->infillNode = nullptr;
	this->topsNode = nullptr;
	this->leftWallNode = nullptr;
	this->rightWallNode = nullptr;
	this->bottomsNode = nullptr;
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

	Vec2* previous = nullptr;

	for (auto it = this->points.begin(); it != this->points.end(); it++)
	{
		if (previous != nullptr)
		{
			this->segments.push_back(std::tuple<Vec2, Vec2>(*it, *previous));
		}

		previous = &(*it);
	}

	// Loop to start
	if (this->points.size() >= 2)
	{
		this->segments.push_back(std::tuple<Vec2, Vec2>(this->points[0], this->points.back()));
	}
}

void TerrainObject::rebuildTerrain()
{
	this->removeAllChildren();

	this->buildCollisionBounds();
	this->buildInfill(Color4B::BLACK);
	this->buildBottoms();
	this->buildLeftWall();
	this->buildRightWall();
	this->buildTops();
}

void TerrainObject::buildCollisionBounds()
{
	if (this->collisionNode != nullptr)
	{
		this->removeChild(this->collisionNode);
	}

	ValueMap collisionProperties = ValueMap(*this->properties);

	// Clear x/y position -- this is already handled by this TerrainObject, and would otherwise result in incorrectly placed collision
	collisionProperties[SerializableObject::MapKeyXPosition] = 0.0f;
	collisionProperties[SerializableObject::MapKeyYPosition] = 0.0f;

	// Create collision object
	CategoryName categoryName = collisionProperties.at(SerializableObject::MapKeyName).asString();
	PhysicsBody* physicsBody = PhysicsBody::createEdgePolygon(this->points.data(), this->points.size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	this->collisionNode = new CollisionObject(&collisionProperties, physicsBody, categoryName, false, false);

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

void TerrainObject::buildTops()
{
	if (this->topsNode != nullptr)
	{
		this->removeChild(this->topsNode);
	}

	this->topsNode = Node::create();

	// Distance used to check which direction is "inside" the terrain
	const float INNER_NORMAL_COLLISION_TEST_DISTANCE = 8.0f;

	float seamlessSegmentX = 0.0f;

	for (auto it = this->segments.begin(); it != this->segments.end(); it++)
	{
		std::tuple<Vec2, Vec2> segment = *it;
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);
		Vec2 delta = dest - source;
		Vec2 normal = delta.getNormalized();
		Vec2 candidateInnerNormal = source.getMidpoint(dest) + INNER_NORMAL_COLLISION_TEST_DISTANCE * Vec2(normal.x, -normal.y);
		bool isCandidateInnerNormalOutside = true;
		auto shapes = this->collisionNode->getPhysicsBody()->getShapes();

		// There are two possible normals -- check if the one we picked is the surface normal (if not, we pick the other normal)
		for (auto it = shapes.begin(); it != shapes.end(); it++)
		{
			if ((*it)->containsPoint(candidateInnerNormal))
			{
				isCandidateInnerNormalOutside = false;
				break;
			}
		}

		Vec2 outerNormal = isCandidateInnerNormalOutside ? Vec2(normal.x, -normal.y) : Vec2(-normal.x, normal.y);
		float angle = delta.x == 0.0f ? 0.0f : std::atan2(outerNormal.y, outerNormal.x) - M_PI;
		float angleDegrees = angle * 180.0f / M_PI;

		Sprite* top = Sprite::create(TerrainResources::Castle);
		Texture2D::TexParams params = Texture2D::TexParams();
		Size textureSize = top->getContentSize();
		float currentSegmentLength = source.distance(dest);

		// Set parameters to repeat the texture
		params.minFilter = GL_LINEAR;
		params.magFilter = GL_LINEAR;
		params.wrapS = GL_REPEAT;

		top->setAnchorPoint(Vec2(0.5f, 1.0f));
		top->getTexture()->setTexParameters(params);

		// Start the texture from where the previous texture left off for seamless integration
		top->setTextureRect(Rect(seamlessSegmentX, 0, currentSegmentLength, textureSize.height));

		// Center the sprite between the two nodes, but offset it vertically so that the collision is part way through the sprite
		top->setPosition(source.getMidpoint(dest) + Vec2(0.0f, textureSize.height / 2.0f));
		top->setRotation(angleDegrees);

		// Advance the seamless segment distance (with wrap around on overflow)
		seamlessSegmentX = std::remainderf(seamlessSegmentX + currentSegmentLength, textureSize.width);

		this->topsNode->addChild(top);
	}

	this->addChild(this->topsNode);
}

void TerrainObject::buildLeftWall()
{
	if (this->leftWallNode != nullptr)
	{
		this->removeChild(this->leftWallNode);
	}

	this->leftWallNode = Node::create();

	this->addChild(this->leftWallNode);
}

void TerrainObject::buildRightWall()
{
	if (this->rightWallNode != nullptr)
	{
		this->removeChild(this->rightWallNode);
	}

	this->rightWallNode = Node::create();

	this->addChild(this->rightWallNode);
}

void TerrainObject::buildBottoms()
{
	if (this->bottomsNode != nullptr)
	{
		this->removeChild(this->bottomsNode);
	}

	this->bottomsNode = Node::create();

	this->addChild(this->bottomsNode);
}
