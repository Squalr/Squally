#include "LevelSegment.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/MathUtils.h"
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

	this->mapNode->setAnchorPoint(Vec2::ZERO);

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

	int index = 0;
	
	for (auto it = this->mapNodes.begin(); it != this->mapNodes.end(); index++, it++)
	{
		(*it)->setPosition(this->calculateMapNodePosition(float(index) / float(this->mapNodes.size() - 1)) + (*it)->getPositionOffset());
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
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::EndianForest);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::EndianForestBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::EndianForestMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::EndianForestTop);
					break;
				}
			}

			break;
		}
		case SegmentType::UnderflowRuins:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::UnderflowRuins);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::UnderflowRuinsBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::UnderflowRuinsMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::UnderflowRuinsTop);
					break;
				}
			}

			break;
		}
		case SegmentType::SeaSharpCaverns:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::SeaSharpCaverns);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::SeaSharpCavernsBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::SeaSharpCavernsMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::SeaSharpCavernsTop);
					break;
				}
			}

			break;
		}
		case SegmentType::CastleValgrind:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::CastleValgrind);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::CastleValgrindBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::CastleValgrindMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::CastleValgrindTop);
					break;
				}
			}

			break;
		}
		case SegmentType::BalmerPeaks:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::BalmerPeaks);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::BalmerPeaksBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::BalmerPeaksMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::BalmerPeaksTop);
					break;
				}
			}

			break;
		}
		case SegmentType::DaemonsHallow:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::DaemonsHallow);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::DaemonsHallowBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::DaemonsHallowMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::DaemonsHallowTop);
					break;
				}
			}

			break;
		}
		case SegmentType::LambdaCrypts:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::LambdaCrypts);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::LambdaCryptsBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::LambdaCryptsMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::LambdaCryptsTop);
					break;
				}
			}

			break;
		}
		case SegmentType::VoidStar:
		{
			switch(pieceType)
			{
				case PieceType::Normal:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::VoidStar);
					break;
				}
				case PieceType::SegmentBottom:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::VoidStarBottom);
					break;
				}
				case PieceType::SegmentMid:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::VoidStarMid);
					break;
				}
				case PieceType::SegmentTop:
				{
					this->mapSprite = Sprite::create(PointerTraceResources::VoidStarTop);
					break;
				}
			}

			break;
		}
	}

	if (this->mapSprite != nullptr)
	{
		this->mapNode->removeChild(this->mapSprite);
		this->mapNode->addChild(this->mapSprite);

		this->mapSprite->setAnchorPoint(Vec2::ZERO);
	}
}

Vec2 LevelSegment::calculateMapNodePosition(float progress)
{
	/* Lagrange interpolate over coordinates in the map image:
	Note 1: The x and y coordinates are inverted such that this yields a proper function
	Note 2: The y coordinate is in photoshop-space, not cocos-space
	(2432.0, 1362.0), (2216.0, 1146.0), (2048.0, 420.0), (1564.0, 1028.0), (1048.0, 360.0), (728.0, 1566.0), (356.0, 768.0), (158.0, 1248.0)
	Yielding (plug this bad boy into wolfram alpha over the range 158 to 2432 to validate): 
		-1.26657*10^(-17)*x^7 +
		1.16948*10^(-13)* x^6 -
		4.33678*10^(-10)*x^5 +
		8.24414*10^(-7)*x^4 -
		0.000848483*x^3 +
		0.457377*x^2 -
		114.196*x +
		10746.9
	*/
	const float min = 158.0f;
	const float max = 2432.0f;
	const float realMax = 2588.0f;

	// Progress flows the opposite direction from what the interpolation would assume
	progress = 1.0f - MathUtils::clamp(progress, 0.0f, 1.0f);

	float x = progress * (max - min) + min;
	// Where is your god now?
	float y = -1.26657 * std::pow(10, -17) * std::pow(x, 7) +
		1.16948 * std::pow(10, -13) * std::pow(x, 6) -
		4.33678 * std::pow(10, -10) * std::pow(x, 5) +
		8.24414 * std::pow(10, -7) * std::pow(x, 4) -
		0.000848483 * std::pow(x, 3) +
		0.457377 * std::pow(x, 2) -
		114.196 * x +
		10746.9;

	// Re-invert the resulting x/y coordinates, and fix the y coordinate
	Size visibleSize = Director::getInstance()->getVisibleSize();

	return Vec2(y, realMax - x);
}
