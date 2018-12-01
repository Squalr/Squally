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
	this->innerTexturesNode = Node::create();
	this->infillNode = Node::create();
	this->topsNode = Node::create();
	this->leftWallNode = Node::create();
	this->rightWallNode = Node::create();
	this->bottomsNode = Node::create();
	this->debugNode = Node::create();

	this->addChild(this->edgeCollisionNode);
	this->addChild(this->innerTexturesNode);
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

	float sum = 0.0f;

	for (auto it = this->segments.begin(); it != this->segments.end(); it++)
	{
		std::tuple<Vec2, Vec2> segment = *it;
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);

		sum += (dest.x - source.y) * (dest.y - source.y);
	}

	// If counter clockwise (sum > 0.0f), reverse the point/segment order
	if (sum > 0.0f)
	{
		std::reverse(this->points.begin(), this->points.end());
		std::reverse(this->segments.begin(), this->segments.end());
	}
}

void TerrainObject::rebuildTerrain()
{
	this->debugNode->removeAllChildren();

	this->shardPolygon();
	this->buildCollisionEdge();
	this->buildInnerTextures();
	this->buildInfill(Color4B(11, 30, 39, 255));
	this->buildSurfaceTextures();
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

void TerrainObject::buildInnerTextures()
{
	this->innerTexturesNode->removeAllChildren();

	DrawNode* stencil = DrawNode::create();

	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		ShardedTriangle triangle = *it;

		stencil->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F::GREEN);
	}

	ClippingNode* clip = ClippingNode::create(stencil);

	Rect drawRect = Rect::ZERO;

	for (auto it = this->points.begin(); it != this->points.end(); it++)
	{
		Vec2 point = *it;

		drawRect.origin.x = std::min(drawRect.origin.x, point.x);
		drawRect.origin.y = std::min(drawRect.origin.y, point.y);
		drawRect.size.width = std::max(drawRect.size.width, point.x);
		drawRect.size.height = std::max(drawRect.size.height, point.y);
	}

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;

	Sprite* texture = Sprite::create(TerrainResources::CastleTexture);

	texture->setAnchorPoint(Vec2(0.0f, 0.0f));
	texture->getTexture()->setTexParameters(params);
	texture->setPosition(drawRect.origin);
	texture->setTextureRect(Rect(0.0f, 0.0f, drawRect.size.width - drawRect.origin.x, drawRect.size.height - drawRect.origin.y));
	clip->addChild(texture);

	this->innerTexturesNode->addChild(clip);
}

void TerrainObject::buildInfill(Color4B infillColor)
{
	this->infillNode->removeAllChildren();

	DrawNode* infill = DrawNode::create();

	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		ShardedTriangle triangle = *it;

		if (TerrainObject::EnableTerrainDebugging)
		{
			infill->drawPolygon(triangle.coords, 3, Color4F(infillColor), 2.0f, Color4F::RED);
		}
		else
		{
			infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillColor));
		}
	}

	// Magic trick to not cover up the texture entirely
	infill->setScale(0.75f);

	this->infillNode->addChild(infill);
}

void TerrainObject::buildSurfaceTextures()
{
	this->topsNode->removeAllChildren();
	this->leftWallNode->removeAllChildren();
	this->rightWallNode->removeAllChildren();
	this->bottomsNode->removeAllChildren();

	const float cornerAngleDelta = M_PI / 3.0f;
	float seamlessSegmentX = 0.0f;
	std::tuple<Vec2, Vec2>* previousSegment = nullptr;

	for (auto it = this->segments.begin(); it != this->segments.end(); it++)
	{
		auto itClone = it;

		std::tuple<Vec2, Vec2> segment = *it;
		std::tuple<Vec2, Vec2>* nextSegment = (++itClone) == this->segments.end() ? nullptr : &(*itClone);
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);
		Vec2 delta = dest - source;
		Vec2 midPoint = source.getMidpoint(dest);
		float currentSegmentLength = source.distance(dest);
		float angle = this->getSegmentAngle(segment);

		float nextAngle = nextSegment == nullptr ? angle : this->getSegmentAngle(*nextSegment);
		float bisectingAngle = (nextAngle + angle) / 2.0f;
		float angleDelta = nextAngle - angle;

		// Create parameters to repeat the texture
		Texture2D::TexParams params = Texture2D::TexParams();
		params.minFilter = GL_LINEAR;
		params.magFilter = GL_LINEAR;
		params.wrapS = GL_REPEAT;

		if (TerrainObject::EnableTerrainDebugging)
		{
			std::stringstream angleStream;
			angleStream << std::fixed << std::setprecision(2) << (angle * 180.0f / M_PI);
			std::string angleString = angleStream.str();

			std::stringstream bisectingAngleStream;
			bisectingAngleStream << std::fixed << std::setprecision(2) << (bisectingAngle * 180.0f / M_PI);
			std::string bisectingAngleString = bisectingAngleStream.str();

			Label* angleDebug = Label::create(angleString, Localization::getCodingFont(), Localization::getFontSizeP(Localization::getCodingFont()));
			Label* bisectingAngleDebug = Label::create(bisectingAngleString, Localization::getCodingFont(), Localization::getFontSizeP(Localization::getCodingFont()));

			angleDebug->setTextColor(Color4B::YELLOW);
			bisectingAngleDebug->setTextColor(Color4B::MAGENTA);

			angleDebug->setPosition(midPoint + Vec2(0.0f, 24.0f));
			bisectingAngleDebug->setPosition(dest + Vec2(0.0f, 24.0f));

			this->debugNode->addChild(angleDebug);
			this->debugNode->addChild(bisectingAngleDebug);
		}

		if (angle > M_PI * 3.0f / 4.0f && angle < M_PI * 5.0f / 4.0f)
		{
			Sprite* top = Sprite::create(TerrainResources::Castle);
			Size textureSize = top->getContentSize();
		
			// Calculate overdraw to create seamless rectangle connection
			if (std::abs(angleDelta) < cornerAngleDelta)
			{
				// Guess that geometry class paid off
				float hypotenuse = textureSize.height;
				float sinTheta = std::sin(bisectingAngle);
				float overDraw = std::ceil(std::abs(sinTheta * hypotenuse));

				currentSegmentLength += overDraw;
			}

			// Prevent off-by-1 rendering errors where texture pixels are barely separated
			currentSegmentLength = std::ceil(currentSegmentLength);

			top->setAnchorPoint(Vec2(0.5f, 1.0f));
			top->getTexture()->setTexParameters(params);

			// Start the texture from where the previous texture left off for seamless integration
			top->setTextureRect(Rect(seamlessSegmentX, 0, currentSegmentLength, textureSize.height));

			top->setPosition(source.getMidpoint(dest) + Vec2(0.0f, textureSize.height / 2.0f));
			top->setRotation(180.0f - angle * 180.0f / M_PI);

			// Advance the seamless segment distance (with wrap around on overflow)
			seamlessSegmentX = std::remainderf(seamlessSegmentX + currentSegmentLength, textureSize.width);

			this->topsNode->addChild(top);
		}

		previousSegment = &segment;
	}
}

Vec2 TerrainObject::getOutwardNormal(std::tuple<Vec2, Vec2> segment)
{
	// Distance used to check which direction is "inside" the terrain
	const float INNER_NORMAL_COLLISION_TEST_DISTANCE = 48.0f;

	Vec2 source = std::get<0>(segment);
	Vec2 dest = std::get<1>(segment);
	Vec2 delta = dest - source;
	Vec2 midPoint = source.getMidpoint(dest);
	Vec2 outwardNormal = Vec2(-delta.getNormalized().y, delta.getNormalized().x);
	Vec2 candidateTestingPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * outwardNormal;

	// There are two possible normals -- check if the one we picked is the surface normal
	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		ShardedTriangle triangle = *it;

		if (this->isPointInShard(triangle, candidateTestingPoint))
		{
			// We chose an inward normal instead of an outward normal -- fix it
			outwardNormal *= -1.0f;
			break;
		}
	}

	if (TerrainObject::EnableTerrainDebugging)
	{
		Vec2 outwardNormalPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * outwardNormal;

		DrawNode* sourcePointDebug = DrawNode::create();
		DrawNode* midPointDebug = DrawNode::create();
		DrawNode* candidateNormalDebug = DrawNode::create(1.0f);
		DrawNode* normalDebug = DrawNode::create();

		sourcePointDebug->drawDot(source, 4.0f, Color4F::BLUE);
		normalDebug->drawLine(midPoint, outwardNormalPoint, Color4F::YELLOW);
		normalDebug->drawDot(outwardNormalPoint, 4.0f, Color4F::YELLOW);
		candidateNormalDebug->drawLine(midPoint, candidateTestingPoint, Color4F::GREEN);
		candidateNormalDebug->drawDot(candidateTestingPoint, 3.0f, Color4F::GREEN);
		midPointDebug->drawDot(midPoint, 8.0f, Color4F::MAGENTA);

		this->debugNode->addChild(sourcePointDebug);
		this->debugNode->addChild(normalDebug);
		this->debugNode->addChild(candidateNormalDebug);
		this->debugNode->addChild(midPointDebug);
	}

	return outwardNormal;
}

float TerrainObject::getSegmentAngle(std::tuple<Vec2, Vec2> segment)
{
	Vec2 outwardNormal = this->getOutwardNormal(segment);
	float angle = std::atan2(outwardNormal.y, outwardNormal.x);

	// Because we used the outward normal to find the angle, correct the angle by 90 degrees
	angle += M_PI / 2.0f;

	// Make it positive for my sanity
	angle = std::fmod(angle, 2.0f * M_PI);

	if (angle < 0)
	{
		angle += 2.0f * M_PI;
	}

	// Not really sure why, but this needs to be negated
	return angle;
}

bool TerrainObject::isPointInShard(ShardedTriangle triangle, Vec2 point)
{
	int as_x = point.x - triangle.coords[0].x;
	int as_y = point.y - triangle.coords[0].y;
	bool s_ab = (triangle.coords[1].x - triangle.coords[0].x) * as_y - (triangle.coords[1].y - triangle.coords[0].y) * as_x > 0;

	if ((triangle.coords[2].x - triangle.coords[0].x) * as_y - (triangle.coords[2].y - triangle.coords[0].y) * as_x > 0 == s_ab || 
		(triangle.coords[2].x - triangle.coords[1].x) * (point.y - triangle.coords[1].y) - (triangle.coords[2].y - triangle.coords[1].y) * (point.x - triangle.coords[1].x) > 0 != s_ab)
	{
		return false;
	}

	return true;
}

void TerrainObject::debugCollisionPoints(Vec2 origin)
{
	if (TerrainObject::EnableTerrainDebugging)
	{
		const int NUMBER_OF_POINTS = 256;

		DrawNode* points = DrawNode::create();

		for (int index = 0; index < NUMBER_OF_POINTS; index++)
		{
			Vec2 point = origin + Vec2(RandomHelper::random_real(-256.0f, 256.0f), RandomHelper::random_real(-256.0f, 256.0f));

			bool isPointInAnyShard = false;

			for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
			{
				ShardedTriangle triangle = *it;

				if (this->isPointInShard(triangle, point))
				{
					isPointInAnyShard = true;
					break;
				}
			}

			if (isPointInAnyShard)
			{
				points->drawPoint(Vec2(point.x, point.y), 3.0f, Color4F::ORANGE);
			}
			else
			{
				points->drawPoint(Vec2(point.x, point.y), 3.0f, Color4F::RED);
			}
		}

		this->debugNode->addChild(points);
	}
}
