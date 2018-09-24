#include "HexusChapterPreviewJungle.h"

HexusChapterPreviewJungle* HexusChapterPreviewJungle::create()
{
	HexusChapterPreviewJungle* instance = new HexusChapterPreviewJungle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewJungle::HexusChapterPreviewJungle()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
}

HexusChapterPreviewJungle::~HexusChapterPreviewJungle()
{
}

void HexusChapterPreviewJungle::initializePositions()
{
	HexusChapterPreview::initializePositions();
}