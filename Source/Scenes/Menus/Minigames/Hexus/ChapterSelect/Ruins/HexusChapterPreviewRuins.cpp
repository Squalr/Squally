#include "HexusChapterPreviewRuins.h"

const std::string HexusChapterPreviewRuins::stringKeyChapterName = "HEXUS_CHAPTER_RUINS";

HexusChapterPreviewRuins* HexusChapterPreviewRuins::create()
{
	HexusChapterPreviewRuins* instance = new HexusChapterPreviewRuins();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewRuins::HexusChapterPreviewRuins() : HexusChapterPreview(HexusChapterPreviewRuins::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->text->setString("Ruins");
}

HexusChapterPreviewRuins::~HexusChapterPreviewRuins()
{
}

void HexusChapterPreviewRuins::initializePositions()
{
	HexusChapterPreview::initializePositions();
}