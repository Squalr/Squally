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
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/TerrainEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Terrain/TerrainHole.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/RenderUtils.h"

#include "Resources/ShaderResources.h"

using namespace cocos2d;

std::string TextureObject::MapKeyTypeTexture = "texture";
std::string TextureObject::PropertyKeyClearAnchor = "apply-anchor";

TextureObject::TextureObject(ValueMap& properties, TextureData terrainData) : super(properties)
{
	this->terrainData = terrainData;
	this->infillTexturesNode = Node::create();
	this->boundsRect = CRect::ZERO;
	this->terrainHoleTag = GameUtils::getKeyOrDefault(this->properties, TerrainHole::TerrainHoleTag, Value("")).asString();

	this->addChild(this->infillTexturesNode);
}

TextureObject::~TextureObject()
{ 
}

void TextureObject::onEnter()
{
	super::onEnter();

	bool isPolygon = GameUtils::keyExists(this->properties, GameObject::MapKeyPolyLinePoints) || GameUtils::keyExists(this->properties, GameObject::MapKeyPoints);
	
	if (!this->terrainHoleTag.empty())
	{
		ObjectEvents::QueryObjects<TerrainHole>([&](TerrainHole* terrainHole)
		{
			Vec2 holeCoords = GameUtils::getWorldCoords(terrainHole, false);
			Vec2 terrainCoords = GameUtils::getWorldCoords(GameUtils::GetFirstParentOfType<TerrainObject>(this), false);
			
			std::vector<Vec2> holePoints = terrainHole->getPolylinePoints();
			AlgoUtils::offsetPoints(holePoints, holeCoords - terrainCoords);

			this->holes.push_back(holePoints);
		}, this->terrainHoleTag);
	}

	if (isPolygon || !this->holes.empty())
	{
		this->useClipping = true;
	}
	else
	{
		this->useClipping = false;
	}

	this->buildTextures();
}

void TextureObject::buildTextures()
{
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->polylinePoints);
	this->textureTriangles = AlgoUtils::trianglefyPolygon(this->polylinePoints, this->holes);
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
	CRect sizeRect = AlgoUtils::getPolygonRect(this->polylinePoints);
	this->boundsRect = CRect(sizeRect.origin + this->getPosition(), sizeRect.size);
	bool isPolygon = GameUtils::keyExists(this->properties, GameObject::MapKeyPolyLinePoints) || GameUtils::keyExists(this->properties, GameObject::MapKeyPoints);

	texture->setAnchorPoint(Vec2::ZERO);

	if (texture->getTexture() != nullptr)
	{
		texture->getTexture()->setTexParameters(params);
	}

	// This allows for a determinstic way to make terrain tile differently.
	// Breaks up the visual sameness of similar sized terrain chunks by starting their tiling at a different position in the texture.
	// Seed the random tiling by the objects unique identifier, which we hash into an unsigned integer
	Vec2 tilingOffset = Vec2(0.0f, 0.0f);
	const std::string identifier = this->getUniqueIdentifier();
	unsigned int seed = 0;

    for (int index = 0; index < int(identifier.size()); index++)
	{
		seed ^= (identifier[index] << (index % 24));
    }
	
	srand(seed);
	tilingOffset.x = float(rand() % 4096);
	tilingOffset.y = float(rand() % 4096);

	tilingOffset.x = MathUtils::wrappingNormalize(tilingOffset.x + 757.0f, 0.0f, 1024.0f);
	tilingOffset.y = MathUtils::wrappingNormalize(tilingOffset.y + 359.0f, 0.0f, 1024.0f);
	
	texture->setPosition(sizeRect.origin);
	texture->setTextureRect(CRect(tilingOffset.x, tilingOffset.y, sizeRect.size.width, sizeRect.size.height));

	if (this->useClipping)
	{
		DrawNode* stencil = DrawNode::create();

		for (auto triangle : this->textureTriangles)
		{
			stencil->drawTriangle(triangle.coords[0], triangle.coords[1], triangle.coords[2], Color4F::GREEN);
		}

		ClippingNode* clip = ClippingNode::create(stencil);

		clip->addChild(texture);

		// Not entirely sure why this correction is needed. The fallback polyline for square objects might be constructed wrong.
		if (!isPolygon)
		{
			clip->setPosition(-Vec2(sizeRect.size) / 2.0f);
		}

		this->infillTexturesNode->addChild(clip);
	}
	else
	{
		this->infillTexturesNode->addChild(texture);
	}
}
