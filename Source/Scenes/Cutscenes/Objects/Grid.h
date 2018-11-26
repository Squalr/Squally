#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "GridObject.h"

using namespace cocos2d;

class Grid : public Node
{
public:
	static Grid* create();

	void addGridObject(GridObject* gridObject);
	Vec2 coordsToLocation(Vec2 coords);
	float getHorizon();

	static const int lineRows;
	static const int lineColumns;

private:
	Grid();
	~Grid();

	void initializePositions();
	void onEnter() override;
	void update(float dt) override;

	Node* createLine(Vec2 source, Vec2 destination, Color4F color);
	void runForeverScroll();
	float getGridOffset();

	std::vector<Node*>* horizontalLines;
	std::vector<Node*>* verticalLines;
	std::vector<GridObject*>* gridObjects;
	LayerGradient* distanceGradient;

	static const float backPlane;
	static const int specialLineColumns;

	static const Color4F gridColor;
	static const Color4F specialGridColor;

	static const float scrollSpeed;
	static const float objectSpeed;
	static const std::string ScheduleKeyScrollGridObjects;
};
