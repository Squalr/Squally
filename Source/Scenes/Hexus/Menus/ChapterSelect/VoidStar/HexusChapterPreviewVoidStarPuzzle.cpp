#include "HexusChapterPreviewVoidStarPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/VoidStar.h"

using namespace cocos2d;

const std::string HexusChapterPreviewVoidStarPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_VOID_STAR_PUZZLES";

HexusChapterPreviewVoidStarPuzzle* HexusChapterPreviewVoidStarPuzzle::create()
{
	HexusChapterPreviewVoidStarPuzzle* instance = new HexusChapterPreviewVoidStarPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewVoidStarPuzzle::HexusChapterPreviewVoidStarPuzzle() : HexusChapterPreview(HexusChapterPreviewVoidStarPuzzle::SaveKeyChapterName, Strings::Menus_Maps_VoidStar::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameVoidStar));
}

HexusChapterPreviewVoidStarPuzzle::~HexusChapterPreviewVoidStarPuzzle()
{
}

void HexusChapterPreviewVoidStarPuzzle::initializePositions()
{
	super::initializePositions();
}
