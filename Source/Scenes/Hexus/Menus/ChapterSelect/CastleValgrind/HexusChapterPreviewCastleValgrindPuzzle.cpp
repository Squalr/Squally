#include "HexusChapterPreviewCastleValgrindPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/CastleValgrind.h"

using namespace cocos2d;

const std::string HexusChapterPreviewCastleValgrindPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_CASTLE_VALGRIND_PUZZLES";

HexusChapterPreviewCastleValgrindPuzzle* HexusChapterPreviewCastleValgrindPuzzle::create()
{
	HexusChapterPreviewCastleValgrindPuzzle* instance = new HexusChapterPreviewCastleValgrindPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCastleValgrindPuzzle::HexusChapterPreviewCastleValgrindPuzzle() : HexusChapterPreview(HexusChapterPreviewCastleValgrindPuzzle::SaveKeyChapterName, Strings::Menus_Maps_CastleValgrind::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_Hexus_HexusFrameCastleValgrind));
}

HexusChapterPreviewCastleValgrindPuzzle::~HexusChapterPreviewCastleValgrindPuzzle()
{
}

void HexusChapterPreviewCastleValgrindPuzzle::initializePositions()
{
	super::initializePositions();
}
