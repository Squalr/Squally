#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/SmartScene.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Caverns/HexusChapterPreviewCaverns.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Menus/Minigames/Hexus/ChapterSelect/IceCaps/HexusChapterPreviewIceCaps.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Jungle/HexusChapterPreviewJungle.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Mech/HexusChapterPreviewMech.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Obelisk/HexusChapterPreviewObelisk.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Ruins/HexusChapterPreviewRuins.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Menus/Minigames/Hexus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

class HexusChapterSelectMenu : public SmartScene
{
public:
	static HexusChapterSelectMenu * create();

protected:
	HexusChapterSelectMenu();
	~HexusChapterSelectMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick(MenuSprite* menuSprite);
	void onDeckManagementClick(MenuSprite* menuSprite);
	void onShopClick(MenuSprite* menuSprite);
	void onMouseOver(HexusChapterPreview* hexusChapterPreview);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	std::vector<HexusChapterPreview*> chapters;
	std::map<HexusChapterPreview*, HexusChapterPreview*> dependencies;

	Sprite* background;
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
	TextMenuSprite* deckManagementButton;
	TextMenuSprite* shopButton;
	Label* chapterSelectLabel;
	TextMenuSprite* backButton;
};

