#pragma once
#include <map>
#include <vector>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class HexusChapterPreview;
class HexusChapterPreviewTrainingPuzzle;
class HexusChapterPreviewBalmerPeaksPuzzle;
class HexusChapterPreviewCastleValgrindPuzzle;
class HexusChapterPreviewDaemonsHallowPuzzle;
class HexusChapterPreviewEndianForestPuzzle;
class HexusChapterPreviewLambdaCryptsPuzzle;
class HexusChapterPreviewSeaSharpCavernsPuzzle;
class HexusChapterPreviewUnderflowRuinsPuzzle;
class HexusChapterPreviewVoidStarPuzzle;
class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;

class HexusChapterSelectMenuPuzzles : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	HexusChapterSelectMenuPuzzles();
	~HexusChapterSelectMenuPuzzles();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick();
	void onDeckManagementClick();
	void onShopClick();
	void onMouseOver(HexusChapterPreview* hexusChapterPreview);

	std::vector<HexusChapterPreview*> chapters;
	std::map<HexusChapterPreview*, HexusChapterPreview*> dependencies;

	cocos2d::Node* backgroundNode;

	HexusChapterPreviewTrainingPuzzle* hexusChapterPreviewTrainingPuzzle;
	HexusChapterPreviewBalmerPeaksPuzzle* hexusChapterPreviewBalmerPeaksPuzzle;
	HexusChapterPreviewCastleValgrindPuzzle* hexusChapterPreviewCastleValgrindPuzzle;
	HexusChapterPreviewDaemonsHallowPuzzle* hexusChapterPreviewDaemonsHallowPuzzle;
	HexusChapterPreviewEndianForestPuzzle* hexusChapterPreviewEndianForestPuzzle;
	HexusChapterPreviewLambdaCryptsPuzzle* hexusChapterPreviewLambdaCryptsPuzzle;
	HexusChapterPreviewSeaSharpCavernsPuzzle* hexusChapterPreviewSeaSharpCavernsPuzzle;
	HexusChapterPreviewUnderflowRuinsPuzzle* hexusChapterPreviewUnderflowRuinsPuzzle;
	HexusChapterPreviewVoidStarPuzzle* hexusChapterPreviewVoidStarPuzzle;

	LocalizedLabel* chapterSelectLabel;
	ClickableTextNode* backButton;

	static HexusChapterSelectMenuPuzzles* instance;
};
