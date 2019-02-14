#pragma once
#include <map>
#include <vector>

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class HexusChapterPreview;
class HexusChapterPreviewTraining;
class HexusChapterPreviewJungle;
class HexusChapterPreviewRuins;
class HexusChapterPreviewForest;
class HexusChapterPreviewCaverns;
class HexusChapterPreviewCastle;
class HexusChapterPreviewIceCaps;
class HexusChapterPreviewVolcano;
class HexusChapterPreviewObelisk;
class HexusChapterPreviewMech;
class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;

class HexusChapterSelectMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	HexusChapterSelectMenu();
	~HexusChapterSelectMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick(ClickableNode* menuSprite);
	void onDeckManagementClick(ClickableNode* menuSprite);
	void onShopClick(ClickableNode* menuSprite);
	void onMouseOver(HexusChapterPreview* hexusChapterPreview);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	std::vector<HexusChapterPreview*> chapters;
	std::map<HexusChapterPreview*, HexusChapterPreview*> dependencies;

	cocos2d::Sprite* background;
	HexusChapterPreviewTraining* hexusChapterPreviewTraining;
	HexusChapterPreviewJungle* hexusChapterPreviewJungle;
	HexusChapterPreviewRuins* hexusChapterPreviewRuins;
	HexusChapterPreviewForest* hexusChapterPreviewForest;
	HexusChapterPreviewCaverns* hexusChapterPreviewCaverns;
	HexusChapterPreviewCastle* hexusChapterPreviewCastle;
	HexusChapterPreviewIceCaps* hexusChapterPreviewIceCaps;
	HexusChapterPreviewVolcano* hexusChapterPreviewVolcano;
	HexusChapterPreviewObelisk* hexusChapterPreviewObelisk;
	HexusChapterPreviewMech* hexusChapterPreviewMech;
	ClickableTextNode* deckManagementButton;
	ClickableTextNode* shopButton;
	LocalizedLabel* chapterSelectLabel;
	ClickableTextNode* backButton;

	static HexusChapterSelectMenu* instance;
};
