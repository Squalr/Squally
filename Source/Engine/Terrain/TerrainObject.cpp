#include "TerrainObject.h"

std::string TerrainObject::MapKeyTypeTerrain = "terrain";
const bool TerrainObject::EnableTerrainDebugging = true;
const float TerrainObject::ShadowDistance = 32.0f;
const float TerrainObject::InfillDistance = 128.0f;

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
	this->triangles = std::vector<AlgoUtils::Triangle>();

	this->edgeCollisionNode = Node::create();
	this->infillTexturesNode = Node::create();
	this->infillNode = Node::create();
	this->shadowsNode = Node::create();
	this->topsNode = Node::create();
	this->leftWallNode = Node::create();
	this->rightWallNode = Node::create();
	this->bottomsNode = Node::create();
	this->debugNode = Node::create();

	this->addChild(this->edgeCollisionNode);
	this->addChild(this->infillTexturesNode);
	this->addChild(this->infillNode);
	this->addChild(this->shadowsNode);
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
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->points);
	this->triangles = AlgoUtils::trianglefyPolygon(this->points);
}

void TerrainObject::rebuildTerrain()
{
	this->debugNode->removeAllChildren();

	this->buildCollisionEdge();
	this->buildInnerTextures();
	this->buildInfill(Color4B(11, 30, 39, 255));
	this->buildSurfaceShadow();
	this->buildSurfaceTextures();
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
	this->infillTexturesNode->removeAllChildren();

	DrawNode* stencil = DrawNode::create();

	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		stencil->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F::GREEN);
	}

	ClippingNode* clip = ClippingNode::create(stencil);

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;

	Sprite* texture = Sprite::create(TerrainResources::CastleTexture);
	Rect drawRect = AlgoUtils::getPolygonRect(this->points);

	texture->setAnchorPoint(Vec2(0.0f, 0.0f));
	texture->getTexture()->setTexParameters(params);
	texture->setPosition(drawRect.origin);
	texture->setTextureRect(Rect(0.0f, 0.0f, drawRect.size.width - drawRect.origin.x, drawRect.size.height - drawRect.origin.y));
	clip->addChild(texture);

	this->infillTexturesNode->addChild(clip);
}

void TerrainObject::buildInfill(Color4B infillColor)
{
	this->infillNode->removeAllChildren();

	std::vector<Vec2> infillPoints = AlgoUtils::insetPolygon(this->triangles, this->segments, TerrainObject::InfillDistance);
	std::vector<AlgoUtils::Triangle> infillTriangles = AlgoUtils::trianglefyPolygon(infillPoints);

	DrawNode* infill = DrawNode::create();

	// Invisible padding up to the original triangle size
	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(Color3B(infillColor), 0.000001f));
	}

	// Loop over all infill triangles and create the solid infill color
	for (auto it = infillTriangles.begin(); it != infillTriangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		if (TerrainObject::EnableTerrainDebugging)
		{
			// infill->drawPolygon(triangle.coords, 3, Color4F(infillColor), 2.0f, Color4F::RED);
			infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillColor));
		}
		else
		{
			infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillColor));
		}
	}

	// Render the infill to a texture (Note: using the rect from the outer points, not the infill points, due to the earlier padding)
	Rect infillRect = AlgoUtils::getPolygonRect(this->points);
	Size infillSize = Size(infillRect.size.width - infillRect.origin.x, infillRect.size.height - infillRect.origin.y);
	RenderTexture* renderedInfill = RenderTexture::create(infillSize.width, infillSize.height);

	infill->setPosition(-infillRect.origin);
	renderedInfill->begin();
	infill->visit();
	renderedInfill->end();

	// Rasterize the texture to a sprite (required for shader to work properly)
	Sprite* rasterizedInfill = renderedInfill->getSprite();

	rasterizedInfill->setAnchorPoint(Vec2::ZERO);
	rasterizedInfill->setPosition(infillRect.origin);

	this->infillNode->addChild(rasterizedInfill);

	GLProgram* blur = GLProgram::createWithFilenames(ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(blur);

	state->setUniformVec2("resolution", Vec2(infillSize.width, infillSize.height));
	state->setUniformFloat("blurRadius", 128.0f);
	state->setUniformFloat("sampleNum", 24.0f);

	rasterizedInfill->setGLProgram(blur);
	rasterizedInfill->setGLProgramState(state);
	blur->use();
}

void TerrainObject::buildSurfaceShadow()
{
	this->shadowsNode->removeAllChildren();

	std::vector<Vec2> shadowPoints = AlgoUtils::insetPolygon(this->triangles, this->segments, TerrainObject::ShadowDistance);

	DrawNode* shadowLine = DrawNode::create(8.0);

	shadowLine->drawPoly(shadowPoints.data(), shadowPoints.size(), true, Color4F::BLACK);

	// Render the infill to a texture (Note: using the rect from the outer points, not the infill points, due to the earlier padding)
	Rect infillRect = AlgoUtils::getPolygonRect(this->points);
	Size infillSize = Size(infillRect.size.width - infillRect.origin.x, infillRect.size.height - infillRect.origin.y);
	RenderTexture* renderedShadowLine = RenderTexture::create(infillSize.width, infillSize.height);

	shadowLine->setPosition(-infillRect.origin);
	renderedShadowLine->begin();
	shadowLine->visit();
	renderedShadowLine->end();

	// Rasterize the texture to a sprite (required for shader to work properly)
	Sprite* rasterizedShadow = renderedShadowLine->getSprite();

	rasterizedShadow->setAnchorPoint(Vec2::ZERO);
	rasterizedShadow->setPosition(infillRect.origin);

	this->infillNode->addChild(rasterizedShadow);

	GLProgram* blur = GLProgram::createWithFilenames(ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(blur);

	state->setUniformVec2("resolution", Vec2(infillSize.width, infillSize.height));
	state->setUniformFloat("blurRadius", 32.0f);
	state->setUniformFloat("sampleNum", 8.0f);

	rasterizedShadow->setGLProgram(blur);
	rasterizedShadow->setGLProgramState(state);
	blur->use();

	this->shadowsNode->addChild(rasterizedShadow);
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
		std::tuple<Vec2, Vec2> nextSegment = (++itClone) == this->segments.end() ? this->segments[0] : (*itClone);
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);
		Vec2 delta = dest - source;
		Vec2 midPoint = source.getMidpoint(dest);
		float currentSegmentLength = source.distance(dest);
		float angle = AlgoUtils::getSegmentAngle(segment, this->triangles, TerrainObject::EnableTerrainDebugging ? this->debugNode : nullptr);
		float nextAngle = AlgoUtils::getSegmentAngle(nextSegment, this->triangles);
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
