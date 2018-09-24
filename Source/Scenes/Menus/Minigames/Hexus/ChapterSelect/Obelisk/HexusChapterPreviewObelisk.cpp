#include "HexusChapterPreviewObelisk.h"

HexusChapterPreviewObelisk* HexusChapterPreviewObelisk::create()
{
	HexusChapterPreviewObelisk* instance = new HexusChapterPreviewObelisk();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewObelisk::HexusChapterPreviewObelisk()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
}

HexusChapterPreviewObelisk::~HexusChapterPreviewObelisk()
{
}

void HexusChapterPreviewObelisk::initializePositions()
{
	HexusChapterPreview::initializePositions();
}