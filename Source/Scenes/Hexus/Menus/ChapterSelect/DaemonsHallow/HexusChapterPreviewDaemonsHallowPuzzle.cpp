#include "HexusChapterPreviewDaemonsHallowPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/DaemonsHallow.h"

using namespace cocos2d;

const std::string HexusChapterPreviewDaemonsHallowPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_DAEMONS_HALLOW_PUZZLES";

HexusChapterPreviewDaemonsHallowPuzzle* HexusChapterPreviewDaemonsHallowPuzzle::create()
{
	HexusChapterPreviewDaemonsHallowPuzzle* instance = new HexusChapterPreviewDaemonsHallowPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewDaemonsHallowPuzzle::HexusChapterPreviewDaemonsHallowPuzzle() : HexusChapterPreview(HexusChapterPreviewDaemonsHallowPuzzle::SaveKeyChapterName, Strings::Menus_Maps_DaemonsHallow::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameDaemonsHallow));
}

HexusChapterPreviewDaemonsHallowPuzzle::~HexusChapterPreviewDaemonsHallowPuzzle()
{
}

void HexusChapterPreviewDaemonsHallowPuzzle::initializePositions()
{
	super::initializePositions();
}
