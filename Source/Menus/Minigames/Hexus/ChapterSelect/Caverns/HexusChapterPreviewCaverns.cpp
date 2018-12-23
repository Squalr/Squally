#include "HexusChapterPreviewCaverns.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewCaverns::SaveKeyChapterName = "HEXUS_CHAPTER_CAVERNS";

HexusChapterPreviewCaverns* HexusChapterPreviewCaverns::create()
{
	HexusChapterPreviewCaverns* instance = new HexusChapterPreviewCaverns();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCaverns::HexusChapterPreviewCaverns() : HexusChapterPreview(HexusChapterPreviewCaverns::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns));
	this->text->setString("Caverns");
}

HexusChapterPreviewCaverns::~HexusChapterPreviewCaverns()
{
}

void HexusChapterPreviewCaverns::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
