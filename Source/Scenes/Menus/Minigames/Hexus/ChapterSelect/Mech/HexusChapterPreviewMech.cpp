#include "HexusChapterPreviewMech.h"

const std::string HexusChapterPreviewMech::stringKeyChapterName = "HEXUS_CHAPTER_MECH";

HexusChapterPreviewMech* HexusChapterPreviewMech::create()
{
	HexusChapterPreviewMech* instance = new HexusChapterPreviewMech();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewMech::HexusChapterPreviewMech() : HexusChapterPreview(HexusChapterPreviewMech::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech));
	this->text->setString("Laboratory");
}

HexusChapterPreviewMech::~HexusChapterPreviewMech()
{
}

void HexusChapterPreviewMech::initializePositions()
{
	HexusChapterPreview::initializePositions();
}