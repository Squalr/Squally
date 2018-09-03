#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"
#include "Scenes/Cutscenes/Objects/Grid.h"
#include "Scenes/Cutscenes/Objects/GridObject.h"

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

	void runCutscene();
	FiniteTimeAction* createCutsceneGridSetup();
	FiniteTimeAction* createCutsceneForest();
	FiniteTimeAction* createCutsceneCaverns();
	FiniteTimeAction* createCutsceneIceCaps();
	FiniteTimeAction* createCutsceneObelisk();

	int getCellIndex(int row, int column);

	std::map<int, GridObject*>* cells;

	Sprite* forestBackground;

	Grid* grid;
	Sprite* darkLord;

	LayerColor* dialoguePlate;
	Label* escapeLabel;

	static const float dialogueHeight;

	static const int cellRows;
	static const int cellColumns;
};
