#include "TerrainObject.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/renderer/CCGLProgram.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/RenderUtils.h"

#include "Resources/ShaderResources.h"

using namespace cocos2d;

std::string TerrainObject::MapKeyTypeTexture = "texture";
std::string TerrainObject::MapKeyTypeTerrain = "terrain";
std::string TerrainObject::MapKeyCollisionDisabled = "collision-disabled";
const float TerrainObject::ShadowDistance = 32.0f;
const float TerrainObject::InfillDistance = 128.0f;
const float TerrainObject::TopThreshold = M_PI / 6.0f;
const float TerrainObject::BottomThreshold = 7 * M_PI / 6.0f;

TerrainObject* TerrainObject::deserialize(ValueMap* initProperties, TerrainData terrainData)
{
	TerrainObject* instance = new TerrainObject(initProperties, terrainData);

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

TerrainObject::TerrainObject(ValueMap* initProperties, TerrainData terrainData) : HackableObject(initProperties)
{
	this->terrainData = terrainData;
	this->points = std::vector<Vec2>();
	this->segments = std::vector<std::tuple<Vec2, Vec2>>();
	this->triangles = std::vector<AlgoUtils::Triangle>();

	this->collisionNode = Node::create();
	this->infillTexturesNode = Node::create();
	this->infillNode = Node::create();
	this->shadowsNode = Node::create();
	this->leftWallNode = Node::create();
	this->rightWallNode = Node::create();
	this->bottomsNode = Node::create();
	this->bottomCornersNode = Node::create();
	this->topsNode = Node::create();
	this->topCornersNode = Node::create();
	this->debugNode = Node::create();

	this->debugNode->setVisible(false);

	this->addChild(this->collisionNode);
	this->addChild(this->infillTexturesNode);
	this->addChild(this->infillNode);
	this->addChild(this->shadowsNode);
	this->addChild(this->leftWallNode);
	this->addChild(this->rightWallNode);
	this->addChild(this->bottomsNode);
	this->addChild(this->bottomCornersNode);
	this->addChild(this->topsNode);
	this->addChild(this->topCornersNode);
	this->addChild(this->debugNode);
}

TerrainObject::~TerrainObject()
{
}

void TerrainObject::onEnter()
{
	super::onEnter();
}

void TerrainObject::onDeveloperModeEnable()
{
	this->debugNode->setVisible(true);
}

void TerrainObject::onDeveloperModeDisable()
{
	this->debugNode->setVisible(false);
}

void TerrainObject::initializeListeners()
{
	super::initializeListeners();
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

	this->buildCollision();
	this->buildInnerTextures();
	this->buildInfill(Color4B(11, 30, 39, 255));
	this->buildSurfaceShadow();
	this->buildSurfaceTextures();
}

void TerrainObject::buildCollision()
{
	this->collisionNode->removeAllChildren();

	// Check if physics is disabled for this terrain
	if (GameUtils::keyExists(this->properties, TerrainObject::MapKeyCollisionDisabled) && !(*this->properties)[TerrainObject::MapKeyCollisionDisabled].asBool())
	{
		return;
	}

	ValueMap collisionProperties = ValueMap(*this->properties);

	// Clear x/y position -- this is already handled by this TerrainObject, and would otherwise result in incorrectly placed collision
	collisionProperties[SerializableObject::MapKeyXPosition] = 0.0f;
	collisionProperties[SerializableObject::MapKeyYPosition] = 0.0f;

	std::string deserializedCollisionName = collisionProperties.at(SerializableObject::MapKeyName).asString();

	// Create terrain collision as a series of triangles -- the other option is 1 giant EdgePolgyon, but this lacks internal collision
	for (auto it = this->triangles.begin(); it != this->triangles.end(); it++)
	{
		PhysicsBody* physicsBody = PhysicsBody::createPolygon((*it).coords, 3, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		CollisionObject* collisionObject = new CollisionObject(&collisionProperties, physicsBody, deserializedCollisionName, false, false);

		this->collisionNode->addChild(collisionObject);
	}
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

	Sprite* texture = Sprite::create(this->terrainData.textureResource);
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

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(Color3B(infillColor), 0.0f));
	}

	// Loop over all infill triangles and create the solid infill color
	for (auto it = infillTriangles.begin(); it != infillTriangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillColor));
	}

	// Render the infill to a texture (Note: using outer points, not the infill points, due to the earlier padding)
	Rect infillRect = AlgoUtils::getPolygonRect(this->points);
	GLProgram* blur = GLProgram::createWithFilenames(ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(blur);

	state->setUniformVec2("resolution", Vec2(infillRect.size.width, infillRect.size.height));
	state->setUniformFloat("blurRadius", 112.0f);
	state->setUniformFloat("sampleNum", 24.0f);

	Sprite* renderedInfill = RenderUtils::renderDrawNode(infill, infillRect.origin, infillRect.size);
	Sprite* rasterizedInfill = RenderUtils::applyShaderOnce(renderedInfill, blur, state);

	this->infillNode->addChild(rasterizedInfill);
}

void TerrainObject::buildSurfaceShadow()
{
	this->shadowsNode->removeAllChildren();

	std::vector<Vec2> shadowPoints = AlgoUtils::insetPolygon(this->triangles, this->segments, TerrainObject::ShadowDistance);
	std::vector<AlgoUtils::Triangle> shadowTriangles = AlgoUtils::trianglefyPolygon(shadowPoints);
	std::vector<std::tuple<Vec2, Vec2>> shadowSegments = AlgoUtils::buildSegmentsFromPoints(shadowPoints);

	DrawNode* shadowLine = DrawNode::create(12.0f);

	// Draw shadow lines below the floors
	for (auto it = shadowSegments.begin(); it != shadowSegments.end(); it++)
	{
		std::tuple<Vec2, Vec2> segment = *it;
		Vec2 source = std::get<0>(segment);
		Vec2 dest = std::get<1>(segment);
		Vec2 delta = dest - source;
		Vec2 midPoint = source.getMidpoint(dest);
		float currentSegmentLength = source.distance(dest);
		float normalAngle = AlgoUtils::getSegmentNormalAngle(segment, shadowTriangles);

		if (normalAngle >= TerrainObject::TopThreshold && normalAngle <= M_PI - TerrainObject::TopThreshold)
		{
			shadowLine->drawLine(source, dest, Color4F::BLACK);
		}
	}

	// Render the infill to a texture (Note: using outer points for padding)
	Rect shadowRect = AlgoUtils::getPolygonRect(this->points);
	GLProgram* blur = GLProgram::createWithFilenames(ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(blur);

	state->setUniformVec2("resolution", Vec2(shadowRect.size.width, shadowRect.size.height));
	state->setUniformFloat("blurRadius", 32.0f);
	state->setUniformFloat("sampleNum", 12.0f);

	Sprite* renderedShadowLine = RenderUtils::renderDrawNode(shadowLine, shadowRect.origin, shadowRect.size);
	Sprite* rasterizedShadowLine = RenderUtils::applyShaderOnce(renderedShadowLine, blur, state);

	this->shadowsNode->addChild(rasterizedShadowLine);
}

void TerrainObject::buildSurfaceTextures()
{
	this->leftWallNode->removeAllChildren();
	this->rightWallNode->removeAllChildren();
	this->bottomsNode->removeAllChildren();
	this->bottomCornersNode->removeAllChildren();
	this->topsNode->removeAllChildren();
	this->topCornersNode->removeAllChildren();

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
		float angle = AlgoUtils::getSegmentAngle(segment, this->triangles, this->debugNode);
		float normalAngle = AlgoUtils::getSegmentNormalAngle(segment, this->triangles);
		float nextAngle = AlgoUtils::getSegmentAngle(nextSegment, this->triangles);
		float nextSegmentNormalAngle = AlgoUtils::getSegmentNormalAngle(nextSegment, this->triangles);
		float bisectingAngle = (nextAngle + angle) / 2.0f;
		float angleDelta = nextAngle - angle;

		std::stringstream angleStream;
		angleStream << std::fixed << std::setprecision(2) << (angle * 180.0f / M_PI);
		ConstantString* angleString = ConstantString::create(angleStream.str());

		std::stringstream bisectingAngleStream;
		bisectingAngleStream << std::fixed << std::setprecision(2) << (bisectingAngle * 180.0f / M_PI);
		ConstantString* bisectingAngleString = ConstantString::create(bisectingAngleStream.str());

		LocalizedLabel* angleDebug = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, angleString);
		LocalizedLabel* bisectingAngleDebug = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, bisectingAngleString);

		angleDebug->setTextColor(Color4B::YELLOW);
		bisectingAngleDebug->setTextColor(Color4B::MAGENTA);

		angleDebug->setPosition(midPoint + Vec2(0.0f, 24.0f));
		bisectingAngleDebug->setPosition(dest + Vec2(0.0f, 24.0f));

		this->debugNode->addChild(angleDebug);
		this->debugNode->addChild(bisectingAngleDebug);

		auto buildSegment = [&](Node* parent, Sprite* sprite, Vec2 anchor, Vec2 offset, float initialAngle, bool isTextureHorizontal)
		{
			Size textureSize = sprite->getContentSize();

			// Create parameters to repeat the texture
			Texture2D::TexParams params = Texture2D::TexParams();
			params.minFilter = GL_LINEAR;
			params.magFilter = GL_LINEAR;

			if (isTextureHorizontal)
			{
				params.wrapS = GL_REPEAT;
			}
			else
			{
				params.wrapT = GL_REPEAT;
			}

			// Calculate overdraw to create seamless rectangle connection
			// TODO: clear seg length on side change
			// TEMP: This is a mediocre correction to the gap problem
			if (isTextureHorizontal)
			{
				float hypotenuse = textureSize.height;
				float sinTheta = std::sin(bisectingAngle);
				float overDraw = std::ceil(std::abs(sinTheta * hypotenuse));

				currentSegmentLength += overDraw;
			}

			// Prevent off-by-1 rendering errors where texture pixels are barely separated
			currentSegmentLength = std::ceil(currentSegmentLength);

			sprite->setAnchorPoint(anchor);
			sprite->getTexture()->setTexParameters(params);

			// Start the texture from where the previous texture left off for seamless integration
			if (isTextureHorizontal)
			{
				sprite->setTextureRect(Rect(seamlessSegmentX, 0.0f, currentSegmentLength, textureSize.height));
			}
			else
			{
				sprite->setTextureRect(Rect(0.0f, seamlessSegmentX, textureSize.width, currentSegmentLength));
			}

			sprite->setPosition(source.getMidpoint(dest) + offset);
			sprite->setRotation(initialAngle - angle * 180.0f / M_PI);

			// Advance the seamless segment distance (with wrap around on overflow)
			seamlessSegmentX = std::remainderf(seamlessSegmentX + currentSegmentLength, isTextureHorizontal ? textureSize.width : textureSize.height);

			parent->addChild(sprite);
		};

		if (this->isTopAngle(normalAngle))
		{
			Sprite* top = Sprite::create(this->terrainData.topResource);

			buildSegment(this->topsNode, top, Vec2(0.5f, 1.0f), Vec2(0.0f, top->getContentSize().height / 2.0f), 180.0f, true);
		}
		else if (this->isBottomAngle(normalAngle))
		{
			Sprite* bottom = Sprite::create(this->terrainData.bottomResource);

			buildSegment(this->bottomsNode, bottom, Vec2(0.5f, 0.0f), Vec2(0.0f, -bottom->getContentSize().height / 2.0f), 360.0f, true);
		}
		else if (this->isLeftAngle(normalAngle))
		{
			Sprite* left = Sprite::create(this->terrainData.leftResource);

			buildSegment(this->leftWallNode, left, Vec2(0.0f, 0.5f), Vec2(0.0f, 0.0f), 270.0f, false);
		}
		else
		{
			Sprite* right = Sprite::create(this->terrainData.rightResource);

			buildSegment(this->rightWallNode, right, Vec2(1.0f, 0.5f), Vec2(0.0f, 0.0f), 90.0f, false);
		}

		// Figure out what the transition is between this segment and the next
		bool floorToWall = this->isTopAngle(normalAngle) && !this->isTopAngle(nextSegmentNormalAngle);
		bool wallToFloor = !this->isTopAngle(normalAngle) && this->isTopAngle(nextSegmentNormalAngle);
		bool roofToWall = this->isBottomAngle(normalAngle) && !this->isBottomAngle(nextSegmentNormalAngle);
		bool wallToRoof = !this->isBottomAngle(normalAngle) && this->isBottomAngle(nextSegmentNormalAngle);

		// A slight anchor offset to make the top corners overlap a bit with the floor terrain -- if they entirely extrude, there is often a 1-2px gap
		// Note that this is not needed for the bottom corners -- bottom corners already overlap entirely with the roof material (they don't extrude)
		const float TOP_ANCHOR_X_OFFSET = 0.1f;

		// Handle case when going from floor to walls
		if (floorToWall || wallToFloor)
		{
			Vec2 nextSource = std::get<0>(nextSegment);
			Vec2 nextDest = std::get<1>(nextSegment);

			if ((floorToWall && nextSource.x <= source.x) || (wallToFloor && nextDest.x >= dest.x))
			{
				Sprite* topLeft = Sprite::create(this->terrainData.topCornerLeftResource);
				Size textureSize = topLeft->getContentSize();

				
				topLeft->setAnchorPoint(Vec2(1.0f - TOP_ANCHOR_X_OFFSET, 1.0f));
				topLeft->setPosition(dest + Vec2(0.0f, topLeft->getContentSize().height / 2.0f));
				topLeft->setRotation(180.0f - (floorToWall ? angle : nextAngle) * 180.0f / M_PI);

				this->topCornersNode->addChild(topLeft);
			}
			else
			{
				Sprite* topRight = Sprite::create(this->terrainData.topCornerRightResource);
				Size textureSize = topRight->getContentSize();

				topRight->setAnchorPoint(Vec2(0.0f + TOP_ANCHOR_X_OFFSET, 1.0f));
				topRight->setPosition(dest + Vec2(0.0f, topRight->getContentSize().height / 2.0f));
				topRight->setRotation(180.0f - (floorToWall ? angle : nextAngle) * 180.0f / M_PI);

				this->topCornersNode->addChild(topRight);
			}
		}
		// Handle case when going from roof to walls
		else if (roofToWall || wallToRoof)
		{
			Vec2 nextSource = std::get<0>(nextSegment);
			Vec2 nextDest = std::get<1>(nextSegment);

			if ((roofToWall && nextSource.x <= source.x) || (wallToRoof && nextDest.x >= dest.x))
			{
				Sprite* bottomLeft = Sprite::create(this->terrainData.bottomCornerLeftResource);
				Size textureSize = bottomLeft->getContentSize();

				bottomLeft->setAnchorPoint(Vec2(0.0f, 0.0f));
				bottomLeft->setPosition(dest + Vec2(0.0f, -bottomLeft->getContentSize().height / 2.0f));
				bottomLeft->setRotation(360.0f - (roofToWall ? angle : nextAngle) * 180.0f / M_PI);

				this->bottomCornersNode->addChild(bottomLeft);
			}
			else
			{
				Sprite* bottomRight = Sprite::create(this->terrainData.bottomCornerRightResource);
				Size textureSize = bottomRight->getContentSize();

				bottomRight->setAnchorPoint(Vec2(1.0f, 0.0f));
				bottomRight->setPosition(dest + Vec2(0.0f, -bottomRight->getContentSize().height / 2.0f));
				bottomRight->setRotation(360.0f - (roofToWall ? angle : nextAngle) * 180.0f / M_PI);

				this->bottomCornersNode->addChild(bottomRight);
			}
		}

		previousSegment = &segment;
	}
}

bool TerrainObject::isTopAngle(float normalAngle)
{
	return normalAngle >= TerrainObject::TopThreshold && normalAngle <= M_PI - TerrainObject::TopThreshold;
}

bool TerrainObject::isBottomAngle(float normalAngle)
{
	return normalAngle >= TerrainObject::BottomThreshold && normalAngle <= 2.0f * M_PI - (TerrainObject::BottomThreshold - M_PI);
}

bool TerrainObject::isLeftAngle(float normalAngle)
{
	return (!this->isTopAngle(normalAngle) && !this->isBottomAngle(normalAngle) && normalAngle <= TerrainObject::BottomThreshold);
}

bool TerrainObject::isRightAngle(float normalAngle)
{
	return (!this->isTopAngle(normalAngle) && !this->isBottomAngle(normalAngle) && !this->isLeftAngle(normalAngle));
}

