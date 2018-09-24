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
	this->text->setString("Caverns");
}

HexusChapterPreviewCaverns::~HexusChapterPreviewCaverns()
{
}

void HexusChapterPreviewCaverns::initializePositions()
{
	HexusChapterPreview::initializePositions();
}