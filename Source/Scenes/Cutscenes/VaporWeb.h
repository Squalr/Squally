#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"

using namespace cocos2d;

class VaporWeb : public Cutscene
{
public:
	static VaporWeb* create();

protected:
	VaporWeb();
	~VaporWeb();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();
	void endCutscene();

	Node* createLine(Vec2 source, Vec2 destination, Color4F color);
	void runForeverScroll();
	void cutsceneIntro();
	void cutsceneForest();
	void cutsceneCaverns();
	void cutsceneIceCaps();
	void cutsceneObelisk();

	int getCellIndex(int row, int column);
	float getHorizon();
	float getGridOffset();
	Vec2 coordsToLocation(Vec2 coords);

	Sprite* forestBackground;

	std::vector<Node*>* horizontalLines;
	std::vector<Node*>* verticalLines;
	LayerGradient* distanceGradient;
	std::map<int, Sprite*>* cells;

	Sprite* darkLord;

	LayerColor* dialogPlate;
	Label* escapeLabel;

	static const int cellRows;
	static const int cellColumns;
	static const int lineRows;
	static const int lineColumns;
	static const int specialLineColumns;
	static const float backPlane;

	static const float scrollSpeed;

	static const Color4F gridColor;
	static const Color4F specialGridColor;
};
