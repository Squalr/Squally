#include "HexusChapterPreviewJungle.h"

const std::string HexusChapterPreviewJungle::stringKeyChapterName = "HEXUS_CHAPTER_JUNGLE";

HexusChapterPreviewJungle* HexusChapterPreviewJungle::create()
{
	HexusChapterPreviewJungle* instance = new HexusChapterPreviewJungle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewJungle::HexusChapterPreviewJungle() : HexusChapterPreview(HexusChapterPreviewJungle::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->text->setString("Jungle");
}

HexusChapterPreviewJungle::~HexusChapterPreviewJungle()
{
}

void HexusChapterPreviewJungle::initializePositions()
{
	HexusChapterPreview::initializePositions();
}