#include "TerrainObject.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/renderer/CCGLProgram.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Config/ConfigManager.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/TerrainEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Terrain/TextureObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/RenderUtils.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/ShaderResources.h"

using namespace cocos2d;

const std::string TerrainObject::MapKey = "terrain";
const std::string TerrainObject::PropertyTopOnly = "top-only";
const float TerrainObject::ShadowDistance = 32.0f;
const float TerrainObject::InfillDistance = 128.0f;
const float TerrainObject::TopThreshold = float(M_PI) / 6.0f;
const float TerrainObject::BottomThreshold = 7.0f * float(M_PI) / 6.0f;
unsigned int TerrainObject::NextTerrainId = 0;

TerrainObject::TerrainObject(ValueMap& properties, TerrainData terrainData) : super(properties)
{
	this->terrainObjectId = TerrainObject::NextTerrainId++;
	this->terrainData = terrainData;
	this->points = std::vector<Vec2>();
	this->intersectionPoints = std::vector<Vec2>();
	this->segments = std::vector<std::tuple<Vec2, Vec2>>();
	this->collisionSegments = std::vector<std::tuple<Vec2, Vec2>>();
	this->textureTriangles = std::vector<AlgoUtils::Triangle>();
	this->infillTriangles = std::vector<AlgoUtils::Triangle>();
	this->isTopOnlyCollision = GameUtils::getKeyOrDefault(this->properties, TerrainObject::PropertyTopOnly, Value(false)).asBool();
	this->isInactive = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString() == CollisionObject::MapKeyCollisionTypeNone;
	this->isFlipped = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool();
	this->enableHackerModeEvents = true;
	this->hasBuiltTerrain = false;
	this->isDynamic = false;

	this->addTag(TerrainObject::MapKey);

	this->setName("terrain - " + GameUtils::getKeyOrDefault(this->properties, TerrainObject::MapKey, Value("")).asString());

	this->rootNode = Node::create();
	this->collisionNode = Node::create();
	this->infillTexturesNode = Node::create();
	this->infillNode = Node::create();
	this->shadowsNode = Node::create();
	this->leftWallNode = Node::create();
	this->rightWallNode = Node::create();
	this->bottomsNode = Node::create();
	this->bottomCornersNode = Node::create();
	this->topsNode = Node::create();
	this->connectorsNode = Node::create();
	this->topCornersNode = Node::create();
	this->debugLabelsNode = DeveloperModeController::IsDeveloperBuild ? Node::create() : nullptr;
	this->debugDrawNode = DeveloperModeController::IsDeveloperBuild ? DrawNode::create() : nullptr;
	this->drawRect = Rect::ZERO;
	this->boundsRect = Rect::ZERO;

	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugLabelsNode->setVisible(false);
		this->debugDrawNode->setVisible(false);
	}
	
	this->setLocalZOrder(int32_t(this->getPositionZ()));

	this->rootNode->addChild(this->infillTexturesNode);
	this->rootNode->addChild(this->infillNode);
	this->rootNode->addChild(this->shadowsNode);
	this->rootNode->addChild(this->leftWallNode);
	this->rootNode->addChild(this->rightWallNode);
	this->rootNode->addChild(this->bottomsNode);
	this->rootNode->addChild(this->topsNode);
	this->rootNode->addChild(this->connectorsNode);
	this->rootNode->addChild(this->bottomCornersNode);
	this->rootNode->addChild(this->topCornersNode);
	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->rootNode->addChild(this->debugLabelsNode);
		this->rootNode->addChild(this->debugDrawNode);
	}
	this->rootNode->addChild(this->collisionNode);
	this->addChild(this->rootNode);
}

TerrainObject::~TerrainObject()
{ 
}

void TerrainObject::onEnter()
{
	super::onEnter();

	this->initResources();

	if (this->polylinePoints.empty())
	{
		Size size = Size(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		this->setPoints(std::vector<Vec2>({
			Vec2(-size.width / 2.0f, -size.height / 2.0f),
			Vec2(-size.width / 2.0f, size.height / 2.0f),
			Vec2(size.width / 2.0f, size.height / 2.0f),
			Vec2(size.width / 2.0f, -size.height / 2.0f)
		}));
	}
	else
	{
		this->setPoints(this->polylinePoints);
	}

	this->cullCollision();
	this->optimizationHideOffscreenTerrain();
}

void TerrainObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Should get called right after this is terrain is added to the map
	if (!this->isInactive)
	{
		TerrainEvents::TriggerResolveOverlapConflicts(TerrainEvents::TerrainOverlapArgs(this));
	}
	
	// This gets built as a deferred step since we may be waiting on masking until this point
	this->defer([=]()
	{
		this->buildCollision();
	});
}

void TerrainObject::onDeveloperModeEnable(int debugLevel)
{
	if (debugLevel >= 2 && DeveloperModeController::IsDeveloperBuild)
	{
		this->debugLabelsNode->setVisible(true);
		this->debugDrawNode->setVisible(true);
	}
}

void TerrainObject::onDeveloperModeDisable()
{
	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugLabelsNode->setVisible(false);
		this->debugDrawNode->setVisible(false);
	}
}

void TerrainObject::initializeListeners()
{
	super::initializeListeners();
	
	if (!this->isInactive)
	{
		this->addEventListener(EventListenerCustom::create(TerrainEvents::EventResolveOverlapConflicts, [=](EventCustom* eventCustom)
		{
			TerrainEvents::TerrainOverlapArgs* args = static_cast<TerrainEvents::TerrainOverlapArgs*>(eventCustom->getData());

			if (args != nullptr && args->newTerrain != this && this->terrainObjectId < args->newTerrain->terrainObjectId)
			{
				this->maskAgainstOther(args->newTerrain);
			}
		}));
	}
}

void TerrainObject::update(float dt)
{
	super::update(dt);
	
	this->optimizationHideOffscreenTerrain();
}

void TerrainObject::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->setVisible(false);
}

void TerrainObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->setVisible(true);
}

void TerrainObject::setDynamic(bool isDynamic)
{
	this->isDynamic = isDynamic;
}

void TerrainObject::initResources()
{
	if (!this->isFlipped)
	{
		return;
	}

	auto swapResources = [=](std::string* resourceA, Vec2* offsetA, std::string* resourceB, Vec2* offsetB)
	{
		std::string tempStr = *resourceA;
		Vec2 tempVec = *offsetA;

		*resourceA = *resourceB;
		*offsetA = *offsetB;
		*resourceB = tempStr;
		*offsetB = tempVec;

		offsetA->y *= -1.0f;
		offsetB->y *= -1.0f;
	};

	swapResources(
		&this->terrainData.topCornerRightResource, &this->terrainData.topRightCornerOffset,
		&this->terrainData.bottomCornerRightResource, &this->terrainData.bottomRightCornerOffset
	);

	swapResources(
		&this->terrainData.topCornerLeftResource, &this->terrainData.topLeftCornerOffset,
		&this->terrainData.bottomCornerLeftResource, &this->terrainData.bottomLeftCornerOffset
	);

	swapResources(
		&this->terrainData.topResource, &this->terrainData.topOffset,
		&this->terrainData.bottomResource, &this->terrainData.bottomOffset
	);

	swapResources(
		&this->terrainData.topConnectorResource, &this->terrainData.topConnectorOffset,
		&this->terrainData.bottomConnectorResource, &this->terrainData.bottomConnectorOffset
	);
}

void TerrainObject::setPoints(const std::vector<Vec2>& points)
{
	this->points = points;
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->points);
	this->collisionSegments = this->segments;
	this->textureTriangles = AlgoUtils::trianglefyPolygon(this->points);
	this->infillTriangles = this->textureTriangles;
	this->drawRect = AlgoUtils::getPolygonRect(this->points);
	this->boundsRect = Rect(drawRect.origin + this->getPosition(), drawRect.size);

	// Most terrain is static, so the coords only need be updated once
	this->updateCachedCoords(true);
}

void TerrainObject::cullCollision()
{
	std::string deserializedCollisionName = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString();
	
	if (deserializedCollisionName == "none")
	{
		return;
	}

	std::tuple<Vec2, Vec2>* previousSegment = nullptr;
	std::vector<std::tuple<Vec2, Vec2>> usedCollisionSegments;
	
	for (auto it = this->collisionSegments.begin(); it != this->collisionSegments.end(); it++)
	{
		auto itClone = it;
		std::tuple<Vec2, Vec2> segment = *it;
		std::tuple<Vec2, Vec2> nextSegment = (++itClone) == this->collisionSegments.end() ? this->collisionSegments[0] : (*itClone);

		float normalAngle = AlgoUtils::getSegmentNormalAngle(*it, this->textureTriangles);
		
		if ((!this->isFlipped && this->isTopAngle(normalAngle)) || (this->isFlipped && this->isBottomAngle(normalAngle)))
		{
			usedCollisionSegments.push_back(*it);
		}
		else if ((!this->isFlipped && this->isBottomAngle(normalAngle)) || (this->isFlipped && this->isTopAngle(normalAngle)))
		{
			if (this->isTopCollisionFriendly(previousSegment, &segment, &nextSegment))
			{
				usedCollisionSegments.push_back(*it);
			}
		}
		else
		{
			if (this->isTopCollisionFriendly(previousSegment, &segment, &nextSegment))
			{
				usedCollisionSegments.push_back(*it);
			}
		}
	}

	this->collisionSegments = usedCollisionSegments;
}

void TerrainObject::buildCollision()
{
	this->collisionNode->removeAllChildren();

	if (!this->terrainData.buildCollision || this->isInactive)
	{
		return;
	}

	std::string deserializedCollisionName = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString();
	
	if (deserializedCollisionName == "none")
	{
		return;
	}

	std::tuple<Vec2, Vec2>* previousSegment = nullptr;
	
	for (auto it = this->collisionSegments.begin(); it != this->collisionSegments.end(); it++)
	{
		auto itClone = it;
		std::tuple<Vec2, Vec2> segment = *it;
		std::tuple<Vec2, Vec2> nextSegment = (++itClone) == this->collisionSegments.end() ? this->collisionSegments[0] : (*itClone);

		std::vector<Vec2> shape = std::vector<Vec2>();

		shape.push_back(std::get<0>(segment));
		shape.push_back(std::get<1>(segment));
		
		CollisionObject* collisionObject = nullptr;

		float normalAngle = AlgoUtils::getSegmentNormalAngle(*it, this->textureTriangles);
		
		if ((!this->isFlipped && this->isTopAngle(normalAngle)) || (this->isFlipped && this->isBottomAngle(normalAngle)))
		{
			collisionObject = CollisionObject::create(shape, (CollisionType)EngineCollisionTypes::PassThrough, CollisionObject::Properties(false, false));
		}
		else if ((!this->isFlipped && this->isBottomAngle(normalAngle)) || (this->isFlipped && this->isTopAngle(normalAngle)))
		{
			if (this->isTopCollisionFriendly(previousSegment, &segment, &nextSegment))
			{
				collisionObject = CollisionObject::create(shape, (CollisionType)EngineCollisionTypes::SolidRoof, CollisionObject::Properties(false, false));
			}
		}
		else
		{
			if (this->isTopCollisionFriendly(previousSegment, &segment, &nextSegment))
			{
				collisionObject = CollisionObject::create(shape, (CollisionType)EngineCollisionTypes::Solid, CollisionObject::Properties(false, false));
			}
		}
		
		if (collisionObject != nullptr)
		{
			this->collisionNode->addChild(collisionObject);
		}

		previousSegment = &(*it);
	}

	for (auto intersectionPoint : this->intersectionPoints)
	{
		const float Radius = 32.0f;

		CollisionObject* collisionObject = CollisionObject::create(CollisionObject::createCircle(Radius), (CollisionType)EngineCollisionTypes::Intersection, CollisionObject::Properties(false, false));

		collisionObject->setPosition(intersectionPoint);

		this->collisionNode->addChild(collisionObject);
	}
}

void TerrainObject::buildInnerTextures()
{
	if (this->terrainData.textureFactory != nullptr)
	{
		TextureObject* textures = this->terrainData.textureFactory(this->properties);

		this->infillTexturesNode->removeAllChildren();

		if (textures != nullptr)
		{
			this->infillTexturesNode->addChild(textures);
		}
	}
}

void TerrainObject::buildInfill(InfillData infillData)
{
	this->infillNode->removeAllChildren();

	if (!infillData.applyInfill || this->textureTriangles.empty())
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

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(Color3B(infillData.infillColor), 0.0f));
	}

	// Loop over all infill triangles and create the solid infill color
	for (auto it = infillTriangles.begin(); it != infillTriangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillData.infillColor));
	}

	// Render the infill to a texture (Note: using outer points, not the infill points, due to the earlier padding)
	Rect infillRect = AlgoUtils::getPolygonRect(this->points);
	Sprite* renderedInfill = RenderUtils::renderNodeToSprite(infill, infillRect.origin, infillRect.size);

	if (infillData.blurInfill)
	{
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
	else
	{
		renderedInfill->setAnchorPoint(Vec2::ZERO);
		renderedInfill->setPosition(infillRect.origin);

		this->infillNode->addChild(renderedInfill);
	}
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
		float segmentLength = source.distance(dest);
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

void TerrainObject::buildSurfaceTextures()
{
	this->leftWallNode->removeAllChildren();
	this->rightWallNode->removeAllChildren();
	this->bottomsNode->removeAllChildren();
	this->bottomCornersNode->removeAllChildren();
	this->topsNode->removeAllChildren();
	this->topCornersNode->removeAllChildren();

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
		float segmentLength = source.distance(dest);
		float angle = AlgoUtils::getSegmentAngle(segment, this->textureTriangles, this->debugDrawNode);
		float normalAngle = AlgoUtils::getSegmentNormalAngle(segment, this->textureTriangles);
		float nextAngle = AlgoUtils::getSegmentAngle(nextSegment, this->textureTriangles);
		float nextSegmentNormalAngle = AlgoUtils::getSegmentNormalAngle(nextSegment, this->textureTriangles);
		float bisectingAngle = (nextAngle + angle) / 2.0f;
		float angleDelta = nextAngle - angle;

		// Figure out what the transition is between this segment and the next
		bool floorToWall = this->isTopAngle(normalAngle) && !this->isTopAngle(nextSegmentNormalAngle);
		bool wallToFloor = !this->isTopAngle(normalAngle) && this->isTopAngle(nextSegmentNormalAngle);
		bool roofToWall = this->isBottomAngle(normalAngle) && !this->isBottomAngle(nextSegmentNormalAngle);
		bool wallToRoof = !this->isBottomAngle(normalAngle) && this->isBottomAngle(nextSegmentNormalAngle);
		bool floorToFloor = this->isTopAngle(normalAngle) && this->isTopAngle(nextSegmentNormalAngle);
		bool leftToLeft = this->isLeftAngle(normalAngle) && this->isLeftAngle(nextSegmentNormalAngle);
		bool rightToRight = this->isRightAngle(normalAngle) && this->isRightAngle(nextSegmentNormalAngle);
		bool roofToRoof = this->isBottomAngle(normalAngle) && this->isBottomAngle(nextSegmentNormalAngle);

		if (DeveloperModeController::IsDeveloperBuild)
		{
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

			this->debugLabelsNode->addChild(angleDebug);
			this->debugLabelsNode->addChild(bisectingAngleDebug);
		}

		if (this->isTopAngle(normalAngle))
		{
			Sprite* top = Sprite::create(this->terrainData.topResource);

			top->setFlippedY(this->isFlipped);

			this->buildSegment(this->topsNode, top, Vec2(0.5f, 0.5f), source.getMidpoint(dest) + terrainData.topOffset, 180.0f - angle * 180.0f / float(M_PI), segmentLength, TileMethod::Horizontal);
		}
		else if (this->isBottomAngle(normalAngle))
		{
			Sprite* bottom = Sprite::create(this->terrainData.bottomResource);

			bottom->setFlippedY(this->isFlipped);

			this->buildSegment(this->bottomsNode, bottom, Vec2(0.5f, 0.5f), source.getMidpoint(dest) + terrainData.bottomOffset, 360.0f - angle * 180.0f / float(M_PI), segmentLength, TileMethod::Horizontal);
		}
		else if (this->isLeftAngle(normalAngle))
		{
			Sprite* left = Sprite::create(this->terrainData.leftResource);

			this->buildSegment(this->leftWallNode, left, Vec2(0.0f, 0.5f), source.getMidpoint(dest) + Vec2(0.0f, 0.0f), 270.0f - angle * 180.0f / float(M_PI), segmentLength, TileMethod::Vertical);
		}
		else
		{
			Sprite* right = Sprite::create(this->terrainData.rightResource);

			this->buildSegment(this->rightWallNode, right, Vec2(1.0f, 0.5f), source.getMidpoint(dest) + Vec2(0.0f, 0.0f), 90.0f - angle * 180.0f / float(M_PI), segmentLength, TileMethod::Vertical);
		}

		enum Concavity
		{
			Standard,
			ConvexMedium,
			ConvexDeep,
			ConcaveMedium,
			ConcaveDeep,
		};

		Concavity concavity = Concavity::Standard;
		float normalDeg = normalAngle * 180.0f / float(M_PI);
		float nextNormalDeg = nextSegmentNormalAngle * 180.0f / float(M_PI);

		// Calculate concavity, taking into account counter-clockwise terrain segment layouts
		bool isConcave = (std::get<0>(nextSegment).x > std::get<0>(segment).x) ? (nextNormalDeg > normalDeg) : (normalDeg > nextNormalDeg);
		
		if (isConcave)
		{
			// Concave
			float normalDelta = std::abs(nextNormalDeg - normalDeg);

			if (normalDelta <= 24.0f)
			{
				concavity = Concavity::Standard;
			}
			else if (normalDelta <= 96.0f)
			{
				concavity = Concavity::ConcaveMedium;
			}
			else
			{
				concavity = Concavity::ConcaveDeep;
			}
		}
		else
		{
			// Convex
			float normalDelta = std::abs(normalDeg - nextNormalDeg);

			if (normalDelta <= 24.0f)
			{
				concavity = Concavity::Standard;
			}
			else if (normalDelta <= 96.0f)
			{
				concavity = Concavity::ConvexMedium;
			}
			else
			{
				concavity = Concavity::ConvexDeep;
			}
		}

		if (floorToFloor)
		{
			Sprite* topConnector = nullptr;
			Vec2 offset = terrainData.topOffset;
			
			if (DeveloperModeController::IsDeveloperBuild)
			{
				ConstantString* str = ConstantString::create("S");
				LocalizedLabel* concavityLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, str);
				concavityLabel->setTextColor(Color4B::MAGENTA);
				concavityLabel->setPosition(dest + Vec2(0.0f, -24.0f));
				switch (concavity)
				{
					default: case Concavity::Standard: { str->setString("S"); break; }
					case Concavity::ConvexMedium: { str->setString("t"); break; }
					case Concavity::ConvexDeep: { str->setString("_T_"); break; }
					case Concavity::ConcaveMedium: { str->setString("v"); break; }
					case Concavity::ConcaveDeep: { str->setString("_V_"); break; }
				}
				this->debugLabelsNode->addChild(concavityLabel);
			}
			
			switch (concavity)
			{
				default:
				case Concavity::Standard:
				{
					topConnector = Sprite::create(this->terrainData.topConnectorResource);
					offset += this->terrainData.topOffset + this->terrainData.topConnectorOffset;
					break;
				}
				case Concavity::ConvexMedium:
				{
					topConnector = Sprite::create(this->terrainData.topConnectorConvexResource);
					offset += this->terrainData.topOffset + this->terrainData.topConnectorConvexOffset;
					break;
				}
				case Concavity::ConvexDeep:
				{
					topConnector = Sprite::create(this->terrainData.topConnectorConvexDeepResource);
					offset += this->terrainData.topOffset + this->terrainData.topConnectorConvexDeepOffset;
					break;
				}
				case Concavity::ConcaveMedium:
				{
					topConnector = Sprite::create(this->terrainData.topConnectorConcaveResource);
					offset += this->terrainData.topOffset + this->terrainData.topConnectorConcaveOffset;
					break;
				}
				case Concavity::ConcaveDeep:
				{
					topConnector = Sprite::create(this->terrainData.topConnectorConcaveDeepResource);
					offset += this->terrainData.topOffset + this->terrainData.topConnectorConcaveDeepOffset;
					break;
				}
			}

			this->buildSegment(this->connectorsNode, topConnector, Vec2(0.5f, 0.5f), dest + offset, 180.0f - bisectingAngle * 180.0f / float(M_PI), segmentLength, TileMethod::None);
		}
		else if (roofToRoof)
		{
			Sprite* bottom = Sprite::create(this->terrainData.bottomConnectorResource);
			Vec2 offset = this->terrainData.bottomOffset + this->terrainData.bottomConnectorOffset;

			bottom->setFlippedY(this->isFlipped);

			this->buildSegment(this->connectorsNode, bottom, Vec2(0.5f, 0.5f), dest + offset, 360.0f - bisectingAngle * 180.0f / float(M_PI), segmentLength, TileMethod::None);
		}

		// Handle case when going from floor to walls
		if (floorToWall || wallToFloor)
		{
			Vec2 nextSource = std::get<0>(nextSegment);
			Vec2 nextDest = std::get<1>(nextSegment);

			bool isTopLeft = (floorToWall && nextSource.x <= source.x) || (wallToFloor && nextDest.x >= dest.x);

			if (isTopLeft)
			{
				Sprite* topLeft = Sprite::create(this->terrainData.topCornerLeftResource);
				Vec2 offset = this->terrainData.topOffset + this->terrainData.topLeftCornerOffset;

				topLeft->setFlippedY(this->isFlipped);

				this->buildSegment(this->topCornersNode, topLeft, Vec2(0.5f, 0.5f), dest + offset, 180.0f - (floorToWall ? angle : nextAngle) * 180.0f / float(M_PI), segmentLength, TileMethod::None);
			}
			else
			{
				Sprite* topRight = Sprite::create(this->terrainData.topCornerRightResource);
				Vec2 offset = this->terrainData.topOffset + this->terrainData.topRightCornerOffset;

				topRight->setFlippedY(this->isFlipped);

				this->buildSegment(this->topCornersNode, topRight, Vec2(0.5f, 0.5f), dest + offset, 180.0f - (floorToWall ? angle : nextAngle) * 180.0f / float(M_PI), segmentLength, TileMethod::None);
			}
		}
		// Handle case when going from roof to walls
		else if (roofToWall || wallToRoof)
		{
			Vec2 nextSource = std::get<0>(nextSegment);
			Vec2 nextDest = std::get<1>(nextSegment);

			bool isBottomLeft = ((roofToWall && nextSource.x <= source.x) || (wallToRoof && nextDest.x >= dest.x));

			if (isBottomLeft)
			{
				Sprite* bottomLeft = Sprite::create(this->terrainData.bottomCornerLeftResource);

				bottomLeft->setFlippedY(this->isFlipped);

				this->buildSegment(this->topCornersNode, bottomLeft, Vec2(0.0f, 0.5f), dest + this->terrainData.bottomLeftCornerOffset, 360.0f - (roofToWall ? angle : nextAngle) * 180.0f / float(M_PI), segmentLength, TileMethod::None);
			}
			else
			{
				Sprite* bottomRight = Sprite::create(this->terrainData.bottomCornerRightResource);

				bottomRight->setFlippedY(this->isFlipped);

				this->buildSegment(this->topCornersNode, bottomRight, Vec2(1.0f, 0.5f), dest + this->terrainData.bottomLeftCornerOffset, 360.0f - (roofToWall ? angle : nextAngle) * 180.0f / float(M_PI), segmentLength, TileMethod::None);
			}
		}

		previousSegment = &segment;
	}
}


void TerrainObject::buildSegment(Node* parent, Sprite* sprite, Vec2 anchor, Vec2 position, float rotation, float segmentLength, TerrainObject::TileMethod tileMethod)
{
	Size textureSize = sprite->getContentSize();

	static float seamlessSegmentX = 0.0f;

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;

	switch(tileMethod)
	{
		case TileMethod::Horizontal:
		{
			params.wrapS = GL_REPEAT;
			break;
		}
		case TileMethod::Vertical:
		{
			params.wrapT = GL_REPEAT;
			break;
		}
		default:
		case TileMethod::None:
		{
			break;
		}
	}

	// Prevent off-by-1 rendering errors where texture pixels are barely separated
	segmentLength = std::ceil(segmentLength);

	sprite->setAnchorPoint(anchor);
	
	if (sprite->getTexture() != nullptr)
	{
		sprite->getTexture()->setTexParameters(params);
	}

	// Start the texture from where the previous texture left off for seamless integration
	if (tileMethod == TileMethod::Horizontal)
	{
		sprite->setTextureRect(Rect(seamlessSegmentX, 0.0f, segmentLength, textureSize.height));

		// Advance the seamless segment distance (with wrap around on overflow)
		seamlessSegmentX = MathUtils::wrappingNormalize(seamlessSegmentX + segmentLength, 0.0f, textureSize.width);
	}
	else if (tileMethod == TileMethod::Vertical)
	{
		sprite->setTextureRect(Rect(0.0f, seamlessSegmentX, textureSize.width, segmentLength));

		// Advance the seamless segment distance (with wrap around on overflow)
		seamlessSegmentX = MathUtils::wrappingNormalize(seamlessSegmentX + segmentLength, 0.0f,  textureSize.height);
	}

	sprite->setPosition(position);
	sprite->setRotation(rotation);

	parent->addChild(sprite);
};

void TerrainObject::maskAgainstOther(TerrainObject* other)
{
	if (this->isInactive
		|| !this->boundsRect.intersectsRect(other->boundsRect)
		|| (std::abs(GameUtils::getDepth(this) - GameUtils::getDepth(other))) > CollisionObject::CollisionZThreshold)
	{
		return;
	}

	std::vector<std::tuple<Vec2, Vec2>> rebuiltSegments = std::vector<std::tuple<Vec2, Vec2>>();
	
	for (auto it = this->collisionSegments.begin(); it != this->collisionSegments.end(); it++)
	{
		std::tuple<Vec2, Vec2> segment = *it;
		float normalAngle = AlgoUtils::getSegmentNormalAngle(*it, this->textureTriangles);
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
			// Entirely eclipsed, discarded
		}
		else if (isEclipsed[0] || isEclipsed[1])
		{
			Vec2 eclipsedPoint = isEclipsed[0] ? pointA : pointB;
			Vec2 anchorPoint = isEclipsed[0] ? pointB : pointA;
			std::tuple<Vec2, Vec2> eclipsedSegment = std::tuple<Vec2, Vec2>(eclipsedPoint, anchorPoint);

			for (auto segmentIt = other->segments.begin(); segmentIt != other->segments.end(); segmentIt++)
			{
				float otherNormalAngle = AlgoUtils::getSegmentNormalAngle(*segmentIt, other->textureTriangles);
				Vec2 p1 = std::get<0>(*segmentIt);
				Vec2 p2 = std::get<1>(*segmentIt);

				p1 += other->getPosition();
				p2 += other->getPosition();
				
				std::tuple<Vec2, Vec2> candidateSegment = std::tuple<Vec2, Vec2>(p1, p2);

				if (AlgoUtils::doSegmentsIntersect(eclipsedSegment, candidateSegment))
				{
					Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(eclipsedSegment, candidateSegment) - this->getPosition();

					if (isEclipsed[0])
					{
						std::get<0>(segment) = intersectionPoint;	
					}
					else
					{
						std::get<1>(segment) = intersectionPoint;	
					}
					
					if (((!this->isFlipped && this->isTopAngle(normalAngle)) || (this->isFlipped && this->isBottomAngle(normalAngle))) &&
						((!other->isFlipped && other->isTopAngle(otherNormalAngle)) || (other->isFlipped && other->isBottomAngle(otherNormalAngle))))
					{
						this->intersectionPoints.push_back(intersectionPoint);
					}
				}
			}

			rebuiltSegments.push_back(segment);
		}
		else
		{
			rebuiltSegments.push_back(*it);
		}
	}

	this->collisionSegments = rebuiltSegments;
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

bool TerrainObject::isTopCollisionFriendly(std::tuple<Vec2, Vec2>* previousSegment, std::tuple<Vec2, Vec2>* segment, std::tuple<Vec2, Vec2>* nextSegment)
{
	if (!this->isTopOnlyCollision)
	{
		return true;
	}

	if (previousSegment == nullptr || segment == nullptr || nextSegment == nullptr)
	{
		return false;
	}

	float normalAngle = AlgoUtils::getSegmentNormalAngle(*segment, this->textureTriangles);
	float prevNormalAngle = AlgoUtils::getSegmentNormalAngle(*previousSegment, this->textureTriangles);
	float nextNormalAngle = AlgoUtils::getSegmentNormalAngle(*nextSegment, this->textureTriangles);
	bool isWallCollision = (this->isLeftAngle(normalAngle) || this->isRightAngle(normalAngle));

	if (isWallCollision && this->isTopAngle(prevNormalAngle) && this->isTopAngle(nextNormalAngle))
	{
		return true;
	}

	return false;
}

ValueMap TerrainObject::transformPropertiesForTexture(ValueMap properties)
{
	ValueMap textureProperties = properties;

	textureProperties[GameObject::MapKeyType] = TextureObject::MapKeyTypeTexture;
	textureProperties[GameObject::MapKeyXPosition] = Value(0.0f);
	textureProperties[GameObject::MapKeyYPosition] = Value(0.0f);
	textureProperties[GameObject::MapKeyDepth] = Value(0.0f);
	textureProperties[TextureObject::PropertyKeyClearAnchor] = Value(!this->polylinePoints.empty());

	return textureProperties;
}

void TerrainObject::buildTerrain()
{
	if (this->hasBuiltTerrain)
	{
		return;
	}

	this->hasBuiltTerrain = true;

	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugLabelsNode->removeAllChildren();
		this->debugDrawNode->removeAllChildren();
	}

	this->buildInnerTextures();
	this->buildInfill(terrainData.infillData);

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

void TerrainObject::updateCachedCoords(bool force)
{
	if (this->isDynamic || force)
	{
		// Terrain doesn't move, this should never need to be updated.
		this->cachedCoords = GameUtils::getWorldCoords3D(this, false) + Vec3(drawRect.origin.x, drawRect.origin.y, 0.0f);
		return;
	}
}

void TerrainObject::optimizationHideOffscreenTerrain()
{
	// A little padding otherwise surface textures will pop into existence, as they can hang outside terrain bounds
	static const Size Padding = Size(128.0f, 128.0f);
	static const Rect CameraRect = Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize());

	this->updateCachedCoords();
	Rect thisRect = GameUtils::getScreenBounds(this->cachedCoords, drawRect.size + Padding);

	if (CameraRect.intersectsRect(thisRect))
	{
		this->buildTerrain();
		this->rootNode->setVisible(true);
	}
	else
	{
		this->rootNode->setVisible(false);
	}
}
