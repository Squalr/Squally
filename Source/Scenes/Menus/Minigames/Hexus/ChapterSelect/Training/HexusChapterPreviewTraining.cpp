#include "HexusChapterPreviewTraining.h"

HexusChapterPreviewTraining* HexusChapterPreviewTraining::create()
{
	HexusChapterPreviewTraining* instance = new HexusChapterPreviewTraining();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewTraining::HexusChapterPreviewTraining()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameTraining));
	this->text->setString("Training Grounds");
}

HexusChapterPreviewTraining::~HexusChapterPreviewTraining()
{
}

void HexusChapterPreviewTraining::initializePositions()
{
	HexusChapterPreview::initializePositions();
}