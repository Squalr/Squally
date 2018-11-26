#include "HexusChapterPreviewForest.h"

const std::string HexusChapterPreviewForest::stringKeyChapterName = "HEXUS_CHAPTER_FOREST";

HexusChapterPreviewForest* HexusChapterPreviewForest::create()
{
	HexusChapterPreviewForest* instance = new HexusChapterPreviewForest();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewForest::HexusChapterPreviewForest() : HexusChapterPreview(HexusChapterPreviewForest::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest));
	this->text->setString("Forest");
}

HexusChapterPreviewForest::~HexusChapterPreviewForest()
{
}

void HexusChapterPreviewForest::initializePositions()
{
	HexusChapterPreview::initializePositions();
}