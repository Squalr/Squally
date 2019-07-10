#include "HexusChapterPreviewSeaSharpCavernsPuzzle.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

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
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameSeaSharpCaverns));
}

HexusChapterPreviewSeaSharpCavernsPuzzle::~HexusChapterPreviewSeaSharpCavernsPuzzle()
{
}

void HexusChapterPreviewSeaSharpCavernsPuzzle::initializePositions()
{
	super::initializePositions();
}
