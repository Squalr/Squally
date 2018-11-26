#include "HexusChapterPreviewIceCaps.h"

const std::string HexusChapterPreviewIceCaps::stringKeyChapterName = "HEXUS_CHAPTER_ICE_CAPS";

HexusChapterPreviewIceCaps* HexusChapterPreviewIceCaps::create()
{
	HexusChapterPreviewIceCaps* instance = new HexusChapterPreviewIceCaps();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewIceCaps::HexusChapterPreviewIceCaps() : HexusChapterPreview(HexusChapterPreviewIceCaps::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps));
	this->text->setString("Ice Caps");
}

HexusChapterPreviewIceCaps::~HexusChapterPreviewIceCaps()
{
}

void HexusChapterPreviewIceCaps::initializePositions()
{
	HexusChapterPreview::initializePositions();
}