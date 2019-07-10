#include "HexusChapterPreviewBalmerPeaksPuzzle.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/BallmerPeaks.h"

using namespace cocos2d;

const std::string HexusChapterPreviewBalmerPeaksPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_BALMER_PEAKS_PUZZLES";

HexusChapterPreviewBalmerPeaksPuzzle* HexusChapterPreviewBalmerPeaksPuzzle::create()
{
	HexusChapterPreviewBalmerPeaksPuzzle* instance = new HexusChapterPreviewBalmerPeaksPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewBalmerPeaksPuzzle::HexusChapterPreviewBalmerPeaksPuzzle() : HexusChapterPreview(HexusChapterPreviewBalmerPeaksPuzzle::SaveKeyChapterName, Strings::Menus_Maps_BallmerPeaks::create())
{
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameBalmerPeaks));
}

HexusChapterPreviewBalmerPeaksPuzzle::~HexusChapterPreviewBalmerPeaksPuzzle()
{
}

void HexusChapterPreviewBalmerPeaksPuzzle::initializePositions()
{
	super::initializePositions();
}
