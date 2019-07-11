#include "HexusChapterPreviewSeaSharpCaverns.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

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
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameSeaSharpCaverns));
}

HexusChapterPreviewSeaSharpCaverns::~HexusChapterPreviewSeaSharpCaverns()
{
}

void HexusChapterPreviewSeaSharpCaverns::initializePositions()
{
	super::initializePositions();
}
