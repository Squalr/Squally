#include "HexusChapterPreviewIceCaps.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewIceCaps::SaveKeyChapterName = "HEXUS_CHAPTER_ICE_CAPS";

HexusChapterPreviewIceCaps* HexusChapterPreviewIceCaps::create()
{
	HexusChapterPreviewIceCaps* instance = new HexusChapterPreviewIceCaps();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewIceCaps::HexusChapterPreviewIceCaps() : HexusChapterPreview(HexusChapterPreviewIceCaps::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps));
	this->text->setString("Ice Caps");
}

HexusChapterPreviewIceCaps::~HexusChapterPreviewIceCaps()
{
}

void HexusChapterPreviewIceCaps::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
