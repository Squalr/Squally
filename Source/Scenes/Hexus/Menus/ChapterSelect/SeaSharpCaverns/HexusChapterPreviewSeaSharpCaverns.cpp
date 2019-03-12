#include "HexusChapterPreviewSeaSharpCaverns.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/SeaSharpCaverns.h"

using namespace cocos2d;

const std::string HexusChapterPreviewSeaSharpCaverns::SaveKeyChapterName = "HEXUS_CHAPTER_SEA_SHARP_CAVERNS";

HexusChapterPreviewSeaSharpCaverns* HexusChapterPreviewSeaSharpCaverns::create()
{
	HexusChapterPreviewSeaSharpCaverns* instance = new HexusChapterPreviewSeaSharpCaverns();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewSeaSharpCaverns::HexusChapterPreviewSeaSharpCaverns() : HexusChapterPreview(HexusChapterPreviewSeaSharpCaverns::SaveKeyChapterName, Strings::Menus_Maps_SeaSharpCaverns::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns));
}

HexusChapterPreviewSeaSharpCaverns::~HexusChapterPreviewSeaSharpCaverns()
{
}

void HexusChapterPreviewSeaSharpCaverns::initializePositions()
{
	super::initializePositions();
}
