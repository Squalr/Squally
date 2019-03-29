#include "HexusChapterPreviewEndianForestPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

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
	this->frameClip->addChild(Sprite::create(UIResources::Menus_Hexus_HexusFrameEndianForest));
}

HexusChapterPreviewEndianForestPuzzle::~HexusChapterPreviewEndianForestPuzzle()
{
}

void HexusChapterPreviewEndianForestPuzzle::initializePositions()
{
	super::initializePositions();
}
