#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerGradient;
}

class GridObject;

class Grid : public SmartNode
{
public:
	static Grid* create();

	void addGridObject(GridObject* gridObject);
	cocos2d::Vec2 coordsToLocation(cocos2d::Vec2 coords);
	float getHorizon();

	static const int lineRows;
	static const int lineColumns;

private:
	Grid();
	~Grid();

	void initializePositions();
	void onEnter() override;
	void update(float dt) override;

	cocos2d::Node* createLine(cocos2d::Vec2 source, cocos2d::Vec2 destination, cocos2d::Color4F color);
	void runForeverScroll();
	float getGridOffset();

	std::vector<cocos2d::Node*> horizontalLines;
	std::vector<cocos2d::Node*> verticalLines;
	std::vector<GridObject*> gridObjects;
	cocos2d::LayerGradient* distanceGradient;

	static const float backPlane;
	static const int specialLineColumns;

	static const cocos2d::Color4F gridColor;
	static const cocos2d::Color4F specialGridColor;

	static const float scrollSpeed;
	static const float objectSpeed;
	static const std::string ScheduleKeyScrollGridObjects;
};
