#include "TerrainObject.h"

std::string TerrainObject::MapKeyTypeTerrain = "terrain";
const bool TerrainObject::EnableTerrainDebugging = true;

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
	this->triangles = std::vector<ShardedTriangle>();

	this->edgeCollisionNode = Node::create();
	this->infillNode = Node::create();
	this->topsNode = Node::create();
	this->leftWallNode = Node::create();
	this->rightWallNode = Node::create();
	this->bottomsNode = Node::create();
	this->debugNode = Node::create();

	this->addChild(this->edgeCollisionNode);
	this->addChild(this->infillNode);
	this->addChild(this->topsNode);
	this->addChild(this->leftWallNode);
	this->addChild(this->rightWallNode);
	this->addChild(this->bottomsNode);
	this->addChild(this->debugNode);
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
			this->segments.push_back(std::tuple<Vec2, Vec2>(*previous, *it));
		}

		previous = &(*it);
	}

	// Loop to start
	if (this->points.size() >= 2)
	{
		this->segments.push_back(std::tuple<Vec2, Vec2>(this->points.back(), this->points[0]));
	}
}

void TerrainObject::rebuildTerrain()
{
	this->debugNode->removeAllChildren();

	this->shardPolygon();
	this->buildCollisionEdge();
	this->buildInfill(Color4B(11, 30, 39, 255));
	this->buildTextures();
}

void TerrainObject::shardPolygon()
{
	this->triangles.clear();

	// It turns out that in order to check if a point is inside the terrain, or to generate a solid infill color, we must shard
	// The polygon into many triangles. cocos2d-x does not support either of those on polygons, so we have to get creative

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

		this->triangles.push_back(ShardedTriangle(trianglePointA, trianglePointB, trianglePointC));
	}
}

void TerrainObject::buildCollisionEdge()
{
	this->edgeCollisionNode->removeAllChildren();

	ValueMap collisionProperties = ValueMap(*this->properties);

	// Clear x/y position -- this is already handled by this TerrainObject, and would otherwise result in incorrectly placed collision
	collisionProperties[SerializableObject::MapKeyXPosition] = 0.0f;
	collisionProperties[SerializableObject::MapKeyYPosition] = 0.0f;

	// Create collision object
	CategoryName categoryName = collisionProperties.at(SerializableObject::MapKeyName).asString();
	PhysicsBody* physicsBody = PhysicsBody::createEdgePolygon(this->points.data(), this->points.size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	this->edgeCollisionObject = new CollisionObject(&collisionProperties, physicsBody, categoryName, false, false);

	this->edgeCollisionNode->addChild(this->edgeCollisionObject);
}

void TerrainObject::buildInfill(Color4B infillColor)
{
	this->infillNode->removeAllChildren();

	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		ShardedTriangle triangle = *it;
		DrawNode* infillTriangle = DrawNode::create();

		if (TerrainObject::EnableTerrainDebugging)
		{
			infillTriangle->drawPolygon(triangle.coords, 3, Color4F(infillColor), 2.0f, Color4F::RED);
		}
		else
		{
			infillTriangle->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillColor));
		}

		this->infillNode->addChild(infillTriangle);
	}
}

void TerrainObject::buildTextures()
{
	this->topsNode->removeAllChildren();
	this->leftWallNode->removeAllChildren();
	this->rightWallNode->removeAllChildren();
	this->bottomsNode->removeAllChildren();

	const float cornerAngleDelta = M_PI / 3.0f;
	float seamlessSegmentX = 0.0f;

	for (auto it = this->segments.begin(); it != this->segments.end(); it++)
	{
		auto itClone = it;

		std::tuple<Vec2, Vec2> segment = *it;
		std::tuple<Vec2, Vec2>* nextSegment = (++itClone) == this->segments.end() ? nullptr : &(*itClone);
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);
		Vec2 delta = dest - source;
		float currentSegmentLength = source.distance(dest);
		float angle = this->getSegmentAngle(segment);
		float nextAngle = nextSegment == nullptr ? angle : this->getSegmentAngle(*nextSegment);
		float angleDeltaRad = nextAngle - angle;

		// Create parameters to repeat the texture
		Texture2D::TexParams params = Texture2D::TexParams();
		params.minFilter = GL_LINEAR;
		params.magFilter = GL_LINEAR;
		params.wrapS = GL_REPEAT;

		Sprite* top = Sprite::create(TerrainResources::Castle);
		Size textureSize = top->getContentSize();
		
		// Calculate overdraw to create seamless rectangle connection
		if (angleDeltaRad != 0.0f && std::abs(angleDeltaRad) < cornerAngleDelta)
		{
			float overDraw = std::abs(2.0f * ((textureSize.height * std::sin(angleDeltaRad)) / std::cos(angleDeltaRad)));

			// currentSegmentLength += overDraw;
		}

		top->setAnchorPoint(Vec2(0.5f, 0.5f));
		top->getTexture()->setTexParameters(params);

		// Start the texture from where the previous texture left off for seamless integration
		top->setTextureRect(Rect(seamlessSegmentX, 0, currentSegmentLength, textureSize.height));

		top->setPosition(source.getMidpoint(dest));
		top->setRotation(angle * 180.0f / M_PI);

		// Advance the seamless segment distance (with wrap around on overflow)
		seamlessSegmentX = std::remainderf(seamlessSegmentX + currentSegmentLength, textureSize.width);

		this->topsNode->addChild(top);
	}
}

Vec2 TerrainObject::getOutwardNormal(std::tuple<Vec2, Vec2> segment)
{
	// Distance used to check which direction is "inside" the terrain
	const float INNER_NORMAL_COLLISION_TEST_DISTANCE = 128.0f;

	Vec2 source = std::get<0>(segment);
	Vec2 dest = std::get<1>(segment);
	Vec2 delta = dest - source;
	Vec2 midPoint = source.getMidpoint(dest);
	Vec2 candidateNormal = Vec2(-delta.getNormalized().y, delta.getNormalized().x);
	Vec2 candidateTestingPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * candidateNormal;
	bool isCandidateOutwardFacing = true;

	// There are two possible normals -- check if the one we picked is the surface normal
	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		ShardedTriangle triangle = *it;

		if (this->isPointInShard(triangle, candidateNormal))
		{
			isCandidateOutwardFacing = false;
			break;
		}
	}

	// Pick the candidate normal if it is pointing outside, otherwise reverse it
	Vec2 outwardNormal = isCandidateOutwardFacing ? candidateNormal : (candidateNormal * -1.0f);

	if (TerrainObject::EnableTerrainDebugging)
	{
		Vec2 originalCandidateSmall = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE / 2.0f * candidateNormal;
		Vec2 outwardNormalPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * outwardNormal;

		DrawNode* sourcePointDebug = DrawNode::create();
		DrawNode* midPointDebug = DrawNode::create();
		DrawNode* candidateNormalDebug = DrawNode::create();
		DrawNode* normalDebug = DrawNode::create();

		sourcePointDebug->drawDot(source, 4.0f, Color4F::BLUE);
		normalDebug->drawLine(midPoint, outwardNormalPoint, Color4F::YELLOW);
		normalDebug->drawDot(outwardNormalPoint, 4.0f, Color4F::YELLOW);
		candidateNormalDebug->drawLine(midPoint, originalCandidateSmall, Color4F::ORANGE);
		candidateNormalDebug->drawDot(originalCandidateSmall, 4.0f, Color4F::ORANGE);
		midPointDebug->drawDot(midPoint, 8.0f, Color4F::MAGENTA);

		this->debugNode->addChild(sourcePointDebug);
		this->debugNode->addChild(candidateNormalDebug);
		this->debugNode->addChild(normalDebug);
		this->debugNode->addChild(midPointDebug);
	}

	return outwardNormal;
}

float TerrainObject::getSegmentAngle(std::tuple<Vec2, Vec2> segment)
{
	Vec2 outwardNormal = this->getOutwardNormal(segment);
	float angle = std::atan2(outwardNormal.y, outwardNormal.x);

	// Because we used the outward normal to find the angle, correct the angle by 90 degrees
	angle -= M_PI / 2.0f;

	// Not really sure why, but this needs to be negated
	return -angle;
}

bool TerrainObject::isPointInShard(ShardedTriangle triangle, Vec2 point)
{
	auto sign = [](Vec2 p1, Vec2 p2, Vec2 p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	};

	float d1 = sign(point, triangle.coords[0], triangle.coords[1]);
	float d2 = sign(point, triangle.coords[1], triangle.coords[2]);
	float d3 = sign(point, triangle.coords[2], triangle.coords[0]);
	bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}
