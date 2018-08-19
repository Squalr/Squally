#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"

using namespace cocos2d;

class VaporNet : public Cutscene
{
public:
	static VaporNet* create();

protected:
	VaporNet();
	~VaporNet();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();
	void endCutscene();

	Node* createLine(Vec2 source, Vec2 destination);
	void runForeverScroll();

	int getCellIndex(int row, int column);
	float getHorizon();
	float getGridOffset();
	Vec2 coordsToLocation(Vec2 coords);

	Sprite* gridBackground;
	std::vector<Node*>* horizontalLines;
	std::vector<Node*>* verticalLines;
	std::map<int, Sprite*>* cells;

	static const int cellRows;
	static const int cellColumns;
	static const int lineRows;
	static const int lineColumns;
	static const float backPlane;

	static const float scrollSpeed;

	static const Color4F gridColor;
};
