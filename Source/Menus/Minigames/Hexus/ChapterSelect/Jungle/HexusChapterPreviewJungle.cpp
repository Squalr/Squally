#include "HexusChapterPreviewJungle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewJungle::SaveKeyChapterName = "HEXUS_CHAPTER_JUNGLE";

HexusChapterPreviewJungle* HexusChapterPreviewJungle::create()
{
	HexusChapterPreviewJungle* instance = new HexusChapterPreviewJungle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewJungle::HexusChapterPreviewJungle() : HexusChapterPreview(HexusChapterPreviewJungle::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->text->setString("Jungle");
}

HexusChapterPreviewJungle::~HexusChapterPreviewJungle()
{
}

void HexusChapterPreviewJungle::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
