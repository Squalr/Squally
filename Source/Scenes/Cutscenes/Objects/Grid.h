#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class Grid : public Node
{
public:
	static Grid* create();

	Vec2 coordsToLocation(Vec2 coords);
	float getHorizon();

	static const int lineRows;
	static const int lineColumns;

private:
	Grid();
	~Grid();

	void initializePositions();
	void onEnter() override;

	Node* createLine(Vec2 source, Vec2 destination, Color4F color);
	void runForeverScroll();
	float getGridOffset();

	std::vector<Node*>* horizontalLines;
	std::vector<Node*>* verticalLines;
	LayerGradient* distanceGradient;

	static const float backPlane;
	static const int specialLineColumns;

	static const Color4F gridColor;
	static const Color4F specialGridColor;

	static const float scrollSpeed;
};
