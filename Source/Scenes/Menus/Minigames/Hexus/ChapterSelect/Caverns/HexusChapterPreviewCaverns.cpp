#include "HexusChapterPreviewCaverns.h"

HexusChapterPreviewCaverns* HexusChapterPreviewCaverns::create()
{
	HexusChapterPreviewCaverns* instance = new HexusChapterPreviewCaverns();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCaverns::HexusChapterPreviewCaverns()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns));
}

HexusChapterPreviewCaverns::~HexusChapterPreviewCaverns()
{
}

void HexusChapterPreviewCaverns::initializePositions()
{
	HexusChapterPreview::initializePositions();
}