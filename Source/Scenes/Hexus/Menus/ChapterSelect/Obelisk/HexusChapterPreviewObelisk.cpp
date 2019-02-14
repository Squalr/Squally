#include "HexusChapterPreviewObelisk.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/LambdaCrypts.h"

using namespace cocos2d;

const std::string HexusChapterPreviewObelisk::SaveKeyChapterName = "HEXUS_CHAPTER_OBELISK";

HexusChapterPreviewObelisk* HexusChapterPreviewObelisk::create()
{
	HexusChapterPreviewObelisk* instance = new HexusChapterPreviewObelisk();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewObelisk::HexusChapterPreviewObelisk() : HexusChapterPreview(HexusChapterPreviewObelisk::SaveKeyChapterName, Strings::Menus_Maps_LambdaCrypts::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
}

HexusChapterPreviewObelisk::~HexusChapterPreviewObelisk()
{
}

void HexusChapterPreviewObelisk::initializePositions()
{
	super::initializePositions();
}
