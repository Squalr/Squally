#include "MiniMapTerrainObject.h"

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

const std::string MiniMapTerrainObject::MapKey = "terrain";
const std::string MiniMapTerrainObject::PropertyMiniMapHidden = "mini-map-hidden";
const std::string MiniMapTerrainObject::TagMiniMapTerrain = "mini-map-terrain";

MiniMapTerrainObject::MiniMapTerrainObject(ValueMap& properties, TerrainObject::TerrainData terrainData) : super(properties)
{
	this->terrainData = terrainData;
	this->points = std::vector<Vec2>();
	this->infillTriangles = std::vector<AlgoUtils::Triangle>();
	this->isInactive = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString() == CollisionObject::MapKeyCollisionTypeNone;
	this->isMiniMapHidden = GameUtils::getKeyOrDefault(this->properties, MiniMapTerrainObject::PropertyMiniMapHidden, Value(false)).asBool();

	this->addTag(MiniMapTerrainObject::TagMiniMapTerrain);

	this->rootNode = Node::create();
	this->infillNode = Node::create();

	this->rootNode->addChild(this->infillNode);
	this->addChild(this->rootNode);
}

MiniMapTerrainObject::~MiniMapTerrainObject()
{ 
}

void MiniMapTerrainObject::onEnter()
{
	super::onEnter();

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

	this->buildInfill(terrainData.infillData);
}

void MiniMapTerrainObject::setPoints(std::vector<Vec2> points)
{
	this->points = points;
	this->infillTriangles = AlgoUtils::trianglefyPolygon(this->points);
}

void MiniMapTerrainObject::buildInfill(TerrainObject::InfillData infillData)
{
	if (this->isInactive || this->isMiniMapHidden)
	{
		return;
	}

	this->infillNode->removeAllChildren();

	DrawNode* infill = DrawNode::create();

	// Loop over all infill triangles and create the solid infill color
	for (auto it = this->infillTriangles.begin(); it != this->infillTriangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		infill->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F(infillData.infillColor));
	}

	this->infillNode->addChild(infill);
}
