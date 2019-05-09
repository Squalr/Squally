#pragma once

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class LayerColor;
	class FiniteTimeAction;
	class Sprite;
}

class DialogueLabel;
class Grid;
class GridItem;
class LocalizedLabel;

class VaporWeb : public CutsceneClip
{
public:
	static VaporWeb* create();

protected:
	VaporWeb();
	~VaporWeb();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDialogueShown();
	void runCutscene();
	int getCellIndex(int row, int column);

	cocos2d::FiniteTimeAction* createCutsceneGridSetup();
	cocos2d::FiniteTimeAction* createCutsceneForest();
	cocos2d::FiniteTimeAction* createCutsceneCaverns();
	cocos2d::FiniteTimeAction* createCutsceneObelisk();

	std::map<int, GridItem*> cells;

	cocos2d::Sprite* forestBackground;
	cocos2d::Sprite* cavernsBackground;
	cocos2d::Sprite* obeliskBackground;

	Grid* grid;
	cocos2d::Sprite* darkLord;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	LocalizedLabel* escapeLabel;

	static const float dialogueHeight;

	static const int cellRows;
	static const int cellColumns;
};
