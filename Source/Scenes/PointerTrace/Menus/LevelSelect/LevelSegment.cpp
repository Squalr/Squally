#include "LevelSegment.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/PointerTrace/Menus/LevelSelect/LevelNode.h"

#include "Resources/PointerTraceResources.h"

using namespace cocos2d;

LevelSegment* LevelSegment::create(SegmentType segmentType)
{
	LevelSegment* instance = new LevelSegment(segmentType);

	instance->autorelease();

	return instance;
}

LevelSegment::LevelSegment(SegmentType segmentType)
{
	this->mapNodes = std::vector<LevelNode*>();
	this->segmentType = segmentType;
	this->mapNode = Node::create();
	this->mapSprite = nullptr;

	this->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->addChild(this->mapNode);
}

LevelSegment::~LevelSegment()
{
}

void LevelSegment::initializePositions()
{
	super::initializePositions();

	if (this->mapSprite != nullptr)
	{
		this->setContentSize(this->mapSprite->getContentSize());
	}
}

void LevelSegment::initializeListeners()
{
	super::initializeListeners();
}

LevelSegment::SegmentType LevelSegment::getSegmentType()
{
	return this->segmentType;
}

void LevelSegment::pushLevel(LevelNode* levelNode)
{
	this->mapNodes.push_back(levelNode);

	this->addChild(levelNode);
}

void LevelSegment::loadSprite(PieceType pieceType)
{
	switch (this->segmentType)
	{
		default:
		case SegmentType::EndianForest:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::EndianForest);
			break;
		}
		case SegmentType::UnderflowRuins:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::UnderflowRuins);
			break;
		}
		case SegmentType::SeaSharpCaverns:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::SeaSharpCaverns);
			break;
		}
		case SegmentType::CastleValgrind:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::CastleValgrind);
			break;
		}
		case SegmentType::BalmerPeaks:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::BalmerPeaks);
			break;
		}
		case SegmentType::DaemonsHallow:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::DaemonsHallow);
			break;
		}
		case SegmentType::LambdaCrypts:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::LambdaCrypts);
			break;
		}
		case SegmentType::VoidStar:
		{
			this->mapSprite = Sprite::create(PointerTraceResources::VoidStar);
			break;
		}
	}

	if (this->mapSprite != nullptr)
	{
		this->mapNode->removeChild(this->mapSprite);
		this->mapNode->addChild(this->mapSprite);
	}
}
