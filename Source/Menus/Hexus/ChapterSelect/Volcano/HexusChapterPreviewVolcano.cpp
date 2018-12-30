#include "HexusChapterPreviewVolcano.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/DaemonsHallow.h"

using namespace cocos2d;

const std::string HexusChapterPreviewVolcano::SaveKeyChapterName = "HEXUS_CHAPTER_VOLCANO";

HexusChapterPreviewVolcano* HexusChapterPreviewVolcano::create()
{
	HexusChapterPreviewVolcano* instance = new HexusChapterPreviewVolcano();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewVolcano::HexusChapterPreviewVolcano() : HexusChapterPreview(HexusChapterPreviewVolcano::SaveKeyChapterName, LocaleStrings::DaemonsHallow::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano));
}

HexusChapterPreviewVolcano::~HexusChapterPreviewVolcano()
{
}

void HexusChapterPreviewVolcano::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
