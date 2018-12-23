#include "HexusChapterPreviewObelisk.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewObelisk::SaveKeyChapterName = "HEXUS_CHAPTER_OBELISK";

HexusChapterPreviewObelisk* HexusChapterPreviewObelisk::create()
{
	HexusChapterPreviewObelisk* instance = new HexusChapterPreviewObelisk();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewObelisk::HexusChapterPreviewObelisk() : HexusChapterPreview(HexusChapterPreviewObelisk::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->text->setString("The Void");
}

HexusChapterPreviewObelisk::~HexusChapterPreviewObelisk()
{
}

void HexusChapterPreviewObelisk::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
