#include "HexusChapterPreviewEndianForestPuzzle.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/EndianForest.h"

using namespace cocos2d;

const std::string HexusChapterPreviewEndianForestPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_ENDIAN_FOREST_PUZZLES";

HexusChapterPreviewEndianForestPuzzle* HexusChapterPreviewEndianForestPuzzle::create()
{
	HexusChapterPreviewEndianForestPuzzle* instance = new HexusChapterPreviewEndianForestPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewEndianForestPuzzle::HexusChapterPreviewEndianForestPuzzle() : HexusChapterPreview(HexusChapterPreviewEndianForestPuzzle::SaveKeyChapterName, Strings::Menus_Maps_EndianForest::create())
{
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameEndianForest));
}

HexusChapterPreviewEndianForestPuzzle::~HexusChapterPreviewEndianForestPuzzle()
{
}

void HexusChapterPreviewEndianForestPuzzle::initializePositions()
{
	super::initializePositions();
}
