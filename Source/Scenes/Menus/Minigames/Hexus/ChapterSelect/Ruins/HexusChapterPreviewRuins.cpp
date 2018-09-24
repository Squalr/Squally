#include "HexusChapterPreviewRuins.h"

HexusChapterPreviewRuins* HexusChapterPreviewRuins::create()
{
	HexusChapterPreviewRuins* instance = new HexusChapterPreviewRuins();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewRuins::HexusChapterPreviewRuins()
{
	this->frameClip->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
}

HexusChapterPreviewRuins::~HexusChapterPreviewRuins()
{
}

void HexusChapterPreviewRuins::initializePositions()
{
	HexusChapterPreview::initializePositions();
}