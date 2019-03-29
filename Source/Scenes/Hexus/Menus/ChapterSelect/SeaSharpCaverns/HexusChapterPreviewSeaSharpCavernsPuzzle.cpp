#include "HexusChapterPreviewSeaSharpCavernsPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/SeaSharpCaverns.h"

using namespace cocos2d;

const std::string HexusChapterPreviewSeaSharpCavernsPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_SEA_SHARP_CAVERNS_PUZZLES";

HexusChapterPreviewSeaSharpCavernsPuzzle* HexusChapterPreviewSeaSharpCavernsPuzzle::create()
{
	HexusChapterPreviewSeaSharpCavernsPuzzle* instance = new HexusChapterPreviewSeaSharpCavernsPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewSeaSharpCavernsPuzzle::HexusChapterPreviewSeaSharpCavernsPuzzle() : HexusChapterPreview(HexusChapterPreviewSeaSharpCavernsPuzzle::SaveKeyChapterName, Strings::Menus_Maps_SeaSharpCaverns::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns));
}

HexusChapterPreviewSeaSharpCavernsPuzzle::~HexusChapterPreviewSeaSharpCavernsPuzzle()
{
}

void HexusChapterPreviewSeaSharpCavernsPuzzle::initializePositions()
{
	super::initializePositions();
}
