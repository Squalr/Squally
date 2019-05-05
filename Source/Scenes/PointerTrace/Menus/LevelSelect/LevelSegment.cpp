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
	static const std::vector<Vec2> trailPoints = 
	{
		Vec2(1272, 2261), Vec2(1080, 2206), Vec2(885, 2242), Vec2(708, 2261), Vec2(507, 2216),
		Vec2(420, 2051), Vec2(468, 1875), Vec2(618, 1767), Vec2(804, 1700), Vec2(966, 1655), Vec2(1020, 1556),
		Vec2(954, 1427), Vec2(798, 1389), Vec2(618, 1350), Vec2(480, 1281), Vec2(376, 1165), Vec2(364, 978),
		Vec2(474, 858), Vec2(630, 795), Vec2(816, 786), Vec2(988, 826), Vec2(1141, 858), Vec2(1308, 877),
		Vec2(1528, 807), Vec2(1546, 618), Vec2(1408, 510), Vec2(1223, 488), Vec2(1049, 507), Vec2(879, 491),
		Vec2(767, 394), Vec2(786, 250), Vec2(942, 166), Vec2(1120, 157), Vec2(1235, 138)
	};

	const float realMax = 2561.0f;
	
	progress = MathUtils::clamp(progress, 0.0f, 1.0f);

	int trailIndex = MathUtils::clamp(int(std::round(progress * float(trailPoints.size() - 1))), 0, trailPoints.size() - 1);

	float x = trailPoints[trailIndex].x;
	float y = trailPoints[trailIndex].y;

	return Vec2(x, realMax - y);
}
