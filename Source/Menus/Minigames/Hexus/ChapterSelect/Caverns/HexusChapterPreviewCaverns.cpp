#include "HexusChapterPreviewCaverns.h"

const std::string HexusChapterPreviewCaverns::stringKeyChapterName = "HEXUS_CHAPTER_CAVERNS";

HexusChapterPreviewCaverns* HexusChapterPreviewCaverns::create()
{
	HexusChapterPreviewCaverns* instance = new HexusChapterPreviewCaverns();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCaverns::HexusChapterPreviewCaverns() : HexusChapterPreview(HexusChapterPreviewCaverns::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns));
	this->text->setString("Caverns");
}

HexusChapterPreviewCaverns::~HexusChapterPreviewCaverns()
{
}

void HexusChapterPreviewCaverns::initializePositions()
{
	HexusChapterPreview::initializePositions();
}