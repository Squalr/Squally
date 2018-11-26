#include "HexusChapterPreviewCastle.h"

const std::string HexusChapterPreviewCastle::stringKeyChapterName = "HEXUS_CHAPTER_CASTLE";

HexusChapterPreviewCastle* HexusChapterPreviewCastle::create()
{
	HexusChapterPreviewCastle* instance = new HexusChapterPreviewCastle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCastle::HexusChapterPreviewCastle() : HexusChapterPreview(HexusChapterPreviewCastle::stringKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->text->setString("Castle");
}

HexusChapterPreviewCastle::~HexusChapterPreviewCastle()
{
}

void HexusChapterPreviewCastle::initializePositions()
{
	HexusChapterPreview::initializePositions();
}