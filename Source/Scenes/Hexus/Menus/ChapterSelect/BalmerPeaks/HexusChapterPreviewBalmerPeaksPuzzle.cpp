#include "HexusChapterPreviewBalmerPeaksPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

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
	this->frameClip->addChild(Sprite::create(UIResources::Menus_Hexus_HexusFrameBalmerPeaks));
}

HexusChapterPreviewBalmerPeaksPuzzle::~HexusChapterPreviewBalmerPeaksPuzzle()
{
}

void HexusChapterPreviewBalmerPeaksPuzzle::initializePositions()
{
	super::initializePositions();
}
