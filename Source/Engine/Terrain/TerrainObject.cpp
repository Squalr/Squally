#include "TerrainObject.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/renderer/CCGLProgram.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/TerrainEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/RenderUtils.h"

#include "Resources/ShaderResources.h"

using namespace cocos2d;

std::string TerrainObject::MapKeyTypeIsHollow = "is-hollow";
std::string TerrainObject::MapKeyTypeTerrain = "terrain";
const float TerrainObject::ShadowDistance = 32.0f;
const float TerrainObject::InfillDistance = 128.0f;
const float TerrainObject::HollowDistance = 144.0f;
const float TerrainObject::TopThreshold = float(M_PI) / 6.0f;
const float TerrainObject::BottomThreshold = 7.0f * float(M_PI) / 6.0f;

TerrainObject::TerrainObject(ValueMap& properties, TerrainData terrainData) : super(properties)
{
	this->terrainData = terrainData;
	this->points = std::vector<Vec2>();
	this->intersectionPoints = std::vector<Vec2>();
	this->segments = std::vector<std::tuple<Vec2, Vec2>>();
	this->collisionSegments = std::vector<std::tuple<Vec2, Vec2>>();
	this->textureTriangles = std::vector<AlgoUtils::Triangle>();
	this->infillTriangles = std::vector<AlgoUtils::Triangle>();
	this->isHollow = GameUtils::getKeyOrDefault(this->properties, TerrainObject::MapKeyTypeIsHollow, Value(false)).asBool();
	this->isInactive = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString() == CollisionObject::MapKeyCollisionTypeNone;

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
	this->boundsRect = Rect::ZERO;

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

	// Build the terrain from the parsed points
	this->setPoints(this->polylinePoints);
	this->rebuildTerrain(terrainData);
}

TerrainObject::~TerrainObject()
{ 
}

void TerrainObject::onEnter()
{
	super::onEnter();

	// Should get called right after this is terrain is added to the map
	if (!this->isInactive)
	{
		TerrainEvents::TriggerResolveOverlapConflicts(TerrainEvents::TerrainOverlapArgs(this));
	}
}

void TerrainObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
	
	// This gets built as a deferred step since we may be waiting on masking until this point
	this->buildCollision();
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

	// Hollow terrain should listen for other terrain creation to remove any overlapping segments
	if (this->isHollow && !this->isInactive)
	{
		this->addEventListener(EventListenerCustom::create(TerrainEvents::EventResolveOverlapConflicts, [=](EventCustom* eventCustom)
		{
			TerrainEvents::TerrainOverlapArgs* args = static_cast<TerrainEvents::TerrainOverlapArgs*>(eventCustom->getUserData());

			if (args != nullptr && args->newTerrain != this)
			{
				this->maskAgainstOther(args->newTerrain);
			}
		}));
	}
}

void TerrainObject::setPoints(std::vector<Vec2> points)
{
	this->points = points;
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->points);
	this->collisionSegments = this->segments;
	this->textureTriangles = AlgoUtils::trianglefyPolygon(this->points);

	if (this->isHollow)
	{
		std::vector<Vec2> holes = AlgoUtils::insetPolygon(this->textureTriangles, this->segments, TerrainObject::HollowDistance);

		this->infillTriangles = AlgoUtils::trianglefyPolygon(this->points, holes);
	}
	else
	{
		this->infillTriangles = this->textureTriangles;
	}
}

void TerrainObject::rebuildTerrain(TerrainData terrainData)
{
	this->debugNode->removeAllChildren();

	this->buildInnerTextures();

	switch(ConfigManager::getGraphics())
	{
		case ConfigManager::GraphicsSetting::SlowHighQuality:
		{
			// Zac: Disabled for now since this is pretty slow
			// this->buildInfill(terrainData.infillColor);
			// this->buildSurfaceShadow();
			break;
		}
		case ConfigManager::GraphicsSetting::FastLowQuality:
		{
			break;
		}
	}

	this->buildSurfaceTextures();
}

void TerrainObject::buildCollision()
{
	this->collisionNode->removeAllChildren();

	if (this->isInactive)
	{
		return;
	}

	this->removeHollowEdgeCollisions();

	// Clear x/y position -- this is already handled by this TerrainObject, and would otherwise result in incorrectly placed collision
	this->properties[GameObject::MapKeyXPosition] = 0.0f;
	this->properties[GameObject::MapKeyYPosition] = 0.0f;

	std::string deserializedCollisionName = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString();
	
	for (auto it = this->collisionSegments.begin(); it != this->collisionSegments.end(); it++)
	{
		PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.friction = MathUtils::clamp(this->terrainData.friction, 0.0f, 1.0f);
		PhysicsBody* physicsBody = PhysicsBody::createEdgeSegment(std::get<0>(*it), std::get<1>(*it), material, 2.0f);
		CollisionObject* collisionObject = nullptr;

		if (deserializedCollisionName != "")
		{
			collisionObject = CollisionObject::create(this->properties, physicsBody, deserializedCollisionName, false, false);
		}
		else
		{
			if (this->isHollow)
			{
				collisionObject = CollisionObject::create(this->properties, physicsBody, (CollisionType)EngineCollisionTypes::PassThrough, false, false);
			}
			else
			{
				collisionObject = CollisionObject::create(this->properties, physicsBody, (CollisionType)EngineCollisionTypes::Solid, false, false);
			}
		}
		

		this->collisionNode->addChild(collisionObject);
	}

	for (auto it = this->intersectionPoints.begin(); it != this->intersectionPoints.end(); it++)
	{
		const float Radius = 32.0f;

		PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.friction = MathUtils::clamp(this->terrainData.friction, 0.0f, 1.0f);
		PhysicsBody* physicsBody = PhysicsBody::createCircle(Radius, material, *it);
		CollisionObject* collisionObject = CollisionObject::create(this->properties, physicsBody, (CollisionType)EngineCollisionTypes::Intersection, false, false);

		this->collisionNode->addChild(collisionObject);
	}
}

void TerrainObject::buildInnerTextures()
{
	this->infillTexturesNode->removeAllChildren();

	if (this->textureTriangles.empty())
	{
		return;
	}

	DrawNode* stencil = DrawNode::create();

	for (auto it = this->textureTriangles.begin(); it != this->textureTriangles.end(); it++)
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

	this->boundsRect = Rect(drawRect.origin + this->getPosition(), drawRect.size);

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

	if (this->textureTriangles.empty())
	{
		return;
	}

	if (this->isHollow)
	{
		return;
	}

	std::vector<Vec2> infillPoints = AlgoUtils::insetPolygon(this->textureTriangles, this->segments, TerrainObject::InfillDistance);
	std::vector<AlgoUtils::Triangle> infillTriangles = AlgoUtils::trianglefyPolygon(infillPoints);

	DrawNode* infill = DrawNode::create();

	// Invisible padding up to the original triangle size
	for (auto it = this->textureTriangles.begin(); it != this->textureTriangles.end(); it++)
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

	Sprite* renderedInfill = RenderUtils::renderNodeToSprite(infill, infillRect.origin, infillRect.size);
	Sprite* rasterizedInfill = RenderUtils::applyShaderOnce(renderedInfill, ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur, [=](GLProgramState* state)
	{
		state->setUniformVec2("resolution", Vec2(infillRect.size.width, infillRect.size.height));
		state->setUniformFloat("blurRadius", 112.0f);
		state->setUniformFloat("sampleNum", 24.0f);
	});
	rasterizedInfill->setAnchorPoint(Vec2::ZERO);
	rasterizedInfill->setPosition(infillRect.origin);

	this->infillNode->addChild(rasterizedInfill);
}

void TerrainObject::buildSurfaceShadow()
{
	this->shadowsNode->removeAllChildren();

	if (this->textureTriangles.empty())
	{
		return;
	}

	std::vector<Vec2> shadowPoints = AlgoUtils::insetPolygon(this->textureTriangles, this->segments, TerrainObject::ShadowDistance);
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

		if (normalAngle >= TerrainObject::TopThreshold && normalAngle <= float(M_PI) - TerrainObject::TopThreshold)
		{
			shadowLine->drawLine(source, dest, Color4F::BLACK);
		}
	}

	// Render the infill to a texture (Note: using outer points for padding)
	Rect shadowRect = AlgoUtils::getPolygonRect(this->points);

	Sprite* renderedShadowLine = RenderUtils::renderNodeToSprite(shadowLine, shadowRect.origin, shadowRect.size);

	if (renderedShadowLine != nullptr)
	{
		Sprite* rasterizedShadowLine = RenderUtils::applyShaderOnce(renderedShadowLine, ShaderResources::Vertex_Blur, ShaderResources::Fragment_Blur, [=](GLProgramState* state)
		{
			state->setUniformVec2("resolution", Vec2(shadowRect.size.width, shadowRect.size.height));
			state->setUniformFloat("blurRadius", 32.0f);
			state->setUniformFloat("sampleNum", 12.0f);
		});

		if (rasterizedShadowLine != nullptr)
		{
			rasterizedShadowLine->setAnchorPoint(Vec2::ZERO);
			rasterizedShadowLine->setPosition(shadowRect.origin);

			this->shadowsNode->addChild(rasterizedShadowLine);
		}
	}
}

void TerrainObject::removeHollowEdgeCollisions()
{
	if (!this->isHollow || this->isInactive)
	{
		return;
	}
	
	this->collisionSegments.erase(std::remove_if(this->collisionSegments.begin(), this->collisionSegments.end(),
		[=](const std::tuple<cocos2d::Vec2, cocos2d::Vec2>& segment)
		{
			float normalAngle = AlgoUtils::getSegmentNormalAngle(segment, this->textureTriangles);
			
			// Remove all collision except for top collision
			return (!this->isTopAngle(normalAngle));
		}));
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
		float angle = AlgoUtils::getSegmentAngle(segment, this->textureTriangles, this->debugNode);
		float normalAngle = AlgoUtils::getSegmentNormalAngle(segment, this->textureTriangles);
		float nextAngle = AlgoUtils::getSegmentAngle(nextSegment, this->textureTriangles);
		float nextSegmentNormalAngle = AlgoUtils::getSegmentNormalAngle(nextSegment, this->textureTriangles);
		float bisectingAngle = (nextAngle + angle) / 2.0f;
		float angleDelta = nextAngle - angle;

		std::stringstream angleStream;
		angleStream << std::fixed << std::setprecision(2) << (angle * 180.0f / float(M_PI));
		ConstantString* angleString = ConstantString::create(angleStream.str());

		std::stringstream bisectingAngleStream;
		bisectingAngleStream << std::fixed << std::setprecision(2) << (bisectingAngle * 180.0f / float(M_PI));
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
			sprite->setRotation(initialAngle - angle * 180.0f / float(M_PI));

			// Advance the seamless segment distance (with wrap around on overflow)
			seamlessSegmentX = std::remainderf(seamlessSegmentX + currentSegmentLength, isTextureHorizontal ? textureSize.width : textureSize.height);

			parent->addChild(sprite);
		};

		if (this->isTopAngle(normalAngle))
		{
			Sprite* top = Sprite::create(this->terrainData.topResource);
			Vec2 offset = Vec2(0.0f, top->getContentSize().height / 2.0f) + terrainData.topOffset;

			buildSegment(this->topsNode, top, Vec2(0.5f, 1.0f), offset, 180.0f, true);
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

		// Handle case when going from floor to walls
		if (floorToWall || wallToFloor)
		{
			Vec2 nextSource = std::get<0>(nextSegment);
			Vec2 nextDest = std::get<1>(nextSegment);

			if ((floorToWall && nextSource.x <= source.x) || (wallToFloor && nextDest.x >= dest.x))
			{
				Sprite* topLeft = Sprite::create(this->terrainData.topCornerLeftResource);
				Size textureSize = topLeft->getContentSize();

				topLeft->setAnchorPoint(Vec2(0.0f, 0.5f));
				topLeft->setPosition(dest + terrainData.topOffset + this->terrainData.topLeftCornerOffset);
				topLeft->setRotation(180.0f - (floorToWall ? angle : nextAngle) * 180.0f / float(M_PI));

				this->topCornersNode->addChild(topLeft);
			}
			else
			{
				Sprite* topRight = Sprite::create(this->terrainData.topCornerRightResource);
				Size textureSize = topRight->getContentSize();

				topRight->setAnchorPoint(Vec2(1.0f, 0.5f));
				topRight->setPosition(dest + terrainData.topOffset + terrainData.topRightCornerOffset);
				topRight->setRotation(180.0f - (floorToWall ? angle : nextAngle) * 180.0f / float(M_PI));

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

				bottomLeft->setAnchorPoint(Vec2(0.0f, 0.5f));
				bottomLeft->setPosition(dest + this->terrainData.bottomLeftCornerOffset);
				bottomLeft->setRotation(360.0f - (roofToWall ? angle : nextAngle) * 180.0f / float(M_PI));

				this->bottomCornersNode->addChild(bottomLeft);
			}
			else
			{
				Sprite* bottomRight = Sprite::create(this->terrainData.bottomCornerRightResource);
				Size textureSize = bottomRight->getContentSize();

				bottomRight->setAnchorPoint(Vec2(1.0f, 0.5f));
				bottomRight->setPosition(dest + this->terrainData.bottomRightCornerOffset);
				bottomRight->setRotation(360.0f - (roofToWall ? angle : nextAngle) * 180.0f / float(M_PI));

				this->bottomCornersNode->addChild(bottomRight);
			}
		}

		previousSegment = &segment;
	}
}

void TerrainObject::maskAgainstOther(TerrainObject* other)
{
	if (this->isInactive || !this->boundsRect.intersectsRect(other->boundsRect))
	{
		return;
	}

	// Remove all collision boxes that are completely eclipsed
	this->collisionSegments.erase(std::remove_if(this->collisionSegments.begin(), this->collisionSegments.end(),
		[=](const std::tuple<cocos2d::Vec2, cocos2d::Vec2>& segment)
		{
			int index = (&segment - &*this->collisionSegments.begin());

			Vec2 pointA = std::get<0>(segment);
			Vec2 pointB = std::get<1>(segment);
			bool isEclipsed[2] = { false, false };

			pointA += this->getPosition();
			pointB += this->getPosition();

			for (auto it = other->textureTriangles.begin(); it != other->textureTriangles.end(); it++)
			{
				AlgoUtils::Triangle triangle = *it;

				triangle.coords[0] += other->getPosition();
				triangle.coords[1] += other->getPosition();
				triangle.coords[2] += other->getPosition();

				isEclipsed[0] |= AlgoUtils::isPointInTriangle(triangle, pointA);
				isEclipsed[1] |= AlgoUtils::isPointInTriangle(triangle, pointB);

				if (isEclipsed[0] && isEclipsed[1])
				{
					break;
				}
			}

			if (isEclipsed[0] && isEclipsed[1])
			{
				return true;
			}
			else if (isEclipsed[0] || isEclipsed[1])
			{
				Vec2 eclipsedPoint = isEclipsed[0] ? pointA : pointB;
				Vec2 anchorPoint = isEclipsed[0] ? pointB : pointA;
				std::tuple<Vec2, Vec2> eclipsedSegment = std::tuple<Vec2, Vec2>(eclipsedPoint, anchorPoint);

				for (auto segmentIt = other->segments.begin(); segmentIt != other->segments.end(); segmentIt++)
				{
					cocos2d::Vec2 p1 = std::get<0>(*segmentIt);
					cocos2d::Vec2 p2 = std::get<1>(*segmentIt);

					p1 += other->getPosition();
					p2 += other->getPosition();
					
					std::tuple<Vec2, Vec2> candidateSegment = std::tuple<Vec2, Vec2>(p1, p2);

					if (AlgoUtils::doSegmentsIntersect(eclipsedSegment, candidateSegment))
					{
						Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(eclipsedSegment, candidateSegment) - this->getPosition();

						if (isEclipsed[0])
						{
							std::get<0>(this->collisionSegments[index]) = intersectionPoint;	
						}
						else
						{
							std::get<1>(this->collisionSegments[index]) = intersectionPoint;	
						}

						this->intersectionPoints.push_back(intersectionPoint);
					}
				}
			}

			return false;
		}), this->collisionSegments.end()
	);
}

bool TerrainObject::isTopAngle(float normalAngle)
{
	return normalAngle >= TerrainObject::TopThreshold && normalAngle <= float(M_PI) - TerrainObject::TopThreshold;
}

bool TerrainObject::isBottomAngle(float normalAngle)
{
	return normalAngle >= TerrainObject::BottomThreshold && normalAngle <= 2.0f * float(M_PI) - (TerrainObject::BottomThreshold - float(M_PI));
}

bool TerrainObject::isLeftAngle(float normalAngle)
{
	return (!this->isTopAngle(normalAngle) && !this->isBottomAngle(normalAngle) && normalAngle <= TerrainObject::BottomThreshold);
}

bool TerrainObject::isRightAngle(float normalAngle)
{
	return (!this->isTopAngle(normalAngle) && !this->isBottomAngle(normalAngle) && !this->isLeftAngle(normalAngle));
}

