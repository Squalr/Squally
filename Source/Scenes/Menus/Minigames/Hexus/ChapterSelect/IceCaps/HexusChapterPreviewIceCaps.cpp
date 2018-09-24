#include "HexusChapterPreviewIceCaps.h"

HexusChapterPreviewIceCaps* HexusChapterPreviewIceCaps::create()
{
	HexusChapterPreviewIceCaps* instance = new HexusChapterPreviewIceCaps();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewIceCaps::HexusChapterPreviewIceCaps()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps));
}

HexusChapterPreviewIceCaps::~HexusChapterPreviewIceCaps()
{
}

void HexusChapterPreviewIceCaps::initializePositions()
{
	HexusChapterPreview::initializePositions();
}