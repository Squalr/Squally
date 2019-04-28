#pragma once

#include "Engine/SmartNode.h"
#include "Events/NavigationEvents.h"

namespace cocos2d
{
	class Sprite;
}

class LevelNode;

class LevelSegment : public SmartNode
{
public:
	enum class SegmentType
	{
		EndianForest,
		UnderflowRuins,
		SeaSharpCaverns,
		CastleValgrind,
		BalmerPeaks,
		DaemonsHallow,
		LambdaCrypts,
		VoidStar,
	};

	enum class PieceType
	{
		Normal,
		SegmentMid,
		SegmentTop,
		SegmentBottom
	};

	SegmentType getSegmentType();
	void pushLevel(LevelNode* levelNode);
	void loadSprite(PieceType pieceType);

	static LevelSegment* create(SegmentType segmentType);

protected:
	LevelSegment(SegmentType segmentType);
	~LevelSegment();

private:
	typedef SmartNode super;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 calculateMapNodePosition(float progress);

	cocos2d::Node* mapNode;
	cocos2d::Sprite* mapSprite;
	SegmentType segmentType;

	std::vector<LevelNode*> mapNodes;
};
