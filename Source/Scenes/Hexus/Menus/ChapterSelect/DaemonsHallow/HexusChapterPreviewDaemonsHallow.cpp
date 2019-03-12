#include "HexusChapterPreviewDaemonsHallow.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/DaemonsHallow.h"

using namespace cocos2d;

const std::string HexusChapterPreviewDaemonsHallow::SaveKeyChapterName = "HEXUS_CHAPTER_DAEMONS_HALLOW";

HexusChapterPreviewDaemonsHallow* HexusChapterPreviewDaemonsHallow::create()
{
	HexusChapterPreviewDaemonsHallow* instance = new HexusChapterPreviewDaemonsHallow();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewDaemonsHallow::HexusChapterPreviewDaemonsHallow() : HexusChapterPreview(HexusChapterPreviewDaemonsHallow::SaveKeyChapterName, Strings::Menus_Maps_DaemonsHallow::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano));
}

HexusChapterPreviewDaemonsHallow::~HexusChapterPreviewDaemonsHallow()
{
}

void HexusChapterPreviewDaemonsHallow::initializePositions()
{
	super::initializePositions();
}
