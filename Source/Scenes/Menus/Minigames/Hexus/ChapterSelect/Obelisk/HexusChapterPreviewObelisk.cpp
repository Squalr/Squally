#include "HexusChapterPreviewObelisk.h"

const std::string HexusChapterPreviewObelisk::stringKeyChapterName = "HEXUS_CHAPTER_OBELISK";

HexusChapterPreviewObelisk* HexusChapterPreviewObelisk::create()
{
	HexusChapterPreviewObelisk* instance = new HexusChapterPreviewObelisk();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewObelisk::HexusChapterPreviewObelisk() : HexusChapterPreview(HexusChapterPreviewObelisk::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->text->setString("The Void");
}

HexusChapterPreviewObelisk::~HexusChapterPreviewObelisk()
{
}

void HexusChapterPreviewObelisk::initializePositions()
{
	HexusChapterPreview::initializePositions();
}