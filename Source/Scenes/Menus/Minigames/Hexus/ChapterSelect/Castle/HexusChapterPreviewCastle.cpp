#include "HexusChapterPreviewCastle.h"

HexusChapterPreviewCastle* HexusChapterPreviewCastle::create()
{
	HexusChapterPreviewCastle* instance = new HexusChapterPreviewCastle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCastle::HexusChapterPreviewCastle()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
}

HexusChapterPreviewCastle::~HexusChapterPreviewCastle()
{
}

void HexusChapterPreviewCastle::initializePositions()
{
	HexusChapterPreview::initializePositions();
}