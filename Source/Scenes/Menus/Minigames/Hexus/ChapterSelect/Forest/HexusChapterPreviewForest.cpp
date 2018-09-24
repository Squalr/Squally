#include "HexusChapterPreviewForest.h"

HexusChapterPreviewForest* HexusChapterPreviewForest::create()
{
	HexusChapterPreviewForest* instance = new HexusChapterPreviewForest();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewForest::HexusChapterPreviewForest()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest));
	this->text->setString("Forest");
}

HexusChapterPreviewForest::~HexusChapterPreviewForest()
{
}

void HexusChapterPreviewForest::initializePositions()
{
	HexusChapterPreview::initializePositions();
}