#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Caverns/HexusChapterPreviewCaverns.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/IceCaps/HexusChapterPreviewIceCaps.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Jungle/HexusChapterPreviewJungle.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Mech/HexusChapterPreviewMech.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Obelisk/HexusChapterPreviewObelisk.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Ruins/HexusChapterPreviewRuins.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"

using namespace cocos2d;

class HexusChapterSelectMenu : public FadeScene
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
	void onCloseClick(MenuSprite* menuSprite);
	void onDeckManagementClick(MenuSprite* menuSprite);
	void onMouseOver(HexusChapterPreview* hexusChapterPreview);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	std::vector<HexusChapterPreview*>* chapters;
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
	Label* chapterSelectLabel;
};

