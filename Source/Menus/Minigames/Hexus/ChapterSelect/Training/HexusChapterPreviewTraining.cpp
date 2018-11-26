#include "HexusChapterPreviewTraining.h"

const std::string HexusChapterPreviewTraining::stringKeyChapterName = "HEXUS_CHAPTER_TRAINING";

HexusChapterPreviewTraining* HexusChapterPreviewTraining::create()
{
	HexusChapterPreviewTraining* instance = new HexusChapterPreviewTraining();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewTraining::HexusChapterPreviewTraining() : HexusChapterPreview(HexusChapterPreviewTraining::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameTraining));
	this->text->setString("Training Grounds");
}

HexusChapterPreviewTraining::~HexusChapterPreviewTraining()
{
}

void HexusChapterPreviewTraining::initializePositions()
{
	HexusChapterPreview::initializePositions();
}