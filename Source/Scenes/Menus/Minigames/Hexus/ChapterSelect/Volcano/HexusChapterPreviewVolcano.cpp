#include "HexusChapterPreviewVolcano.h"

HexusChapterPreviewVolcano* HexusChapterPreviewVolcano::create()
{
	HexusChapterPreviewVolcano* instance = new HexusChapterPreviewVolcano();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewVolcano::HexusChapterPreviewVolcano()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano));
	this->text->setString("Volcano");
}

HexusChapterPreviewVolcano::~HexusChapterPreviewVolcano()
{
}

void HexusChapterPreviewVolcano::initializePositions()
{
	HexusChapterPreview::initializePositions();
}