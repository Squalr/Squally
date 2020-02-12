#include "TextureObject.h"

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

std::string TextureObject::MapKeyTypeTexture = "texture";
std::string TextureObject::MapPropertyKeyIsPartOfTerrain = "part-of-terrain";

TextureObject::TextureObject(ValueMap& properties, TextureData terrainData) : super(properties)
{
	this->terrainData = terrainData;
	this->points = std::vector<Vec2>();
	this->segments = std::vector<std::tuple<Vec2, Vec2>>();
	this->textureTriangles = std::vector<AlgoUtils::Triangle>();
	this->infillTexturesNode = Node::create();
	this->boundsRect = Rect::ZERO;

	this->addChild(this->infillTexturesNode);

	// Build the terrain from the parsed points
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

		this->useClipping = false;
	}
	else
	{
		this->setPoints(this->polylinePoints);
		this->useClipping = true;
	}

	this->buildTextures();
}

TextureObject::~TextureObject()
{ 
}

void TextureObject::setPoints(std::vector<Vec2> points)
{
	this->points = points;
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->points);
	this->textureTriangles = AlgoUtils::trianglefyPolygon(this->points);
}

void TextureObject::buildTextures()
{
	this->infillTexturesNode->removeAllChildren();

	if (this->textureTriangles.empty())
	{
		return;
	}

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;

	Sprite* texture = Sprite::create(this->terrainData.textureResource);
	Rect drawRect = AlgoUtils::getPolygonRect(this->points);

	this->boundsRect = Rect(drawRect.origin + this->getPosition(), drawRect.size);

	if (!GameUtils::getKeyOrDefault(this->properties, TextureObject::MapPropertyKeyIsPartOfTerrain, Value(false)).asBool())
	{
		texture->setAnchorPoint(Vec2::ZERO);
	}
	
	texture->getTexture()->setTexParameters(params);
	texture->setPosition(drawRect.origin);
	texture->setTextureRect(Rect(0.0f, 0.0f, drawRect.size.width, drawRect.size.height));

	if (this->useClipping)
	{
		DrawNode* stencil = DrawNode::create();

		for (auto it = this->textureTriangles.begin(); it != this->textureTriangles.end(); it++)
		{
			AlgoUtils::Triangle triangle = *it;

			stencil->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F::GREEN);
		}

		ClippingNode* clip = ClippingNode::create(stencil);

		clip->addChild(texture);

		this->infillTexturesNode->addChild(clip);
	}
	else
	{
		this->infillTexturesNode->addChild(texture);
	}
}
